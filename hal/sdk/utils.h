#pragma once
#pragma once
#include <cstddef>
#include <vector>
#include "../memoryman.h"

namespace HAL::SDK::Utils {
	typedef __int64 (*GetGameBuildFn)();
	GetGameBuildFn GetGameBuild = (GetGameBuildFn)HAL::MemoryMan::PatternScan(GetModuleHandleA("asi-five.dll"), "4C 8B DC 55 49 8D 6B");


}