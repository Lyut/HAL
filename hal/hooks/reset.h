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

void HAL::Hooks::Reset::CreateSwapChain_hk(__int64 who_cares, ID3D11Device* pDevice, DXGI_SWAP_CHAIN_DESC pDesc, __int64** ppSwapChain) {
	VMP_BEGIN("HAL::Hooks::Reset::CreateSwapChain_hk");
    ImGui_ImplDX11_InvalidateDeviceObjects();
	pD11RenderTargetView->Release();
	pD11RenderTargetView = nullptr;
	pD11Device->Release();
	pD11Device = nullptr;
	SDK::Game::Init();

	return o_CreateSwapChain(who_cares, pDevice, pDesc, ppSwapChain);
	VMP_END();
}