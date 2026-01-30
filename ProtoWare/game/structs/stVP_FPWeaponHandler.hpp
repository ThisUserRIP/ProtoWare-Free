#include "pch.h"
#include "tlist.h"
#include "il2cpp_structs.h"

#define IL2CPP_CLASS il2cpp_class*

struct vp_FPWeaponHandler {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	uintptr __internalObj;
	int StartWeapon; // 0x18
	float AttackStateDisableDelay; // 0x1c
	float SetWeaponRefreshStatesDelay; // 0x20
	float SetWeaponDuration; // 0x24
	float SetWeaponReloadSleepDuration; // 0x28
	float SetWeaponZoomSleepDuration; // 0x2c
	float SetWeaponAttackSleepDuration; // 0x30
	float ReloadAttackSleepDuration; // 0x34
	uintptr m_Player; // 0x38
	tlist* m_Weapons; // 0x40
	int m_CurrentWeaponID; // 0x48
	char padding_0[4];
	uintptr m_CurrentWeapon; // 0x50
	uintptr m_SetWeaponTimer; // 0x58
	uintptr m_SetWeaponRefreshTimer; // 0x60
	uintptr m_DisableAttackStateTimer; // 0x68
	uintptr m_DisableReloadStateTimer; // 0x70
};