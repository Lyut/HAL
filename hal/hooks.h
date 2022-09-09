#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include "graphics/imgui.h"
#include "graphics/imgui_impl_dx11.h"
#include "graphics/imgui_internal.h"
#pragma comment(lib, "d3d11.lib")

namespace HAL::Hooks
{
    namespace Present
    {
        using FnPresent = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
        void* g_pPresent;
        FnPresent o_Present;
        HWND hWndDX;
        WNDPROC WndProcFunc;
        LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
        HRESULT Present_hk(IDXGISwapChain*, UINT, UINT);
    }
    namespace Reset
    {
        /*using FnDeleteD3D11RendererForSwapChain = void(__stdcall*)(__int64, IDXGISwapChain*);
        void* g_pDeleteD3D11RendererForSwapChain;
        FnDeleteD3D11RendererForSwapChain o_DeleteD3D11RendererForSwapChain;
        void DeleteD3D11RendererForSwapChain_hk(__int64, IDXGISwapChain*);*/
        using FnCreateSwapChain = void(__stdcall*)(__int64, ID3D11Device*, DXGI_SWAP_CHAIN_DESC, __int64**);
        void* g_pCreateSwapChain;
        FnCreateSwapChain o_CreateSwapChain;
        void CreateSwapChain_hk(__int64, ID3D11Device*, DXGI_SWAP_CHAIN_DESC, __int64**);
    }
   /* namespace WndProc
    {
        WNDPROC WndProcFunc;
        LRESULT WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    }*/
}