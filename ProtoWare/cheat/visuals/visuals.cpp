#include "pch.h"
#include "globals.h"
#include "visuals.h"
#include "config.h"

#include "mdRenderSettings.hpp"

#include "minhook.h"


typedef bool(__fastcall* DELEGATE_GetZoomFov)(uintptr _this, int wid);

DELEGATE_GetZoomFov getzoomfov_o;

int hkGetZoomFOV(uintptr _this, int wid);
void* null_visuals_hook_data;

void visuals::initialize() {
	MH_CreateHook((void*)(gameassembly + 0x5fc0b0), &hkGetZoomFOV, (void**)&getzoomfov_o);
	MH_EnableHook((void*)(gameassembly + 0x5fc0b0));
}

void visuals::update() {

	float fov = config::custom_fov ? config::game_fov : 65.0f;
	float zoomfov = config::custom_fov ? config::zoom_fov : 46.0f;

	DWORD nullProtect;
	VirtualProtect((LPVOID)(gameassembly + 0x2B54F00), 4, PAGE_EXECUTE_READWRITE, &nullProtect);
	VirtualProtect((LPVOID)(gameassembly + 0x2B54EF4), 4, PAGE_EXECUTE_READWRITE, &nullProtect);
	VirtualProtect((LPVOID)(gameassembly + 0x5EF7E2 + 6), 4, PAGE_EXECUTE_READWRITE, &nullProtect);
	VirtualProtect((LPVOID)(gameassembly + 0x5F0294 + 6), 4, PAGE_EXECUTE_READWRITE, &nullProtect);
	VirtualProtect((LPVOID)(gameassembly + 0x5FE083 + 6), 4, PAGE_EXECUTE_READWRITE, &nullProtect);
	VirtualProtect((LPVOID)(gameassembly + 0x5EE7A4 + 3), 4, PAGE_EXECUTE_READWRITE, &nullProtect);
	VirtualProtect((LPVOID)(gameassembly + 0x35B2F98), 4, PAGE_EXECUTE_READWRITE, &nullProtect);
	*(float*)(gameassembly + 0x2B54F00) = fov; // vp_FPWeapon__Activate, movss xmm1, cs:dword_182B4EF00
	*(float*)(gameassembly + 0x2B54EF4) = zoomfov + 2.0f; // vp_FPWeaponShooter__Update, if ( v5 < 46.0 ), movss xmm1, cs:dword_182B4EEF4
	*(float*)(gameassembly + 0x5EF7E2 + 6) = fov; // vp_FPWeapon__Activate, mov dword ptr [rax+0E0h], 42820000h
	*(float*)(gameassembly + 0x5F0294 + 6) = fov; // vp_FPWeapon__Deactivate, mov dword ptr [rax+0E0h], 42820000h
	*(float*)(gameassembly + 0x5FE083 + 6) = fov; // FPWeaponShooter__OnStop_Zoom, mov dword ptr [rax+0E0h], 42820000h

	*(float*)(gameassembly + 0x35B2F98) = zoomfov + 2.0f;
	*(int*)(gameassembly + 0x5EE7A4 + 3) = (0x35B2F98 - 0x5EE7A4 - 7); // FPInput__InputZoom, comiss  xmm0, cs:dword_182B4EBD4
}
void visuals::unityupdate() {
	RenderSettings__set_fogStartDistance(0.0f);
	RenderSettings__set_fogEndDistance(1110.0f);
}

int hkGetZoomFOV(uintptr _this, int wid) {
	if (!config::custom_fov)
		return getzoomfov_o(_this, wid);
	return (int)(config::zoom_fov);
}