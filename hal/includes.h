#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "build.h"
#include <d3d11.h>
#include <d3dx11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d11.lib")

#ifdef USE_VMP
#include "VMProtectSDK.h"
#define VMP_BEGIN(x) VMProtectBegin(x)
#define VMP_END() VMProtectEnd()
#define VMPSTR(x) VMProtectDecryptStringA(x)
#else
#define VMP_BEGIN(x)
#define VMP_END()
#define VMPSTR(x) x
#endif