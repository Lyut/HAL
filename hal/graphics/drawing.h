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
		DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color); //right 
		DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color); //right 
	}
	void Barrel(Vector3 HeadPos, Vector3 Rotation, const float trailLen = 10.0f) {
		float rot = acosf(Rotation.x) * 180.0f / DirectX::XM_PI;
		if (asinf(Rotation.y) * 180.0f / DirectX::XM_PI < 0.0f) rot *= -1.0f;

		auto ForwardDirection = DirectX::XMConvertToRadians(rot);
		Vector3 forwardVec(cosf(ForwardDirection), sinf(ForwardDirection), 0.0f);
		Vector3 screenOrigin, screenTrail, trailEnd;

		Vector3 trail(forwardVec.x * trailLen, forwardVec.y * trailLen, forwardVec.z * trailLen);
		trailEnd = trail + HeadPos;
		ImVec2 screen_1, screen_2;
		screen_1 = SDK::Game::WorldToScreen(HeadPos);
		screen_2 = SDK::Game::WorldToScreen(trailEnd);

		if (screen_1.x > 0 && screen_1.y > 0 &&
			screen_2.x > 0 && screen_2.y > 0) {
			DrawLine(screen_1.x, screen_1.y, screen_2.x, screen_2.y, FLOAT4TORGBA(Config::Colors::fBarrelColor), 1);
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

			if (bone_1.x > 0 && bone_1.y > 0 && bone_1.z > 0 &&
				bone_2.x > 0 && bone_2.y > 0 && bone_2.z > 0 &&
				screen_1.x > 0 && screen_1.y > 0 &&
				screen_2.x > 0 && screen_2.y > 0) {
				DrawLine(screen_1.x, screen_1.y, screen_2.x, screen_2.y, FLOAT4TORGBA(Config::Colors::fSkeletonColor), 1);
			}
		}
	}
	bool Draw3DBox(Vector3 Position, Vector3 Rotation, Vector3 Origin)
	{
		float rot = acosf(Rotation.x) * 180.0f / DirectX::XM_PI;
		if (asinf(Rotation.y) * 180.0f / DirectX::XM_PI < 0.0f) rot *= -1.0f;

		Vector3 HeadPos = Vector3(Position.x, Position.y, Position.z);
		Vector3 FeetPos = Vector3(Origin.x, Origin.y, Origin.z);

		Vector3 t[8];
		ImVec2 screen_1, screen_2, screen_3, screen_4, screen_5, screen_6, screen_7, screen_8;

		Vector4 Cosines;
		Vector4 Sines;
		Vector4 Corners = Vector4(DirectX::XMConvertToRadians(rot - 45.0f), DirectX::XMConvertToRadians(rot - 135.0f), DirectX::XMConvertToRadians(rot + 45.0f), DirectX::XMConvertToRadians(rot + 135.0f));
		Cosines.x = cosf(Corners.x);
		Cosines.y = cosf(Corners.y);
		Cosines.z = cosf(Corners.z);
		Cosines.w = cosf(Corners.w);
		Sines.x = sinf(Corners.x);
		Sines.y = sinf(Corners.y);
		Sines.z = sinf(Corners.z);
		Sines.w = sinf(Corners.w);

		float radius = 0.5f;

		Vector3 HeadLeftForward = HeadPos + Vector3(Cosines.x * radius, Sines.x * radius, 0.0f);
		Vector3 HeadLeftBackward = HeadPos + Vector3(Cosines.y * radius, Sines.y * radius, 0.0f);
		Vector3 HeadRightForward = HeadPos + Vector3(Cosines.z * radius, Sines.z * radius, 0.0f);
		Vector3 HeadRightBackward = HeadPos + Vector3(Cosines.w * radius, Sines.w * radius, 0.0f);

		Vector3 FeetLeftForward = FeetPos + Vector3(Cosines.x * radius, Sines.x * radius, 0.0f);
		Vector3 FeetLeftBackward = FeetPos + Vector3(Cosines.y * radius, Sines.y * radius, 0.0f);
		Vector3 FeetRightForward = FeetPos + Vector3(Cosines.z * radius, Sines.z * radius, 0.0f);
		Vector3 FeetRightBackward = FeetPos + Vector3(Cosines.w * radius, Sines.w * radius, 0.0f);

		screen_1 = SDK::Game::WorldToScreen(HeadLeftForward);
		screen_2 = SDK::Game::WorldToScreen(HeadLeftBackward);
		screen_3 = SDK::Game::WorldToScreen(HeadRightBackward);
		screen_4 = SDK::Game::WorldToScreen(HeadRightForward);
		screen_5 = SDK::Game::WorldToScreen(FeetLeftForward);
		screen_6 = SDK::Game::WorldToScreen(FeetLeftBackward);
		screen_7 = SDK::Game::WorldToScreen(FeetRightBackward);
		screen_8 = SDK::Game::WorldToScreen(FeetRightForward);
		t[0].x = screen_1.x; t[0].y = screen_1.y;
		t[1].x = screen_2.x; t[1].y = screen_2.y;
		t[2].x = screen_3.x; t[2].y = screen_3.y;
		t[3].x = screen_4.x; t[3].y = screen_4.y;
		t[4].x = screen_5.x; t[4].y = screen_5.y;
		t[5].x = screen_6.x; t[5].y = screen_6.y;
		t[6].x = screen_7.x; t[6].y = screen_7.y;
		t[7].x = screen_8.x; t[7].y = screen_8.y;

		if (screen_1.x > 0 && screen_1.y > 0 &&
			screen_2.x > 0 && screen_2.y > 0 &&
			screen_3.x > 0 && screen_3.y > 0 &&
			screen_4.x > 0 && screen_4.y > 0)
		{
			if (screen_5.x > 0 && screen_5.y > 0 &&
				screen_6.x > 0 && screen_6.y > 0 &&
				screen_7.x > 0 && screen_7.y > 0 &&
				screen_8.x > 0 && screen_8.y > 0)
			{

				for (int i = 0; i < 4; i++)
				{
					DrawLine(t[i].x, t[i].y, t[i + 4].x, t[i + 4].y, FLOAT4TORGBA(Config::Colors::f3DColor), 1);

					if (i != 3) DrawLine(t[i].x, t[i].y, t[i + 1].x, t[i + 1].y, FLOAT4TORGBA(Config::Colors::f3DColor), 1);
					else DrawLine(t[3].x, t[3].y, t[0].x, t[0].y, FLOAT4TORGBA(Config::Colors::f3DColor), 1);
				}

				for (int i = 4; i < 8; i++)
				{
					if (i != 7) DrawLine(t[i].x, t[i].y, t[i + 1].x, t[i + 1].y, FLOAT4TORGBA(Config::Colors::f3DColor), 1);
					else DrawLine(t[7].x, t[7].y, t[4].x, t[4].y, FLOAT4TORGBA(Config::Colors::f3DColor), 1);
				}
			}
		}
		return true;
	}
	void DrawMenu()
	{
		ImGui::ShowDemoWindow();
		ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.6f);
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize(ImVec2(365, 400), ImGuiCond_Appearing);
		ImGui::Begin(xorstr_("lewd.vip"));
		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll;
		if (ImGui::BeginTabBar(xorstr_("merdaMenu"), tab_bar_flags))
		{
			if (ImGui::BeginTabItem(xorstr_("visuals")))
			{
				ImGuiTabBarFlags color_picker_flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoLabel;
				ImGui::Text("Ctrl+LClick to type");
				ImGui::SliderFloat(xorstr_("range"), &Config::ESP::fDistance, 0, 2500, Config::ESP::fDistance == 1.0f ? xorstr_("%.0f meter") : xorstr_("%.0f meters"));
				ImGui::Columns(2, NULL, true);
				ImGui::ColorEdit4(xorstr_("2D box color"), (float*)Config::Colors::f2DColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("2D box"), &Config::ESP::bShow2DBox);
				ImGui::ColorEdit4(xorstr_("3D Box color"), (float*)Config::Colors::f3DColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("3D box"), &Config::ESP::bShow3DBox);
				ImGui::ColorEdit4(xorstr_("skeleton color"), (float*)Config::Colors::fSkeletonColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("skeleton"), &Config::ESP::bShowSkeleton);
				ImGui::ColorEdit4(xorstr_("tracer color"), (float*)Config::Colors::fTracerColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("tracer"), &Config::ESP::bShowTracer);
				ImGui::NextColumn();
				ImGui::ColorEdit4(xorstr_("name color"), (float*)Config::Colors::fNameColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("name"), &Config::ESP::bShowName);
				ImGui::ColorEdit4(xorstr_("distance color"), (float*)Config::Colors::fDistanceColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("distance"), &Config::ESP::bShowDistance);
				ImGui::ColorEdit4(xorstr_("barrel color"), (float*)Config::Colors::fBarrelColor, color_picker_flags);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr_("barrel"), &Config::ESP::bShowBarrel);
				ImGui::Checkbox(xorstr_("health"), &Config::ESP::bShowHealth);
				ImGui::Checkbox(xorstr_("armor"), &Config::ESP::bShowArmor);
				ImGui::EndColumns();
				ImGui::Checkbox(xorstr_("draw NPCs"), &Config::ESP::bDrawNPC);
				ImGui::Checkbox(xorstr_("draw local"), &Config::ESP::bDrawLocal);
				if (ImGui::TreeNode(xorstr_("show:")))
				{
					ImGui::Selectable(xorstr_("MICHAEL"), &Config::PedSelection[0]);
					ImGui::Selectable(xorstr_("FRANKLIN"), &Config::PedSelection[1]);
					ImGui::Selectable(xorstr_("NETWORK_PLAYER"), &Config::PedSelection[2]);
					ImGui::Selectable(xorstr_("TREVOR"), &Config::PedSelection[3]);
					ImGui::Selectable(xorstr_("CIVMALE"), &Config::PedSelection[4]);
					ImGui::Selectable(xorstr_("CIVFEMALE"), &Config::PedSelection[5]);
					ImGui::Selectable(xorstr_("COP"), &Config::PedSelection[6]);
					ImGui::Selectable(xorstr_("GANG_ALBANIAN"), &Config::PedSelection[7]);
					ImGui::Selectable(xorstr_("GANG_BIKER_1"), &Config::PedSelection[8]);
					ImGui::Selectable(xorstr_("GANG_BIKER_2"), &Config::PedSelection[9]);
					ImGui::Selectable(xorstr_("GANG_ITALIAN"), &Config::PedSelection[10]);
					ImGui::Selectable(xorstr_("GANG_RUSSIAN"), &Config::PedSelection[11]);
					ImGui::Selectable(xorstr_("GANG_RUSSIAN_2"), &Config::PedSelection[12]);
					ImGui::Selectable(xorstr_("GANG_IRISH"), &Config::PedSelection[13]);
					ImGui::Selectable(xorstr_("GANG_JAMAICAN"), &Config::PedSelection[14]);
					ImGui::Selectable(xorstr_("GANG_AFRICAN_AMERICAN"), &Config::PedSelection[15]);
					ImGui::Selectable(xorstr_("GANG_KOREAN"), &Config::PedSelection[16]);
					ImGui::Selectable(xorstr_("GANG_CHINESE_JAPANESE"), &Config::PedSelection[17]);
					ImGui::Selectable(xorstr_("GANG_PUERTO_RICAN"), &Config::PedSelection[18]);
					ImGui::Selectable(xorstr_("DEALER"), &Config::PedSelection[19]);
					ImGui::Selectable(xorstr_("MEDIC"), &Config::PedSelection[20]);
					ImGui::Selectable(xorstr_("FIREMAN"), &Config::PedSelection[21]);
					ImGui::Selectable(xorstr_("CRIMINAL"), &Config::PedSelection[22]);
					ImGui::Selectable(xorstr_("BUM"), &Config::PedSelection[23]);
					ImGui::Selectable(xorstr_("PROSTITUTE"), &Config::PedSelection[24]);
					ImGui::Selectable(xorstr_("SPECIAL"), &Config::PedSelection[25]);
					ImGui::Selectable(xorstr_("MISSION"), &Config::PedSelection[26]);
					ImGui::Selectable(xorstr_("SWAT"), &Config::PedSelection[27]);
					ImGui::Selectable(xorstr_("ANIMAL"), &Config::PedSelection[28]);
					ImGui::Selectable(xorstr_("ARMY"), &Config::PedSelection[29]);
					ImGui::TreePop();
				}

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(xorstr_("aimbot")))
			{
				ImGui::SliderInt(xorstr_("FOV"), &Config::Aimbot::iFOV, 100, 300, Config::Aimbot::iFOV == 1 ? xorstr_("%d degree") : xorstr_("%d degrees"));
				ImGui::Checkbox(xorstr_("enabled"), &Config::Aimbot::bEnabled);
				ImGui::Checkbox(xorstr_("smooth"), &Config::Aimbot::bSmoothEnabled);
				ImGui::SliderInt(xorstr_("smoothness"), &Config::Aimbot::iSmoothness, 0, 30);
				const char* bones[] = { "head", "neck", "stomach", "left hand", "right hand", "left leg", "right leg", "left foot", "right foot" };
				ImGui::Combo("aim bone", &Config::Aimbot::iAimBone, bones, IM_ARRAYSIZE(bones));

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(xorstr_("misc")))
			{
				if (SDK::Game::hAsiFive)
					ImGui::Text((std::string(xorstr_("GTA version: b")) + std::to_string(SDK::Game::GetGameBuild())).c_str());

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
					if (SDK::Game::Players[i].Ped == NULL)
						continue;

					if (SDK::Game::Players[i].Ped == SDK::Game::LocalPlayer && !Config::ESP::bDrawLocal)
						continue;

					Vector3 pedPos = Vector3(SDK::Game::Players[i].Position.x, SDK::Game::Players[i].Position.y, SDK::Game::Players[i].Position.z);

					if (SDK::Game::Distance(SDK::Game::Position(), pedPos) >= Config::ESP::fDistance) // to meters
						continue;

					if (SDK::Game::Players[i].PedType != SDK::Game::ped_types::NETWORK_PLAYER && !Config::ESP::bDrawNPC)
						continue;

					if (!Config::PedSelection[SDK::Game::Players[i].PedType])
						continue;

					if (SDK::Game::Players[i].Health < 1)
						continue;

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
						}
						if (Config::ESP::bShow3DBox)
							Draw3DBox(headPos, SDK::Game::Players[i].ObjectNavigation->Rotation, originPos);
						if (Config::ESP::bShowHealth)
						{
							float flBarlenght = ((SDK::Game::Players[i].Health * (h - 2)) / SDK::Game::Players[i].MaxHealth) + 2;
							if (SDK::Game::Players[i].Health < 1)
								flBarlenght = 0;
							Graphics::Drawing::DrawRect(((screenPos.x - 1) + 4) + w, screenPos.y - 1, 3 + 2, h + 2, Graphics::Drawing::Col.black, 1);
							Graphics::Drawing::DrawRect(((screenPos.x + 1) + 4) + w, screenPos.y + 1, 3 - 2, h - 2, Graphics::Drawing::Col.black, 1);
							RGBA colHealth = { 255 - (255 / SDK::Game::Players[i].MaxHealth) * (SDK::Game::Players[i].Health), (255 / SDK::Game::Players[i].MaxHealth) * (SDK::Game::Players[i].Health), 0, 255 };
							Graphics::Drawing::DrawFilledRect((screenPos.x + 4) + w, screenPos.y, 3, flBarlenght, &colHealth);
						}
						if (Config::ESP::bShowArmor)
						{
							if (SDK::Game::Players[i].Armor > 0)
							{
								float flBarlenght = ((SDK::Game::Players[i].Armor * (h - 2)) / 50) + 2;
								Graphics::Drawing::DrawRect(((screenPos.x - 1) + 8) + w, screenPos.y - 1, 3 + 2, h + 2, Graphics::Drawing::Col.black, 1);
								Graphics::Drawing::DrawRect(((screenPos.x + 1) + 8) + w, screenPos.y + 1, 3 - 2, h - 2, Graphics::Drawing::Col.black, 1);
								RGBA colArmor = { 255 - (255 / 50) * (SDK::Game::Players[i].Armor), 0, (255 / 50) * (SDK::Game::Players[i].Armor), 255 };
								Graphics::Drawing::DrawFilledRect((screenPos.x + 8) + w, screenPos.y, 3, flBarlenght, &colArmor);
							}
						}
						if (Config::ESP::bShowName)
							Graphics::Drawing::DrawStrokeText(screenPos.x + w + 4, screenPosHead.y - 4, FLOAT4TORGBA(Config::Colors::fNameColor), std::to_string(SDK::Game::Players[i].Ped).c_str());
						if (Config::ESP::bShowDistance)
						{
							int iDistance = SDK::Game::Distance(SDK::Game::Position(), pedPos);
							std::string sDistance("[" + std::to_string(iDistance) + "m]");
							Graphics::Drawing::DrawStrokeText(screenPos.x + w + 4, screenPosHead.y + 8, FLOAT4TORGBA(Config::Colors::fDistanceColor), sDistance.c_str());
						}
						if (Config::ESP::bShowSkeleton)
							DrawSkeleton(SDK::Game::Players[i].Ped);
						if (Config::ESP::bShowTracer)
							Graphics::Drawing::DrawLine(localPlyScreenPos.x > 0 ? localPlyScreenPos.x : ImGui::GetIO().DisplaySize.x * 0.5f,
								localPlyScreenPos.y > 0 ? localPlyScreenPos.y : ImGui::GetIO().DisplaySize.y * 0.6f,
								screenPos.x, screenPos.y + (h * 0.5), FLOAT4TORGBA(Config::Colors::fTracerColor), 1);
						if (Config::ESP::bShowBarrel)
						{
							auto boneNeck = SDK::Game::getBone(SDK::Game::Players[i].Ped, 0);
							Vector3 v3NeckPos = Vector3(boneNeck.x, boneNeck.y, boneNeck.z);
							Barrel(v3NeckPos, SDK::Game::Players[i].ObjectNavigation->Rotation, 3.0f);
						}
					}
				}
			}
		}
	}
}