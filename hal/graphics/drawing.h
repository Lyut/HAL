#pragma once
#include <string>
#include "../includes.h"
#include "../graphics/imgui.h"
#include "../graphics/imgui_impl_dx11.h"
#include "../graphics/imgui_internal.h"
#include "../sdk/utils.h"
#include "../hooks.h"
#include "../config.h"

namespace HAL::Graphics::Drawing
{
	typedef struct
	{
		DWORD R;
		DWORD G;
		DWORD B;
		DWORD A;
	}RGBA;

	class Color
	{
	public:
		RGBA red = { 255,0,0,255 };
		RGBA Magenta = { 255,0,255,255 };
		RGBA yellow = { 255,255,0,255 };
		RGBA grayblue = { 128,128,255,255 };
		RGBA green = { 128,224,0,255 };
		RGBA darkgreen = { 0,224,128,255 };
		RGBA brown = { 192,96,0,255 };
		RGBA pink = { 255,168,255,255 };
		RGBA DarkYellow = { 216,216,0,255 };
		RGBA SilverWhite = { 236,236,236,255 };
		RGBA purple = { 144,0,255,255 };
		RGBA Navy = { 88,48,224,255 };
		RGBA skyblue = { 0,136,255,255 };
		RGBA graygreen = { 128,160,128,255 };
		RGBA blue = { 0,96,192,255 };
		RGBA orange = { 255,128,0,255 };
		RGBA peachred = { 255,80,128,255 };
		RGBA reds = { 255,128,192,255 };
		RGBA darkgray = { 96,96,96,255 };
		RGBA Navys = { 0,0,128,255 };
		RGBA darkgreens = { 0,128,0,255 };
		RGBA darkblue = { 0,128,128,255 };
		RGBA redbrown = { 128,0,0,255 };
		RGBA purplered = { 128,0,128,255 };
		RGBA greens = { 0,255,0,255 };
		RGBA envy = { 0,255,255,255 };
		RGBA black = { 0,0,0,255 };
		RGBA gray = { 128,128,128,255 };
		RGBA white = { 255,255,255,255 };
		RGBA blues = { 30,144,255,255 };
		RGBA lightblue = { 135,206,250,160 };
		RGBA Scarlet = { 220, 20, 60, 160 };
		RGBA white_ = { 255,255,255,200 };
		RGBA gray_ = { 128,128,128,200 };
		RGBA black_ = { 0,0,0,200 };
		RGBA red_ = { 255,0,0,200 };
		RGBA Magenta_ = { 255,0,255,200 };
		RGBA yellow_ = { 255,255,0,200 };
		RGBA grayblue_ = { 128,128,255,200 };
		RGBA green_ = { 128,224,0,200 };
		RGBA darkgreen_ = { 0,224,128,200 };
		RGBA brown_ = { 192,96,0,200 };
		RGBA pink_ = { 255,168,255,200 };
		RGBA darkyellow_ = { 216,216,0,200 };
		RGBA silverwhite_ = { 236,236,236,200 };
		RGBA purple_ = { 144,0,255,200 };
		RGBA Blue_ = { 88,48,224,200 };
		RGBA skyblue_ = { 0,136,255,200 };
		RGBA graygreen_ = { 128,160,128,200 };
		RGBA blue_ = { 0,96,192,200 };
		RGBA orange_ = { 255,128,0,200 };
		RGBA pinks_ = { 255,80,128,200 };
		RGBA Fuhong_ = { 255,128,192,200 };
		RGBA darkgray_ = { 96,96,96,200 };
		RGBA Navy_ = { 0,0,128,200 };
		RGBA darkgreens_ = { 0,128,0,200 };
		RGBA darkblue_ = { 0,128,128,200 };
		RGBA redbrown_ = { 128,0,0,200 };
		RGBA purplered_ = { 128,0,128,200 };
		RGBA greens_ = { 0,255,0,200 };
		RGBA envy_ = { 0,255,255,200 };

		RGBA glassblack = { 0, 0, 0, 160 };
		RGBA GlassBlue = { 65,105,225,80 };
		RGBA glassyellow = { 255,255,0,160 };
		RGBA glass = { 200,200,200,60 };


		RGBA Plum = { 221,160,221,160 };

	};
	Color Col;

	RGBA FLOAT4TORGBA(float Col[])
	{
		ImU32 col32_no_alpha = ImGui::ColorConvertFloat4ToU32(ImVec4(Col[0], Col[1], Col[2], Col[3]));
		float a = (col32_no_alpha >> 24) & 255;
		float r = (col32_no_alpha >> 16) & 255;
		float g = (col32_no_alpha >> 8) & 255;
		float b = col32_no_alpha & 255;
		return RGBA((int)r, (int)g, (int)b, (int)a);
	}

	std::string string_To_UTF8(const std::string& str)
	{
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

		wchar_t* pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory(pwBuf, nwLen * 2 + 2);

		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

		char* pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);

		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

		std::string retStr(pBuf);

		delete[]pwBuf;
		delete[]pBuf;

		pwBuf = NULL;
		pBuf = NULL;

		return retStr;
	}

	void DrawStrokeText(int x, int y, RGBA color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, color.A / 255.0)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, color.A / 255.0)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, color.A / 255.0)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, color.A / 255.0)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), utf_8_2.c_str());
	}
	void DrawNewText(int x, int y, RGBA* color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
	}
	void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
	}
	void DrawFilledRect(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
	}
	void DrawCircleFilled(int x, int y, int radius, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
	}
	void DrawCircle(int x, int y, int radius, RGBA* color, int segments)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
	}
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color, float thickne)
	{
		ImGui::GetOverlayDrawList()->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickne);
	}
	void DrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
	}
	void DrawLine(int x1, int y1, int x2, int y2, RGBA color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), thickness);
	}
	void DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color)
	{
		DrawFilledRect(x + borderPx, y, w / 3, borderPx, color); //top 
		DrawFilledRect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color); //top 
		DrawFilledRect(x, y, borderPx, h / 3, color); //left 
		DrawFilledRect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color); //left 
		DrawFilledRect(x + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
		DrawFilledRect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
		DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color);//right 
		DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);//right 
	}
	void DrawSkeleton(uintptr_t ped) {
		int bone_positions[][2] = {
			{ 0, 7 },
			{ 7, 6 },
			{ 7, 5 },
			{ 7, 8 },
			{ 8, 3 },
			{ 8, 4 }
		};

		for (int i = 0; i < 6; ++i) {
			ImVec2 screen_1, screen_2;
			auto bone_1 = SDK::Utils::getBone(ped, bone_positions[i][0]),
				bone_2 = SDK::Utils::getBone(ped, bone_positions[i][1]);
			screen_1 = SDK::Utils::WorldToScreen2(bone_1);
			screen_2 = SDK::Utils::WorldToScreen2(bone_2);
			if (bone_1.x != 0 && bone_1.y != 0 && bone_1.z != 0 &&
				bone_2.x != 0 && bone_2.y != 0 && bone_2.z != 0 &&
				screen_1.x != 0 && screen_1.y != 0 &&
				screen_2.x != 0 && screen_2.y != 0) {
				if (SDK::Utils::Distance(Vector3(screen_1.x, screen_1.y, 0.0f), Vector3(screen_2.x, screen_2.y, 0.0f)) < 6.0f)
					DrawLine(screen_1.x, screen_1.y, screen_2.x, screen_2.y, FLOAT4TORGBA(Config::ESP::f2DColor), 1);
			}
		}
	}
	void DrawMenu() 
	{
		ImGui::ShowDemoWindow();
		ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
		ImGui::SetNextWindowPos(center, ImGuiCond_Once, ImVec2(0.5f, 0.5f));
		ImGui::SetWindowSize(ImVec2(300, 500));
		ImGui::Begin(xorstr_("Menu"));
		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
		if (ImGui::BeginTabBar(xorstr_("merdaMenu"), tab_bar_flags))
		{
			if (ImGui::BeginTabItem(xorstr_("DEBUG")))
			{

				ImGui::Text((std::string(xorstr_("GTA version: b")) + std::to_string(SDK::Utils::GetGameBuild())).c_str());
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(xorstr_("Aimbot")))
			{

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(xorstr_("ESP")))
			{
				ImGui::Checkbox("2D Box", &Config::ESP::bShow2DBox);
				ImGui::SameLine();
				ImGui::ColorEdit4("2D Box Color", (float*)Config::ESP::f2DColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaBar);
				ImGui::Checkbox("Name", &Config::ESP::bShowName);
				ImGui::Checkbox("Health", &Config::ESP::bShowHealth);
				ImGui::Checkbox("Skeleton", &Config::ESP::bShowSkeleton);
				ImGui::Checkbox("Tracer", &Config::ESP::bShowTracer);
				
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(xorstr_("Chams")))
			{

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(xorstr_("Settings")))
			{

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ImGui::End();
	}
	void Draw()
	{
		if (MemoryMan::ValidPTR(SDK::Utils::World))
		{
			SDK::Utils::Tick();
			SDK::Utils::LocalPlayer = *(DWORD64*)(SDK::Utils::World + 0x8);
			if (SDK::Utils::LocalPlayer != NULL)
			{
				for (int i = 0; i < 1024; i++)
				{
					if (SDK::Utils::Players[i].ped == SDK::Utils::LocalPlayer)
						continue;

					Vector3 pedPos = Vector3(SDK::Utils::Players[i].position.x, SDK::Utils::Players[i].position.y, SDK::Utils::Players[i].position.z);

					/*if (Distance(SDK::PLAYER::Position(), pedPos) <= (Config::ESP::distance * 3))
						continue;*/

					if (pedPos.x == 0.0f || pedPos.y == 0.0f || pedPos.z == 0.0f)
						continue;

					float health = SDK::Utils::Players[i].health;
					if (health > 200.0f)    health = 200.0f;
					else if (health < 0.0f) health = 0.0f;

					float armor = SDK::Utils::Players[i].armor;
					if (armor > 100.0f)    armor = 100.0f;
					else if (armor < 0.0f) armor = 0.0f;

					Vector3 originPos = Vector3(pedPos.x, pedPos.y, pedPos.z - 1.0f);
					Vector3 headPos = Vector3(pedPos.x, pedPos.y, pedPos.z + 0.9f);

					ImVec2 screenPos = SDK::Utils::WorldToScreen(originPos);
					ImVec2 screenPosHead = SDK::Utils::WorldToScreen(headPos);

					ImVec2 localPlyScreenPos = SDK::Utils::WorldToScreen(SDK::Utils::Position());
					if (screenPos.x > 0 && screenPosHead.x > 0)
					{
						float h = screenPosHead.y - screenPos.y;
						float w = (screenPos.y - screenPosHead.y) / 3.5f;
						if (Config::ESP::bShow2DBox) {
							Graphics::Drawing::DrawLine(screenPos.x - w, screenPosHead.y, screenPos.x + w, screenPosHead.y, FLOAT4TORGBA(Config::ESP::f2DColor), 1);
							Graphics::Drawing::DrawLine(screenPos.x - w, screenPos.y, screenPos.x - w, screenPosHead.y, FLOAT4TORGBA(Config::ESP::f2DColor), 1);
							Graphics::Drawing::DrawLine(screenPos.x + w, screenPos.y, screenPos.x + w, screenPosHead.y, FLOAT4TORGBA(Config::ESP::f2DColor), 1);
							Graphics::Drawing::DrawLine(screenPos.x - w, screenPos.y, screenPos.x + w, screenPos.y, FLOAT4TORGBA(Config::ESP::f2DColor), 1);
						}
						if (Config::ESP::bShowName)
							Graphics::Drawing::DrawStrokeText(screenPos.x - (w / 2.5), screenPosHead.y, FLOAT4TORGBA(Config::ESP::f2DColor), std::to_string(SDK::Utils::Players[i].ped).c_str());
						if (Config::ESP::bShowSkeleton)
							DrawSkeleton(SDK::Utils::Players[i].ped);
						if (Config::ESP::bShowTracer)
							Graphics::Drawing::DrawLine(localPlyScreenPos.x, localPlyScreenPos.y, screenPos.x, screenPos.y + (h * 0.5), FLOAT4TORGBA(Config::ESP::f2DColor), 1);
						if (Config::ESP::bShowHealth)
						{
							Graphics::Drawing::DrawStrokeText(screenPos.x - (w / 2.5), screenPosHead.y, FLOAT4TORGBA(Config::ESP::f2DColor), std::to_string(SDK::Utils::Players[i].health).c_str());
							float flBarlenght = ((SDK::Utils::Players[i].health * (h - 2)) / 100) + 2;
							Graphics::Drawing::DrawRect((screenPos.x - 1) - 4, screenPos.y - 1, 3 + 2, h + 2, &Graphics::Drawing::Col.black, 1);
							Graphics::Drawing::DrawRect((screenPos.x + 1) - 4, screenPos.y + 1, 3 - 2, h - 2, &Graphics::Drawing::Col.black, 1);
							RGBA colHealth = { 255 - 2.55 * (SDK::Utils::Players[i].health), 2.55 * (SDK::Utils::Players[i].health), 0, 255 };
							Graphics::Drawing::DrawFilledRect(screenPos.x - 4, screenPos.y + (h - flBarlenght), 3, flBarlenght, &colHealth);
							/*client.surface->SetDrawColor(0, 0, 0);
							client.surface->DrawOutlined((x - 1) - 4, y - 1, 3 + 2, h + 2);
							client.surface->DrawOutlined((x + 1) - 4, y + 1, 3 - 2, h - 2);
							client.surface->SetDrawColor(255 - 2.55 * (m_iHealth), 2.55 * (m_iHealth), 0);
							client.surface->DrawRect(x - 4, y + (h - flBarlenght), 3, flBarlenght); */
						}
					}
				}
			}
		}
	}
}