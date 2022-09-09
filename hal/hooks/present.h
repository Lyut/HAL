#pragma once
#include "../includes.h"
#include "../hooks.h"
#include "../graphics/drawing.h"
#include "../graphics/imgui.h"
#include "../graphics/imgui_impl_dx11.h"
#include "../graphics/imgui_impl_WIN32.h"
#include "../graphics/imgui_internal.h"
#include "../graphics/font.h"
#include "../sdk/utils.h"

ID3D11Device* pD11Device = nullptr;
ID3D11DeviceContext* pD11DeviceContext = nullptr;
ID3D11RenderTargetView* pD11RenderTargetView = nullptr;
WNDPROC oWndProc;
HRESULT(*HK_PresentOriginal)(IDXGISwapChain* dxSwapChain, UINT syncInterval, UINT flags) = nullptr;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


inline void ImguiStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowPadding = ImVec2(15, 15);
    style->WindowRounding = 0.0f;
    style->FramePadding = ImVec2(5, 5);
    style->FrameRounding = 0.0f;
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;
    style->ChildRounding = 1.0f;
    style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style->TabRounding = 0.0f;
    style->TabBorderSize = 0.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.80f);
    style->Colors[ImGuiCol_Tab] = ImVec4(0.30f, 0.22f, 0.76f, 1.00f);
    style->Colors[ImGuiCol_TabActive] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.00f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.30f, 0.22f, 0.76f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.30f, 0.22f, 0.76f, 1.00f);;
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.30f, 0.22f, 0.76f, 1.00f);;
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.47f, 0.33f, 0.33f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.33f, 0.33f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.30f, 0.22f, 0.76f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

LRESULT __stdcall HAL::Hooks::Present::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_SIZE:
        if (pD11Device != NULL && wParam != SIZE_MINIMIZED) {
            ImGui_ImplDX11_InvalidateDeviceObjects();
            ImGui_ImplDX11_CreateDeviceObjects();
        }
        break;
    /*case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return false;
        break;*/
    }

    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return false;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT HAL::Hooks::Present::Present_hk(IDXGISwapChain* dxSwapChain, UINT syncInterval, UINT flags) 
{
    [[unlikely]]
    if (!pD11Device || !pD11DeviceContext)
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
		io.Fonts->AddFontFromMemoryTTF(&lewdFontData, sizeof lewdFontData, 14);

        if (SUCCEEDED(dxSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pD11Device)))
        {
            dxSwapChain->GetDevice(__uuidof(pD11Device), (void**)&pD11Device);
            pD11Device->GetImmediateContext(&pD11DeviceContext);
        }

        DXGI_SWAP_CHAIN_DESC desc;
        dxSwapChain->GetDesc(&desc);
        oWndProc = (WNDPROC)SetWindowLongPtr(desc.OutputWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

        ImGui_ImplWin32_Init(desc.OutputWindow);
        ImGui_ImplDX11_Init(pD11Device, pD11DeviceContext);
    }
    else
    {
        ID3D11Texture2D* renderTargetTexture = nullptr;
        if (!pD11RenderTargetView)
        {
            if (SUCCEEDED(dxSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&renderTargetTexture))))
            {
                pD11Device->CreateRenderTargetView(renderTargetTexture, nullptr, &pD11RenderTargetView);
                renderTargetTexture->Release();
            }
        }
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

   // HAL::Graphics::Drawing::Draw();
    ImguiStyle();
    ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Once, ImVec2(0.5f, 0.5f));
    ImGui::SetWindowSize(ImVec2(300, 500));
    ImGui::Begin("lewd.vip menu");
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
    if (ImGui::BeginTabBar("merdaMenu", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("DEBUG"))
        {

            ImGui::Text((std::string("GTA version: b") + std::to_string(HAL::SDK::Utils::GetGameBuild())).c_str());
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Aimbot"))
        {

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("ESP"))
        {

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Chams"))
        {

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Settings"))
        {

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::End();

    pD11DeviceContext->OMSetRenderTargets(1, &pD11RenderTargetView, nullptr);
    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return HAL::Hooks::Present::o_Present(dxSwapChain, syncInterval, flags);
}