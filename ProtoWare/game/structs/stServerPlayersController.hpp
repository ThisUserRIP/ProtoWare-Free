#include "pch.h"
#include "il2cpp_structs.h"
#include "tarray.h"
#include "math3d.h"

#define IL2CPP_CLASS il2cpp_class*
#define IL2CPP_ARRAY tarray*
#define UNITYENGINE_VECTOR2 vec2
#define UNITYENGINE_VECTOR3 vec3
#define UNITYENGINE_VECTOR4 quat
#define UNITYENGINE_QUATERNION quat

struct ServerPlayersController {
	IL2CPP_CLASS il2cpp_class;
	uintptr __nulldata_start;
	uintptr __internalObj;
	UNITYENGINE_VECTOR3 myLookPoint; // 0x18
	char padding_0[4];
	IL2CPP_ARRAY BotsGmObj; // 0x28, GameObject[]
	uintptr pgoPlayerCreated; // 0x30
	uintptr Gui; // 0x38
	IL2CPP_ARRAY teamblock; // 0x40, Block[]
	bool PlayersLoaded; // 0x48
	char padding_1[7];
	uintptr csws; // 0x50
	uintptr SkinManager; // 0x58
	uintptr pgoPlayer; // 0x60
	uintptr csrm; // 0x68
	uintptr pgoLocalPlayer; // 0x70
	uintptr csig; // 0x78
	uintptr CurrentPlayer; // 0x80
	uintptr MG; // 0x88
	uintptr FPController; // 0x90
	IL2CPP_ARRAY RemotePlayersList; // 0x98, ServerBotData[]
	float zmupdate; // 0xa0
	float lastupdate; // 0xa4
};