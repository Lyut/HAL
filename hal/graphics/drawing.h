#pragma once
#include <string>
#include <DirectXMath.h>
#include "../includes.h"
#include "../graphics/imgui.h"
#include "../graphics/imgui_impl_dx11.h"
#include "../graphics/imgui_internal.h"
#include "../sdk/utils.h"
#include "../sdk/game.h"
#include "../hooks.h"
#include "../config.h"

static bool selection[29] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };

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
		float r = col32_no_alpha & 255;
		float b = (col32_no_alpha >> 16) & 255;
		float g = (col32_no_alpha >> 8) & 255;
		float a = (col32_no_alpha >> 24) & 255;
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
	void DrawRect(int x, int y, int w, int h, RGBA color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), 0, 0, thickness);
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
	void Barrel(Vector3 HeadPos, Vector3 Rotation, const float trailLen = 10.0f) {
		float rot = acosf(Rotation.x) * 180.0f / DirectX::XM_PI;
		if (asinf(Rotation.y) * 180.0f / DirectX::XM_PI < 0.0f) rot *= -1.0f;

		auto ForwardDirection = DirectX::XMConvertToRadians(rot);
		Vector3 forwardVec(cosf(ForwardDirection), sinf(ForwardDirection), 0.0f);
		Vector3 screenOrigin, screenTrail, trailEnd;

		Vector3 trail(forwardVec.x * trailLen, forwardVec.y * trailLen, forwardVec.z * trailLen);
		trailEnd = Vector3(trail.x + HeadPos.x, trail.y + HeadPos.y, trail.z + HeadPos.z);

		ImVec2 screen_origin = SDK::Game::WorldToScreen(HeadPos);
		ImVec2 screen_trail = SDK::Game::WorldToScreen(trailEnd);

		if (screen_origin.x != 0 && screen_origin.y != 0 &&
			screen_trail.x != 0 && screen_trail.y != 0) {
			DrawLine(screenOrigin.x, screenOrigin.y, screenTrail.x, screenTrail.y, FLOAT4TORGBA(Config::Colors::f2DColor), 1);
		}
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
			auto bone_1 = SDK::Game::getBone(ped, bone_positions[i][0]),
				bone_2 = SDK::Game::getBone(ped, bone_positions[i][1]);
			screen_1 = SDK::Game::WorldToScreen2(bone_1);
			screen_2 = SDK::Game::WorldToScreen2(bone_2);
			if (bone_1.x != 0 && bone_1.y != 0 && bone_1.z != 0 &&
				bone_2.x != 0 && bone_2.y != 0 && bone_2.z != 0 &&
				screen_1.x != 0 && screen_1.y != 0 &&
				screen_2.x != 0 && screen_2.y != 0) {
				//if (SDK::Utils::Distance(Vector3(screen_1.x, screen_1.y, 0.0f), Vector3(screen_2.x, screen_2.y, 0.0f)) > 70.0f)
				if (SDK::Game::Distance(Vector3(screen_1.x, screen_1.y, 0.0f), Vector3(screen_2.x, screen_2.y, 0.0f)) < 900)
					DrawLine(screen_1.x, screen_1.y, screen_2.x, screen_2.y, FLOAT4TORGBA(Config::Colors::fSkeletonColor), 1);
			}
		}
	}
	void DrawMenu()
	{
		ImGui::ShowDemoWindow();
		ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.6f);
		ImGui::SetNextWindowPos(center, ImGuiCond_Once, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize(ImVec2(355, 345), ImGuiCond_Once);
		ImGui::Begin(xorstr_("lewd.vip"));
		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll;
		if (ImGui::BeginTabBar(xorstr_("merdaMenu"), tab_bar_flags))
		{
			if (ImGui::BeginTabItem(xorstr_("DEBUG")))
			{
				if (SDK::Game::hAsiFive)
					ImGui::Text((std::string(xorstr_("GTA version: b")) + std::to_string(SDK::Game::GetGameBuild())).c_str());
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(xorstr_("aimbot")))
			{

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(xorstr_("visuals")))
			{
				ImGuiTabBarFlags color_picker_flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoLabel;
				ImGui::Text("Ctrl+LClick to type");
				ImGui::SliderFloat(xorstr_("Range"), &Config::ESP::fDistance, 0, 2500, Config::ESP::fDistance == 1.0f ? xorstr_("%.0f meter") : xorstr_("%.0f meters"));
				ImGui::Columns(2, NULL, true);
				ImGui::ColorEdit4(xorstr_("2D Box Color"), (float*)Config::Colors::f2DColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("2D Box"), &Config::ESP::bShow2DBox);
				ImGui::ColorEdit4(xorstr_("Name Color"), (float*)Config::Colors::fNameColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("Name"), &Config::ESP::bShowName);
				ImGui::ColorEdit4(xorstr_("Distance Color"), (float*)Config::Colors::fDistanceColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("Distance"), &Config::ESP::bShowDistance);
				ImGui::ColorEdit4(xorstr_("Skeleton Color"), (float*)Config::Colors::fSkeletonColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("Skeleton"), &Config::ESP::bShowSkeleton);
				ImGui::ColorEdit4(xorstr_("Tracer Color"), (float*)Config::Colors::fTracerColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("Tracer"), &Config::ESP::bShowTracer);
				ImGui::NextColumn();
				ImGui::Checkbox(xorstr_("Health"), &Config::ESP::bShowHealth);
				ImGui::Checkbox(xorstr_("Armor"), &Config::ESP::bShowArmor);
				ImGui::EndColumns();
				//if (ImGui::TreeNode("Show:"))
				//{
				//	ImGui::Selectable("PLAYER_0", &selection[0]);
				//	ImGui::Selectable("PLAYER_1", &selection[1]);
				//	ImGui::Selectable("NETWORK_PLAYER", &selection[2]);
				//	ImGui::Selectable("PLAYER_2", &selection[3]);
				//	ImGui::Selectable("CIVMALE", &selection[4]);
				//	ImGui::Selectable("CIVFEMALE", &selection[5]);
				//	ImGui::Selectable("COP", &selection[6]);
				//	ImGui::Selectable("GANG_ALBANIAN", &selection[7]);
				//	ImGui::Selectable("GANG_BIKER_1", &selection[8]);
				//	ImGui::Selectable("GANG_BIKER_2", &selection[9]);
				//	ImGui::Selectable("GANG_ITALIAN", &selection[10]);
				//	ImGui::Selectable("GANG_RUSSIAN", &selection[11]);
				//	ImGui::Selectable("GANG_RUSSIAN_2", &selection[12]);
				//	ImGui::Selectable("GANG_IRISH", &selection[13]);
				//	ImGui::Selectable("GANG_JAMAICAN", &selection[14]);
				//	ImGui::Selectable("GANG_AFRICAN_AMERICAN", &selection[15]);
				//	ImGui::Selectable("GANG_KOREAN", &selection[16]);
				//	ImGui::Selectable("GANG_CHINESE_JAPANESE", &selection[17]);
				//	ImGui::Selectable("GANG_PUERTO_RICAN", &selection[18]);
				//	ImGui::Selectable("DEALER", &selection[19]);
				//	ImGui::Selectable("MEDIC", &selection[20]);
				//	ImGui::Selectable("FIREMAN", &selection[21]);
				//	ImGui::Selectable("CRIMINAL", &selection[22]);
				//	ImGui::Selectable("BUM", &selection[23]);
				//	ImGui::Selectable("PROSTITUTE", &selection[24]);
				//	ImGui::Selectable("SPECIAL", &selection[25]);
				//	ImGui::Selectable("MISSION", &selection[26]);
				//	ImGui::Selectable("SWAT", &selection[27]);
				//	ImGui::Selectable("ANIMAL", &selection[28]);
				//	ImGui::Selectable("ARMY", &selection[29]);
				//	ImGui::TreePop();
				//}

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(xorstr_("settings")))
			{
				ImGui::Columns(3, NULL, false);
				ImGui::NextColumn();
				if (ImGui::Button(xorstr_("   load  ")))
					SDK::Utils::LoadConfig();
				if (ImGui::Button(xorstr_("   save  ")))
					SDK::Utils::SaveConfig();
				if (ImGui::Button(xorstr_("   reset ")))
					SDK::Utils::ResetConfig();
				ImGui::NextColumn();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ImGui::End();
	}
	void Draw()
	{
		if (MemoryMan::ValidPTR(SDK::Game::World))
		{
			SDK::Game::Tick();
			SDK::Game::LocalPlayer = *(DWORD64*)(SDK::Game::World + 0x8);
			if (SDK::Game::LocalPlayer != NULL)
			{
				for (int i = 0; i < 1024; i++)
				{
					if (SDK::Game::Players[i].ped == NULL)
						continue;

					//if (SDK::Game::Players[i].ped == SDK::Game::LocalPlayer)
					//	continue;

					printf("0x%p\n", SDK::Game::LocalPlayer);
					Vector3 pedPos = Vector3(SDK::Game::Players[i].position.x, SDK::Game::Players[i].position.y, SDK::Game::Players[i].position.z);

					//if (Distance(SDK::PLAYER::Position(), pedPos) <= (Config::ESP::distance * 3))
					//	continue

					if (SDK::Game::Distance(SDK::Game::Position(), pedPos) >= Config::ESP::fDistance) // to meters
						continue;

					//if (pedPos.x == 0.0f || pedPos.y == 0.0f || pedPos.z == 0.0f)
					//	continue;

					//if (!selection[SDK::Game::Players[i].ped_type])
					//	continue;

					Vector3 originPos = Vector3(pedPos.x, pedPos.y, pedPos.z - 1.0f);
					Vector3 headPos = Vector3(pedPos.x, pedPos.y, pedPos.z + 0.9f);

					ImVec2 screenPos = SDK::Game::WorldToScreen(originPos);
					ImVec2 screenPosHead = SDK::Game::WorldToScreen(headPos);

					ImVec2 localPlyScreenPos = SDK::Game::WorldToScreen(SDK::Game::Position());
					if (screenPos.x > 0 && screenPosHead.x > 0)
					{
						float h = screenPosHead.y - screenPos.y;
						float w = (screenPos.y - screenPosHead.y) / 3.5f;
						if (Config::ESP::bShow2DBox) {
							Graphics::Drawing::DrawLine(screenPos.x - w, screenPosHead.y, screenPos.x + w, screenPosHead.y, FLOAT4TORGBA(Config::Colors::f2DColor), 1);
							Graphics::Drawing::DrawLine(screenPos.x - w, screenPos.y, screenPos.x - w, screenPosHead.y, FLOAT4TORGBA(Config::Colors::f2DColor), 1);
							Graphics::Drawing::DrawLine(screenPos.x + w, screenPos.y, screenPos.x + w, screenPosHead.y, FLOAT4TORGBA(Config::Colors::f2DColor), 1);
							Graphics::Drawing::DrawLine(screenPos.x - w, screenPos.y, screenPos.x + w, screenPos.y, FLOAT4TORGBA(Config::Colors::f2DColor), 1);

							//Graphics::Drawing::DrawStrokeText(screenPos.x - w, screenPosHead.y, FLOAT4TORGBA(Config::ESP::f2DColor), "a");
							//Graphics::Drawing::DrawStrokeText(screenPos.x + w, screenPosHead.y, FLOAT4TORGBA(Config::ESP::f2DColor), "b");
							//Graphics::Drawing::DrawStrokeText(screenPos.x + w, screenPos.y, FLOAT4TORGBA(Config::ESP::f2DColor), "c");
							//Graphics::Drawing::DrawStrokeText(screenPos.x - w, screenPos.y, FLOAT4TORGBA(Config::ESP::f2DColor), "d");
						}
						if (Config::ESP::bShowHealth)
						{
							float flBarlenght = ((SDK::Game::Players[i].health * (h - 2)) / SDK::Game::Players[i].maxHealth) + 2;
							if (SDK::Game::Players[i].health < 1)
								flBarlenght = 0;
							Graphics::Drawing::DrawRect(((screenPos.x - 1) + 4) + w, screenPos.y - 1, 3 + 2, h + 2, Graphics::Drawing::Col.black, 1);
							Graphics::Drawing::DrawRect(((screenPos.x + 1) + 4) + w, screenPos.y + 1, 3 - 2, h - 2, Graphics::Drawing::Col.black, 1);
							RGBA colHealth = { 255 - (255 / SDK::Game::Players[i].maxHealth) * (SDK::Game::Players[i].health), (255 / SDK::Game::Players[i].maxHealth) * (SDK::Game::Players[i].health), 0, 255 };
							Graphics::Drawing::DrawFilledRect((screenPos.x + 4) + w, screenPos.y, 3, flBarlenght, &colHealth);
						}
						if (Config::ESP::bShowArmor)
						{
							if (SDK::Game::Players[i].armor > 0)
							{
								float flBarlenght = ((SDK::Game::Players[i].armor * (h - 2)) / 50) + 2;
								Graphics::Drawing::DrawRect(((screenPos.x - 1) + 8) + w, screenPos.y - 1, 3 + 2, h + 2, Graphics::Drawing::Col.black, 1);
								Graphics::Drawing::DrawRect(((screenPos.x + 1) + 8) + w, screenPos.y + 1, 3 - 2, h - 2, Graphics::Drawing::Col.black, 1);
								RGBA colArmor = { 255 - (255 / 50) * (SDK::Game::Players[i].armor), 0, (255 / 50) * (SDK::Game::Players[i].armor), 255 };
								Graphics::Drawing::DrawFilledRect((screenPos.x + 8) + w, screenPos.y, 3, flBarlenght, &colArmor);
							}
						}
						if (Config::ESP::bShowName)
							Graphics::Drawing::DrawStrokeText(screenPos.x + w + 4, screenPosHead.y - 4, FLOAT4TORGBA(Config::Colors::fNameColor), std::to_string(SDK::Game::Players[i].ped).c_str());
						//unsigned int test = SDK::Game::Players[i].ped_type << 11 >> 25;
						//Graphics::Drawing::DrawStrokeText(screenPos.x + w + 4, screenPosHead.y + 16, FLOAT4TORGBA(Config::Colors::fNameColor), std::to_string(test).c_str());
						if (Config::ESP::bShowDistance)
						{
							int iDistance = SDK::Game::Distance(SDK::Game::Position(), pedPos);
							std::string sDistance("[" + std::to_string(iDistance) + "m]");
							Graphics::Drawing::DrawStrokeText(screenPos.x + w + 4, screenPosHead.y + 8, FLOAT4TORGBA(Config::Colors::fDistanceColor), sDistance.c_str());
						}
						if (Config::ESP::bShowSkeleton)
							DrawSkeleton(SDK::Game::Players[i].ped);
						if (Config::ESP::bShowTracer)
							Barrel(headPos, SDK::Game::Players[i]._ObjectNavigation, 5.0f);
						if (Config::ESP::bShowHeading)
						{

						}
					}
				}
			}
		}
	}
}