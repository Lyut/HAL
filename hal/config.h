#pragma once
#include "sdk/SimpleIni.h"

namespace HAL::Config {

	CSimpleIniA ConfigIni;
	std::string License;

	bool bShowMenu = true;

	namespace Colors {
		float f2DColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
		float f3DColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
		float fNameColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
		float fDistanceColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
		float fSkeletonColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
		float fTracerColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
		float fBarrelColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
	}

	namespace Aimbot {
		int iFOV = 100;
		bool bEnabled = false;
		bool bSmoothEnabled = false;
		int iSmoothness = 0;
		int iAimBone = 0;
	}

	namespace ESP {
		float fDistance = 2500;
		bool bShowName = false;
		bool bShowDistance = false;
		bool bShow2DBox = false;
		bool bShow3DBox = false;
		bool bShowSkeleton = false;
		bool bShowTracer = false;
		bool bShowHealth = false;
		bool bShowArmor = false;
		bool bShowBarrel = false;
		bool bDrawNPC = false;
		bool bDrawLocal = false;
	}

	static bool PedSelection[29] = { true, true, true, true, true, true, true,
									 true, true, true, true, true, true, true,
									 true, true, true, true, true, true, true,
									 true, true, true, true, true, true, true,
									 true 
	};
}