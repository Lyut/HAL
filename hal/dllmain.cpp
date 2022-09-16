#include "core.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	HANDLE MainThread;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		MainThread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&HAL::Core::Attach), hModule, 0, 0);
		[[likely]]
		if (MainThread != INVALID_HANDLE_VALUE)
			CloseHandle(MainThread);
		break;
	case DLL_PROCESS_DETACH:
		HAL::Core::Detach();
		break;
	}
	return TRUE;
}

