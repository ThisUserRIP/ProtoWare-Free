#include "pch.h"
#include "il2cpp_structs.h"
#include "math3d.h"

#define IL2CPP_CLASS il2cpp_class*
#define UNITYENGINE_VECTOR2 vec2
#define UNITYENGINE_VECTOR3 vec3
#define UNITYENGINE_VECTOR4 quat
#define UNITYENGINE_QUATERNION quat

struct PlayerControl {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	uintptr __internalObj;
	bool freeze; // 0x18
	char padding_0[7];
	uintptr Gui; // 0x20
	uintptr Map; // 0x28
	uintptr mySSEC; // 0x30
	uintptr mySiSwEC; // 0x38
	uintptr myKillEC; // 0x40
	uintptr DeathSound; // 0x48
	uintptr HitSound; // 0x50
	uintptr TraceHitSound; // 0x58
	uintptr Headshot; // 0x60
	uintptr FollowCam; // 0x68
	UNITYENGINE_VECTOR3 _spawnPos; // 0x70
};