#pragma once
#include "../includes.h"
#include "../hooks.h"
#include "../core.h"
#include "../graphics/drawing.h"
#include "../graphics/imgui.h"
#include "../graphics/imgui_impl_dx11.h"
#include "../graphics/imgui_impl_WIN32.h"
#include "../graphics/imgui_internal.h"

// SHOUTOUT TO VALVe SOFTWARE!

/*void HAL::Hooks::Reset::DeleteD3D11RendererForSwapChain_hk(__int64 who_cares, IDXGISwapChain* pSwapChain) {
    ImGui_ImplDX11_InvalidateDeviceObjects();
	pD11RenderTargetView->Release();
	pD11Device->Release();

	return o_DeleteD3D11RendererForSwapChain(who_cares, pSwapChain);
}*/

void HAL::Hooks::Reset::CreateSwapChain_hk(__int64 unk, ID3D11Device* pDevice, DXGI_SWAP_CHAIN_DESC pDesc, __int64** ppSwapChain) {
	ImGui_ImplDX11_InvalidateDeviceObjects();
	pD11RenderTargetView = nullptr;
	pD11Device = nullptr;

	return o_CreateSwapChain(unk, pDevice, pDesc, ppSwapChain);
}