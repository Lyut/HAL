#pragma once
#include <cstddef>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include "../memoryman.h"
#include "vec3.h"

namespace HAL::SDK::Utils {

	SIZE_T GetPointerAddress(SIZE_T Address, UINT Offset)
	{
		if (Address == 0)
			return 0;

		if (sizeof(SIZE_T) == 8)
			return Address + (INT)((*(INT*)(Address + Offset) + Offset) + sizeof(INT));

		return (SIZE_T) * (DWORD*)(Address + Offset);
	}

	void LoadConfig() {

	}

	void SaveConfig() {

	}

	void ResetConfig() {

	}
	
}