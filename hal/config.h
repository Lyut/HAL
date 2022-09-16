#pragma once

namespace HAL::Config {

	bool bShowMenu = true;

	namespace Colors {
		float f2DColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
		float fNameColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
		float fDistanceColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
		float fSkeletonColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
		float fTracerColor[] = { 0.15f, 0.68f, 0.37f, 1.00f };
	}

	namespace ESP {
		float fDistance = 2500;
		bool bShowName = false;
		bool bShowDistance = false;
		bool bShow2DBox = false;
		bool bShowSkeleton = false;
		bool bShowTracer = false;
		bool bShowHealth = false;
		bool bShowArmor = false;
		bool bShowHeading = false;
	}
}