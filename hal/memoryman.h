#pragma once
#include <Windows.h>
#include <vector>
#include <Psapi.h>
#include <winternl.h>
#include <filesystem>
#include "xorstr.h"

#ifdef _WIN64
#define PTRMAXVAL ((DWORD64)0x000F000000000000)
#else
#define PTRMAXVAL ((DWORD64)0xFFF00000)
#endif

namespace HAL::MemoryMan
{
    void OutputDebugString_(const std::string& s)
    {
        ::OutputDebugStringA(s.c_str());
    }

    HMODULE getModuleHandle(const char* name)
    {
        PEB* peb = (PEB*)__readgsqword(0x60);

        LIST_ENTRY* head = &peb->Ldr->InMemoryOrderModuleList;
        for (LIST_ENTRY* item = head->Flink; item != head; item = item->Flink)
        {
            LDR_DATA_TABLE_ENTRY* entry = CONTAINING_RECORD(item, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

            std::filesystem::path path(entry->FullDllName.Buffer);

            if (path.filename() == name)
                return (HMODULE)entry->DllBase;
        }

        return nullptr;
    }

    namespace PageGuard
    {
        static void* breakpointAddress;
        static void* anti_cheat_base;
        static MODULEINFO anti_cheat_info;

        static void* GOR_base;

        auto PageGuardMemory(void* address, const SIZE_T length) -> void
        {
            DWORD oldProtect;
            MEMORY_BASIC_INFORMATION mbi;

            VirtualQuery(static_cast<const void*>(address), &mbi, sizeof(MEMORY_BASIC_INFORMATION));

            if (!VirtualProtect(address, length, mbi.Protect | PAGE_GUARD, &oldProtect))
            {
                OutputDebugString_("[#] failed to protect: " + std::to_string(GetLastError()));
            }
        }

        auto UnPageGuardMemory(void* address, const SIZE_T length) -> void
        {
            DWORD oldProtect;
            MEMORY_BASIC_INFORMATION mbi;

            VirtualQuery(static_cast<const void*>(address), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
            VirtualProtect(address, length, mbi.Protect & ~PAGE_GUARD, &oldProtect);
        }

        typedef LONG(NTAPI* NtSuspendProcess)(IN HANDLE ProcessHandle);

        void SuspendProc(DWORD processId)
        {
            HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

            NtSuspendProcess pfnNtSuspendProcess = (NtSuspendProcess)GetProcAddress(
                GetModuleHandleA("ntdll.dll"), "NtSuspendProcess");

            pfnNtSuspendProcess(processHandle);
            CloseHandle(processHandle);
        }

        auto CALLBACK VectoredExceptionHandler(_EXCEPTION_POINTERS* ep) -> LONG
        {
            if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_GUARD_PAGE)
            {
                //SDK::OutputDebugString_("[#] memory attempt access");

                auto address_source = ep->ExceptionRecord->ExceptionAddress;
                auto address_destination = ep->ExceptionRecord->ExceptionInformation[1];

                if ((void*)address_source >= anti_cheat_base && address_source <= (void*)((uintptr_t)anti_cheat_base + anti_cheat_info.SizeOfImage))
                {
                    std::stringstream stream_address_source; stream_address_source << std::hex << address_source; std::string result_address_source(stream_address_source.str());
                    std::stringstream stream_address_base; stream_address_base << std::hex << anti_cheat_base; std::string result_address_base(stream_address_base.str());
                    std::stringstream stream_address_offset; stream_address_offset << std::hex << (uintptr_t)address_source - (uintptr_t)anti_cheat_base; std::string result_address_offset(stream_address_offset.str());
                    std::stringstream stream_address_destination; stream_address_destination << std::hex << address_destination; std::string result_address_destination(stream_address_destination.str());
                    std::stringstream stream_address_offset_lua; stream_address_offset_lua << std::hex << (uintptr_t)address_destination - (uintptr_t)GOR_base; std::string result_address_offset_lua(stream_address_offset_lua.str());

                    OutputDebugString_("[#] memory attempt access from adhesive: source: " + result_address_source +
                        std::string(" base: ") + result_address_base +
                        std::string(" offset: ") + result_address_offset +
                        std::string(" destination: ") + result_address_destination +
                        std::string(" offset from gor64.dll: ") + result_address_offset_lua);
                   // OutputDebugString_("[#] memory attempt access from adhesive");
                   // SuspendProc(GetCurrentProcessId());
                }

                ep->ContextRecord->EFlags |= 0x100ui32;

                return EXCEPTION_CONTINUE_EXECUTION;
            }
            else if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
            {
                PageGuardMemory(breakpointAddress, 1);

                return EXCEPTION_CONTINUE_EXECUTION;
            }

            return EXCEPTION_CONTINUE_SEARCH;
        }

        auto initializeBreakpoint(void* address) -> void
        {
            breakpointAddress = address;
            PageGuardMemory(breakpointAddress, 1ui64);
        }

        auto disableBreakpoint(void* address) -> void
        {
            breakpointAddress = nullptr;
            UnPageGuardMemory(address, 1ui64);
        }
    }

    bool ValidPTR(DWORD64 ptr)
    {
        if (ptr >= 0x10000 && ptr < PTRMAXVAL)
            return true;

        return false;
    }

    std::uint8_t* PatternScan(const HMODULE Module, const char* Signature)
    {
        [[unlikely]]
        if (!Module)
            return {};

        static auto PatternToBytes = [](const char* Pattern)
        {
            auto Bytes = std::vector<int>{};
            char* StartPos = const_cast<char*>(Pattern);
            char* EndPos = const_cast<char*>(Pattern) + std::strlen(Pattern);

            for (auto CurrentChar = StartPos; CurrentChar < EndPos; ++CurrentChar)
            {
                if (*CurrentChar == '?')
                {
                    ++CurrentChar;

                    if (*CurrentChar == '?')
                        ++CurrentChar;

                    Bytes.push_back(-1);
                }
                else
                    Bytes.push_back(std::strtoul(CurrentChar, &CurrentChar, 16));
            }

            return Bytes;
        };

        const IMAGE_DOS_HEADER* DosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(Module);
        const IMAGE_NT_HEADERS* NtHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<std::uint8_t*>(Module) + DosHeader->e_lfanew);

        auto PatternBytes = PatternToBytes(Signature);
        const std::size_t PatternBytesSize = PatternBytes.size();
        const int* PatternBytesData = PatternBytes.data();

        const auto ImageSize = NtHeaders->OptionalHeader.SizeOfImage;
        std::uint8_t* ScanBytes = reinterpret_cast<std::uint8_t*>(Module);

        for (unsigned long i = 0; i < ImageSize - PatternBytesSize; ++i)
        {
            bool Found = true;

            for (unsigned long j = 0; j < PatternBytesSize; ++j)
            {
                if (ScanBytes[i + j] != PatternBytesData[j] && PatternBytesData[j] != -1)
                {
                    Found = false;
                    break;
                }
            }

            [[unlikely]]
            if (Found)
                return &ScanBytes[i];
        }

        return {};
    }

#ifdef _WIN64
    // char __fastcall ValveHookWrapper(void *FnAddr, __int64 HkAddr, _QWORD *OgAddr, int PreserveLogs)
    using FnValveHook = char(__fastcall*)(void*, void*, void*, int);
#else
    // char __cdecl ValveHook(LPVOID FnAddr, int HkAddr, int OgAddr, int PreserveLogs)
    using FnValveHook = char(__cdecl*)(void*, void*, void*, int);
#endif
    FnValveHook ValveHook;

#ifdef _WIN64
    // void __fastcall ValveUnhook(unsigned __int64 FnAddr, char a2)
    using FnValveUnhook = void(__fastcall*)(void*, char);
#else
    // void __cdecl ValveUnhook(unsigned int FnAddr, char a2)
    using FnValveUnhook = void(__cdecl*)(unsigned int, char);
#endif
    FnValveUnhook ValveUnhook;

    // Store all hooks
    std::vector<void*> EnabledHooks;

    bool Initialize()
    {
#ifdef _WIN64
        const HMODULE GameOverlayRenderer = GetModuleHandleA(xorstr_("gameoverlayrenderer64.dll"));
#else
        const HMODULE GameOverlayRenderer = GetModuleHandleA("gameoverlayrenderer.dll");
#endif

        [[unlikely]]
        if (!GameOverlayRenderer)
            return false;

#ifdef _WIN64
        ValveHook = reinterpret_cast<FnValveHook>(PatternScan(GameOverlayRenderer, xorstr_("48 89 5C 24 ? 57 48 83 EC 30 33 C0")));
#else
        ValveHook = reinterpret_cast<FnValveHook>(PatternScan(GameOverlayRenderer, "55 8B EC 51 8B 45 10 C7"));
#endif

        [[unlikely]]
        if (!ValveHook)
            return false;

#ifdef _WIN64
        const std::uint8_t* JmpAddress = PatternScan(GameOverlayRenderer, xorstr_("E8 ? ? ? ? FF 15 ? ? ? ? 48 89 45 E8"));
#else
        const std::uint8_t* JmpAddress = PatternScan(GameOverlayRenderer, "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?");
#endif

        ValveUnhook = reinterpret_cast<FnValveUnhook>(JmpAddress + 5 + *(DWORD*)(JmpAddress + 1));

        [[unlikely]]
        if (!ValveUnhook)
            return false;

        return true;
    }

    bool Hook(void* FunctionAddress, void* HookAddress, void* OriginalAddress)
    {
        const bool SuccessfullyHooked = static_cast<bool>(ValveHook(FunctionAddress, HookAddress, OriginalAddress, 0));

        [[likely]]
        if (SuccessfullyHooked)
            EnabledHooks.push_back(FunctionAddress);

        return SuccessfullyHooked;
    }

    void Unhook(void* FunctionAddress)
    {
#ifdef _WIN64
        ValveUnhook(FunctionAddress, 0);
#else
        ValveUnhook(reinterpret_cast<unsigned int>(FunctionAddress), 0);
#endif
    }

    void UnhookAll()
    {
        for (void* EnabledHook : EnabledHooks)
            Unhook(EnabledHook);
    }
}