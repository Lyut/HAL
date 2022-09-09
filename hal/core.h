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
        while (!GetModuleHandleA("gameoverlayrenderer64.dll"))
#else
        while (!GetModuleHandleA("gameoverlayrenderer.dll"))
#endif
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }

        [[unlikely]]
        if (!MemoryMan::Initialize())
        {
            Shutdown();
        }

        HAL::Hooks::Present::g_pPresent = HAL::MemoryMan::PatternScan(GetModuleHandleA("gameoverlayrenderer64.dll"), "48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8");

        [[unlikely]]
        if (!HAL::Hooks::Present::g_pPresent)
        {
            Shutdown();
        }

        HAL::MemoryMan::Hook(HAL::Hooks::Present::g_pPresent, &HAL::Hooks::Present::Present_hk, &HAL::Hooks::Present::o_Present);

        /*HAL::Hooks::Reset::g_pDeleteD3D11RendererForSwapChain = HAL::MemoryMan::PatternScan(GetModuleHandleA("gameoverlayrenderer64.dll"), "48 89 6C 24 ? 57 48 83 EC ? 48 8B FA 48 8B E9 48 8B 51 ? 48 8B C2 4C 8B 42 ? 41 80 78 ? ? 75 ? 49 39 78 ? 73 ? 4D 8B 40 ? EB ? 49 8B C0 4D 8B 00 41 80 78 ? ? 74 ? 80 78 ? ? 0F 85 ? ? ? ? 48 3B 78 ? 0F 82 ? ? ? ? 48 3B C2 0F 84 ? ? ? ? 4C 8B 40 ? 48 8B D0 48 89 5C 24 ? 48 89 74 24 ? 41 80 78 ? ? 74 ? 48 8B 48 ? 80 79 ? ? 75 ? 66 0F 1F 44 00 ? 48 3B 41 ? 75 ? 48 8B C1 48 8B 49 ? 80 79 ? ? 74 ? EB ? 4D 8B 00 41 80 78 ? ? 75 ? 90 49 8B 00 4C 8B C0 80 78 ? ? 74 ? 48 8D 4D ? E8 ? ? ? ? BA ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 8B D7 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 4D ? 48 8B D9 48 8B 41 ? 80 78 ? ? 75 ? 48 39 78 ? 73 ? 48 8B 40 ? EB ? 48 8B D8 48 8B 00 80 78 ? ? 74 ? 80 7B ? ? 75 ? 48 3B 7B ? 72 ? 48 3B D9 74 ? 48 8B 7B ? 48 8D 53 ? 48 8D 4D ? E8 ? ? ? ? 48 8B D3 48 8D 4D ? E8 ? ? ? ? 48 85 FF 74 ? 48 8B 07 BA ? ? ? ? 48 8B CF FF 10 EB ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24 ? 48 8B 6C 24 ? 48 83 C4 ? 5F C3 CC CC CC 40 56");
        [[unlikely]]
        if (!HAL::Hooks::Reset::g_pDeleteD3D11RendererForSwapChain)
        {
            Shutdown();
        }
        HAL::MemoryMan::Hook(HAL::Hooks::Reset::g_pDeleteD3D11RendererForSwapChain, &HAL::Hooks::Reset::DeleteD3D11RendererForSwapChain_hk, &HAL::Hooks::Reset::o_DeleteD3D11RendererForSwapChain); */

        HAL::Hooks::Reset::g_pCreateSwapChain = HAL::MemoryMan::PatternScan(GetModuleHandleA("gameoverlayrenderer64.dll"), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F9 49 8B F1 48 8D 0D ? ? ? ? 49 8B D8 48 8B EA E8 ? ? ? ? 4C 8B CE 4C 8B C3 48 8B D5 48 8B CF FF 15 ? ? ? ? 8B D8 85 C0 78 ? 48 85 F6 74 ? 48 83 3E ? 74 ? 48 8B D5 48 8B CE E8 ? ? ? ? 8B C3 48 8B 5C 24 ? 48 8B 6C 24 ? 48 8B 74 24 ? 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24");

        [[unlikely]]
        if (!HAL::Hooks::Reset::g_pCreateSwapChain)
        {
            Shutdown();
        }

        HAL::MemoryMan::Hook(HAL::Hooks::Reset::g_pCreateSwapChain, &HAL::Hooks::Reset::CreateSwapChain_hk, &HAL::Hooks::Reset::o_CreateSwapChain);

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
        HAL::MemoryMan::UnhookAll();
        //SetWindowLongPtr(HAL::Hooks::Present::hWndDX, GWLP_WNDPROC, (LONG)HAL::Hooks::WndProc::WndProcFunc);
    }

}