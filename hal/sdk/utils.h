#pragma once
#include <cstddef>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <shlobj.h>
#include <Shlwapi.h>
#include <shellapi.h>
#include <comutil.h>
#include <fstream>
#include "../memoryman.h"
#include "vec3.h"
#include "../config.h"

namespace HAL::SDK::Utils {

	bool bDoOnce = 0;
	std::string Path;
	std::string ConfigPath;
	std::string LicensePath;
	std::string Username;

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
		Config::License = Config::ConfigIni.GetValue("LEWD", "LicenseKey", "INVALID");
		RemoveSpaces(&Config::License);

		Config::ESP::bShowName = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowName")), false);
		Config::ESP::bShow2DBox = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("Show2DBox")), false);
		Config::ESP::bShow3DBox = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("Show3DBox")), false);
		Config::ESP::bShowArmor = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowArmor")), false);
		Config::ESP::bShowBarrel = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowBarrel")), false);
		Config::ESP::bShowDistance = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowDistance")), false);
		Config::ESP::bShowHealth = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowHealth")), false);
		Config::ESP::bShowSkeleton = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowSkeleton")), false);
		Config::ESP::bShowTracer = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("ShowTracer")), false);
		Config::ESP::bDrawLocal = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("DrawLocal")), false);
		Config::ESP::bDrawNPC = ConfigParseBool(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("DrawNPC")), false);
		Config::ESP::fDistance = ConfigParseInt(Config::ConfigIni.GetValue(xorstr_("ESP"), xorstr_("Distance")), 2500);

		Config::Colors::f2DColor[0] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxR")) * 100) / 100;
		Config::Colors::f2DColor[1] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxG")) * 100) / 100;
		Config::Colors::f2DColor[2] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxB")) * 100) / 100;
		Config::Colors::f2DColor[3] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxA")) * 100) / 100;

		Config::Colors::f3DColor[0] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxR")) * 100) / 100;
		Config::Colors::f3DColor[1] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxG")) * 100) / 100;
		Config::Colors::f3DColor[2] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxB")) * 100) / 100;
		Config::Colors::f3DColor[3] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxA")) * 100) / 100;

		Config::Colors::fNameColor[0] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("NameR")) * 100) / 100;
		Config::Colors::fNameColor[1] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("NameG")) * 100) / 100;
		Config::Colors::fNameColor[2] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("NameB")) * 100) / 100;
		Config::Colors::fNameColor[3] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("NameA")) * 100) / 100;

		Config::Colors::fDistanceColor[0] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceR")) * 100) / 100;
		Config::Colors::fDistanceColor[1] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceG")) * 100) / 100;
		Config::Colors::fDistanceColor[2] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceB")) * 100) / 100;
		Config::Colors::fDistanceColor[3] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceA")) * 100) / 100;

		Config::Colors::fSkeletonColor[0] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonR")) * 100) / 100;
		Config::Colors::fSkeletonColor[1] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonG")) * 100) / 100;
		Config::Colors::fSkeletonColor[2] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonB")) * 100) / 100;
		Config::Colors::fSkeletonColor[3] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonA")) * 100) / 100;

		Config::Colors::fTracerColor[0] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerR")) * 100) / 100;
		Config::Colors::fTracerColor[1] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerG")) * 100) / 100;
		Config::Colors::fTracerColor[2] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerB")) * 100) / 100;
		Config::Colors::fTracerColor[3] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerA")) * 100) / 100;

		Config::Colors::fBarrelColor[0] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelR")) * 100) / 100;
		Config::Colors::fBarrelColor[1] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelG")) * 100) / 100;
		Config::Colors::fBarrelColor[2] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelB")) * 100) / 100;
		Config::Colors::fBarrelColor[3] = floor(Config::ConfigIni.GetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelA")) * 100) / 100;
#pragma endregion
	}

	void InitConfig() {
		[[likely]]
		if (!bDoOnce) {
			char Documents[MAX_PATH];
			SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, Documents);

			Path += std::string(Documents) + xorstr_("\\lewd");
			LicensePath = Path + xorstr_("\\.license");

			if (!PathIsDirectoryA(Path.c_str()))
				CreateDirectoryA(Path.c_str(), 0);

			ConfigPath = Path + xorstr_("\\config.ini");

#pragma region wrappit stuff again
			Config::ConfigIni.SetValue(xorstr_("LEWD"), xorstr_("LicenseKey"), xorstr_("INVALID"));

			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowName"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("Show2DBox"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("Show3DBox"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowArmor"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowBarrel"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowDistance"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowHealth"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowSkeleton"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("ShowTracer"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("DrawLocal"), false);
			Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("DrawNPC"), false);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESP"), xorstr_("Distance"), 2500);

			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxR"), 0);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxG"), 1);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxB"), 0);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxA"), 1);

			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxR"), 1);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxG"), 0);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxB"), 0.88f);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxA"), 1);

			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("NameR"), 1);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("NameG"), 0);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("NameB"), 0.94f);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("NameA"), 1);

			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceR"), 0.99f);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceG"), 1);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceB"), 0.99f);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceA"), 1);

			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonR"), 0.99f);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonG"), 1);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonB"), 0.99f);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonA"), 1);

			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerR"), 1);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerG"), 0);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerB"), 0);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerA"), 0.39f);

			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelR"), 1);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelG"), 0);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelB"), 0);
			Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelA"), 1);
#pragma endregion

			if (PathFileExistsA(ConfigPath.c_str())) {
				Config::ConfigIni.LoadFile(ConfigPath.c_str());
			}
			else {
				Config::ConfigIni.SaveFile(ConfigPath.c_str());
			}
			ParseSettings();
		}
#ifdef USE_ACTIVATION
		if (Config::License == VMPSTR("INSERT PRODUCT KEY HERE")) {
			MessageBoxA(NULL, VMPSTR("Please set your License Key in 'Documents/lewd/config.ini'!"), VMPSTR("ByondHook"), 0);
			ShellExecuteA(NULL, "edit", ConfigPath.c_str(), NULL, Path.c_str(), true);
		}

		char VMPSerial[8192];
		bool Activated = false;
		bool TryToActivate = false;
		//printf("License is %s\n", License.c_str());
		int KeyRes = VMProtectActivateLicense(Config::License.c_str(), VMPSerial, 8192);
		switch (KeyRes) {
		case ACTIVATION_OK:
			Activated = true;
			break;
		case ACTIVATION_ALREADY_USED:
			//Log(VMPSTR("ACTIVATION_ALREADY_USED"));
			MessageBoxA(NULL, VMPSTR("Please only use this LEWD license key with the original machine it was created for.\nIf this is a mistake, please use LEWDbot to regenerate your key."), VMPSTR("LEWD"), 0);
			break;
		case ACTIVATION_NO_CONNECTION:
			//Log(VMPSTR("ACTIVATION_NO_CONNECTION"));
			if (PathFileExistsA(LicensePath.c_str()))
				TryToActivate = true;
			else
				MessageBoxA(NULL, VMPSTR("Failed to connect to LEWD activation server."), VMPSTR("LEWD"), 0);
			break;
		case ACTIVATION_BAD_REPLY:
			//Log(VMPSTR("ACTIVATION_BAD_REPLY"));
			if (PathFileExistsA(LicensePath.c_str()))
				TryToActivate = true;
			else
				MessageBoxA(NULL, VMPSTR("Recieved bad reply from LEWD activation server."), VMPSTR("LEWD"), 0);
			break;
		case ACTIVATION_CORRUPTED:
		case ACTIVATION_BAD_CODE:
		case ACTIVATION_SERIAL_UNKNOWN:
			//Log(VMPSTR("ACTIVATION_CORRUPTED"));
			MessageBoxA(NULL, VMPSTR("Invalid LEWD license key."), VMPSTR("LEWD"), 0);
			if (PathFileExistsA(LicensePath.c_str()))
				DeleteFileA(LicensePath.c_str());
			break;
		default:
			MessageBoxA(NULL, VMPSTR("Could not activate LEWD."), VMPSTR("LEWD"), 0);
			break;
		}
		if (Activated || TryToActivate) {
			if (TryToActivate) {
				std::ifstream lic(LicensePath);
				lic.read(VMPSerial, sizeof(VMPSerial));
				lic.close();
			}
			VMProtectSetSerialNumber(VMPSerial);
			VMProtectSerialNumberData sd = { 0 };
			VMProtectGetSerialNumberData(&sd, sizeof(sd));
			if (sd.nState != SERIAL_STATE_SUCCESS) {
				MessageBoxA(NULL, VMPSTR("LEWD"), VMPSTR("LEWD"), 0);
				Activated = false;
				if (PathFileExistsA(LicensePath.c_str()))
					DeleteFileA(LicensePath.c_str());
			}
			else {
				if (!TryToActivate) {
					std::ofstream lic(LicensePath);
					lic << VMPSerial;
					lic.close();
				}
				_bstr_t b(sd.wUserName);
				Username = _strdup((const char*)b);
			}
		}
		if (!Activated) {
			FreeLibraryAndExitThread(NULL, 0);
			return;
		}
#endif
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
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("DrawLocal"), Config::ESP::bDrawLocal);
		Config::ConfigIni.SetBoolValue(xorstr_("ESP"), xorstr_("DrawNPC"), Config::ESP::bDrawNPC);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESP"), xorstr_("Distance"), Config::ESP::fDistance);

		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxR"), Config::Colors::f2DColor[0]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxG"), Config::Colors::f2DColor[1]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxB"), Config::Colors::f2DColor[2]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("2DBoxA"), Config::Colors::f2DColor[3]);

		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxR"), Config::Colors::f3DColor[0]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxG"), Config::Colors::f3DColor[1]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxB"), Config::Colors::f3DColor[2]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("3DBoxA"), Config::Colors::f3DColor[3]);

		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("NameR"), Config::Colors::fNameColor[0]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("NameG"), Config::Colors::fNameColor[1]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("NameB"), Config::Colors::fNameColor[2]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("NameA"), Config::Colors::fNameColor[3]);

		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceR"), Config::Colors::fDistanceColor[0]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceG"), Config::Colors::fDistanceColor[1]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceB"), Config::Colors::fDistanceColor[2]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("DistanceA"), Config::Colors::fDistanceColor[3]);

		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonR"), Config::Colors::fSkeletonColor[0]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonG"), Config::Colors::fSkeletonColor[1]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonB"), Config::Colors::fSkeletonColor[2]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("SkeletonA"), Config::Colors::fSkeletonColor[3]);

		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerR"), Config::Colors::fTracerColor[0]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerG"), Config::Colors::fTracerColor[1]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerB"), Config::Colors::fTracerColor[2]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("TracerA"), Config::Colors::fTracerColor[3]);

		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelR"), Config::Colors::fBarrelColor[0]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelG"), Config::Colors::fBarrelColor[1]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelB"), Config::Colors::fBarrelColor[2]);
		Config::ConfigIni.SetDoubleValue(xorstr_("ESPColors"), xorstr_("BarrelA"), Config::Colors::fBarrelColor[3]);
		Config::ConfigIni.SaveFile(ConfigPath.c_str());
#pragma endregion
	}

	void ResetConfig() {
		bDoOnce = 0;
		InitConfig();
	}
}