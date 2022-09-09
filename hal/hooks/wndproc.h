#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include "../graphics/imgui.h"
#include "../graphics/imgui_impl_dx11.h"
#include "../graphics/imgui_internal.h"
#include "../hooks.h"
#pragma comment(lib, "d3d11.lib")

/*extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT HAL::Hooks::WndProc::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_SIZE:
        if (HAL::Hooks::Present::hWndDX != NULL && wParam != SIZE_MINIMIZED) {
            ImGui_ImplDX11_InvalidateDeviceObjects();
            ImGui_ImplDX11_CreateDeviceObjects();
        }
        break;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return false;
        break;
    }

    if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam)) {
        return true;
    }

    return CallWindowProcA(WndProcFunc, hwnd, uMsg, wParam, lParam);
}*/