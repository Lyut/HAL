#pragma once
#include <cstddef>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include "../memoryman.h"
#include "vec3.h"

namespace HAL::SDK::Utils {
	typedef __int64 (*GetGameBuildFn)();
	GetGameBuildFn GetGameBuild = (GetGameBuildFn)HAL::MemoryMan::PatternScan(GetModuleHandleA(xorstr_("asi-five.dll")), xorstr_("4C 8B DC 55 49 8D 6B"));

	SIZE_T GetPointerAddress(SIZE_T Address, UINT Offset)
	{
		if (Address == 0)
			return 0;

		if (sizeof(SIZE_T) == 8)
			return Address + (INT)((*(INT*)(Address + Offset) + Offset) + sizeof(INT));

		return (SIZE_T) * (DWORD*)(Address + Offset);
	}

	DWORD64 World = *(DWORD64*)(HAL::SDK::Utils::GetPointerAddress((DWORD64)HAL::MemoryMan::PatternScan(GetModuleHandleA(NULL), xorstr_("48 8B 05 ? ? ? ? 48 8B 58 08 48 85 DB 74 32")), 0x3) + 0x0);
	DWORD64 LocalPlayer = *(DWORD64*)(HAL::SDK::Utils::World + 0x8);

	DWORD64 ReplayInterface = GetPointerAddress((DWORD64)HAL::MemoryMan::PatternScan(GetModuleHandleA(NULL), xorstr_("48 8D 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 48 8D 0D ? ? ? ? 8A D8 E8 ? ? ? ? 84 DB 75 13 48 8D 0D")), 0x3);
	DWORD64 GetReplayInterface()
	{
		if (MemoryMan::ValidPTR(ReplayInterface))
			return *(DWORD64*)(ReplayInterface + 0x0);
	}
	
	struct PoolPlayers
	{
		DWORD64 ped;
		std::string name;
		ImVec4 position;
		float health;
		float armor;
	};
	PoolPlayers Players[1024];

	void Tick() 
	{
		DWORD64 list_interface = NULL;
		DWORD64 list = NULL;
		int list_max_ptr = 0;

		__try
		{
			DWORD64 replayInterface = GetReplayInterface();
			if (HAL::MemoryMan::ValidPTR(replayInterface))
			{
				list_interface = *(DWORD64*)(replayInterface + 0x18);
				list = *(DWORD64*)(list_interface + 0x100);
				list_max_ptr = *(int*)(list_interface + 0x108);
			}
		}
		__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}

		for (int i = 0; i < 1024; i++)
		{
			Players[i].ped = NULL;
			Players[i].position.x = 0.0f;

			if (i < list_max_ptr)
			{
				__try
				{
					DWORD64 ped = *(DWORD64*)(list + i * 0x10);
					if (HAL::MemoryMan::ValidPTR(ped))
					{
						Players[i].ped = ped;
						Vector3 pedPos = *(Vector3*)(ped + 0x90);
						Players[i].position = ImVec4(pedPos.x, pedPos.y, pedPos.z, 0.0f);
						Players[i].health = *(float*)(ped + 0x280) - 100.0f;
						Players[i].armor = *(float*)(ped + 0x14E0);
					}	
				}
				__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}
			}
		}
	}

	typedef BOOLEAN(__cdecl* WorldToScreen_t)(Vector3* WorldPos, float* x, float* y);
	WorldToScreen_t World2Screen = (WorldToScreen_t)(DWORD64)HAL::MemoryMan::PatternScan(GetModuleHandleA(NULL), xorstr_("48 89 5C 24 ?? 55 56 57 48 83 EC 70 65 4C 8B 0C 25 ?? 00 00 00 8B"));
	//typedef int(__fastcall* tGET_RAYCAST_RESULT)(DWORD Handle, bool* hit, D3DXVECTOR3* endCoords, D3DXVECTOR3* surfaceNormal, DWORD* entityHit);
	//tGET_RAYCAST_RESULT raycast_result_func = (tGET_RAYCAST_RESULT)(DWORD64)HAL::MemoryMan::PatternScan(GetModuleHandleA(NULL), xorstr_("48 8B C4 48 89 58 08 48 90 70 10 48 89 78 18 4C 89 70 20 55 48 8D A8 00 00 00 00 48 81 EC 00 00 00 00 33 DB 45 8B F0 48 8B FA 48 8B F1 8B C3 45 85 C9 74 08 41 8B C9 E8 00 00 00 00 F3 0F 10 1F"));

	Vector3 Position()
	{
			return *(Vector3*)(LocalPlayer + 0x90);
	}

	ImVec2 WorldToScreen(Vector3 WorldPos)
	{
		ImVec2 pos;
		if (MemoryMan::ValidPTR((DWORD64)World2Screen))
		{
			if (static_cast<BOOLEAN>(World2Screen(&WorldPos, &pos.x, &pos.y)))
			{
				pos.x = pos.x * ImGui::GetIO().DisplaySize.x;
				pos.y = pos.y * ImGui::GetIO().DisplaySize.y;
				return pos;
			}
		}
		return pos;
	}

	ImVec2 WorldToScreen2(D3DXVECTOR3 WorldPos)
	{
		return WorldToScreen(Vector3(WorldPos.x, WorldPos.y, WorldPos.z));
	}

	D3DXVECTOR3 getBone(uintptr_t ped, int bone_id) {
		auto matrix = *(D3DXMATRIX*)(ped + 0x60);
		auto bone = *(D3DXVECTOR3*)(ped + (0x430 + bone_id * 0x10));
		D3DXVECTOR4 transform;
		D3DXVec3Transform(&transform, &bone, &matrix);
		return D3DXVECTOR3(transform.x, transform.y, transform.z);
	}

	float Distance(const Vector3& point1, const Vector3& point2)
	{
		float distance = sqrt((point1.x - point2.x) * (point1.x - point2.x) +
			(point1.y - point2.y) * (point1.y - point2.y) +
			(point1.z - point2.z) * (point1.z - point2.z));
		return distance;
	}
}