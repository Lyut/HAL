#pragma once
#include <cstddef>
#include <vector>
#include <thread>
#include "includes.h"
#include "memoryman.h"
#include "hooks.h"
#include "hooks/present.h"
#include "hooks/reset.h"

namespace HAL::Core {

    void HALAllocConsole() {
        AllocConsole();
        SetConsoleTitleA("HELLO");
        FILE* NewConsoleStream;
        freopen_s(&NewConsoleStream, "CONIN$", "r", stdin);
        freopen_s(&NewConsoleStream, "CONOUT$", "w", stdout);
        freopen_s(&NewConsoleStream, "CONOUT$", "w", stderr);
    }

    void Attach(const HMODULE Instance)
    {
        auto Shutdown = [Instance]() -> void
        {
            FreeLibraryAndExitThread(Instance, EXIT_FAILURE);
        };

        [[unlikely]]
#ifdef _WIN64
        while (!GetModuleHandleA(xorstr_("gameoverlayrenderer64.dll")))
#else
        while (!GetModuleHandleA(xorstr_("gameoverlayrenderer.dll")))
#endif
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }

        [[unlikely]]
        if (!MemoryMan::Initialize())
        {
            Shutdown();
        }

        Hooks::Present::g_pPresent = MemoryMan::PatternScan(GetModuleHandleA(xorstr_("gameoverlayrenderer64.dll")), xorstr_("48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8"));

        [[unlikely]]
        if (!Hooks::Present::g_pPresent)
        {
            Shutdown();
        }

        MemoryMan::Hook(Hooks::Present::g_pPresent, &Hooks::Present::Present_hk, &Hooks::Present::o_Present);

        Hooks::Reset::g_pCreateSwapChain = MemoryMan::PatternScan(GetModuleHandleA(xorstr_("gameoverlayrenderer64.dll")), xorstr_("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F9 49 8B F1 48 8D 0D ? ? ? ? 49 8B D8 48 8B EA E8 ? ? ? ? 4C 8B CE 4C 8B C3 48 8B D5 48 8B CF FF 15 ? ? ? ? 8B D8 85 C0 78 ? 48 85 F6 74 ? 48 83 3E ? 74 ? 48 8B D5 48 8B CE E8 ? ? ? ? 8B C3 48 8B 5C 24 ? 48 8B 6C 24 ? 48 8B 74 24 ? 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24"));

        [[unlikely]]
        if (!Hooks::Reset::g_pCreateSwapChain)
        {
            Shutdown();
        }

        MemoryMan::Hook(Hooks::Reset::g_pCreateSwapChain, &Hooks::Reset::CreateSwapChain_hk, &Hooks::Reset::o_CreateSwapChain);

        /* [[likely]]
        while (!GetAsyncKeyState(VK_DELETE))
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        FreeLibraryAndExitThread(Instance, EXIT_SUCCESS); */
    }

    void Detach()
    {
      /*fclose(stdin);
        fclose(stdout);
        fclose(stderr);
        FreeConsole();*/
        MemoryMan::UnhookAll();
    }

}