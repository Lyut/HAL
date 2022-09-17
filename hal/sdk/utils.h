#pragma once
#include <cstddef>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <shlobj.h>
#include <Shlwapi.h>
#include "../memoryman.h"
#include "vec3.h"
#include "../config.h"
//test

namespace HAL::SDK::Utils {

	bool bDoOnce = 0;
	std::string Path;
	std::string ConfigPath;

	SIZE_T GetPointerAddress(SIZE_T Address, UINT Offset)
	{
		if (Address == 0)
			return 0;

		if (sizeof(SIZE_T) == 8)
			return Address + (INT)((*(INT*)(Address + Offset) + Offset) + sizeof(INT));

		return (SIZE_T) * (DWORD*)(Address + Offset);
	}

	inline void RemoveSpaces(std::string* s)
	{
		s->erase(std::remove_if(s->begin(), s->end(), ::isspace), s->end());
	}

	inline int ConfigParseInt(std::string str, int defaultt)
	{
		try {
			RemoveSpaces(&str);
			return std::stoi(str);
		}
		catch (...) {
			return defaultt;
		}
	}

	inline float ConfigParseFloat(std::string str, float defaultt)
	{
		try {
			RemoveSpaces(&str);
			return std::stoi(str);
		}
		catch (...) {
			return defaultt;
		}
	}

	inline bool ConfigParseBool(std::string str, bool defaultt)
	{
		try {
			bool x = defaultt;
			RemoveSpaces(&str);
			std::istringstream(str) >> std::boolalpha >> x;
			return x;
		}
		catch (...) {
			return defaultt;
		}
	}

	void ParseSettings()
	{
#pragma region wrappit stuff
		Config::ESP::bShowName = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowName")), false);
		Config::ESP::bShow2DBox = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("Show2DBox")), false);
		Config::ESP::bShow3DBox = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("Show3DBox")), false);
		Config::ESP::bShowArmor = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowArmor")), false);
		Config::ESP::bShowBarrel = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowBarrel")), false);
		Config::ESP::bShowDistance = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowDistance")), false);
		Config::ESP::bShowHealth = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowHealth")), false);
		Config::ESP::bShowSkeleton = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowSkeleton")), false);
		Config::ESP::bShowTracer = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowTracer")), false);
		Config::ESP::bDrawNPC = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("DrawNPC")), false);
		Config::ESP::fDistance = ConfigParseInt(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("Distance")), 2500);

		Config::Colors::f2DColor[0] = ConfigParseFloat(Config::ConfigIni.GetValue(xorstr_("ESPColors"), xorstr_("2DBoxR")), 1);
		Config::Colors::f2DColor[1] = ConfigParseFloat(Config::ConfigIni.GetValue(xorstr_("ESPColors"), xorstr_("2DBoxG")), 0.15f);
		Config::Colors::f2DColor[2] = ConfigParseFloat(Config::ConfigIni.GetValue(xorstr_("ESPColors"), xorstr_("2DBoxB")), 0.15f);
		Config::Colors::f2DColor[3] = ConfigParseFloat(Config::ConfigIni.GetValue(xorstr_("ESPColors"), xorstr_("2DBoxA")), 1);
#pragma endregion
	}

	void InitConfig() {
		[[likely]]
		if (!bDoOnce) {
			char Documents[MAX_PATH];
			SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, Documents);

			Path += std::string(Documents) + "\\lewd";

			if (!PathIsDirectoryA(Path.c_str()))
				CreateDirectoryA(Path.c_str(), 0);

			ConfigPath = Path + "\\config.ini";

#pragma region wrappit stuff again
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowName"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("Show2DBox"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("Show3DBox"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowArmor"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowBarrel"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowDistance"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowHealth"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowSkeleton"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowTracer"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("DrawNPC"), false);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESP"), xorstr_("Distance"), 2500);

			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxR"), 1);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxG"), 1);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxB"), 1);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxA"), 1);
#pragma endregion

			if (PathFileExistsA(ConfigPath.c_str())) {
				Config::ConfigIni.LoadFile(ConfigPath.c_str());
			}
			else {
				Config::ConfigIni.SaveFile(ConfigPath.c_str());
			}
			ParseSettings();
		}
		bDoOnce = 1;
	}

	void LoadConfig() {
		Config::ConfigIni.LoadFile(ConfigPath.c_str());
		ParseSettings();
	}

	void SaveConfig() {
#pragma region more wrappit stuff, yay
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowName"), Config::ESP::bShowName);
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("Show2DBox"), Config::ESP::bShow2DBox);
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("Show3DBox"), Config::ESP::bShow3DBox);
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowArmor"), Config::ESP::bShowArmor);
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowBarrel"), Config::ESP::bShowBarrel);
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowDistance"), Config::ESP::bShowDistance);
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowHealth"), Config::ESP::bShowHealth);
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowSkeleton"), Config::ESP::bShowSkeleton);
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowTracer"), Config::ESP::bShowTracer);
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("DrawNPC"), Config::ESP::bDrawNPC);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESP"), xorstr_("Distance"), Config::ESP::fDistance);

		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxR"), Config::Colors::f2DColor[0]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxG"), Config::Colors::f2DColor[1]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxB"), Config::Colors::f2DColor[2]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxA"), Config::Colors::f2DColor[3]);
		Config::ConfigIni.SaveFile(ConfigPath.c_str());
#pragma endregion
	}

	void ResetConfig() {
		Config::ConfigIni.Reset();
		bDoOnce = 0;
		InitConfig();
		ParseSettings();
	}
}