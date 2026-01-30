#include "pch.h"
#include "globals.h"
#include "math3d.h"

#define GAME_ASSEMBLY_PTR gameassembly
#define UNITYENGINE_VECTOR2 vec2*
#define UNITYENGINE_VECTOR3 vec3*
#define UNITYENGINE_VECTOR4 quat*
#define UNITYENGINE_QUATERNION quat*


inline void ParticleManager__Awake(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0xa0f200))(__this);
}

inline void ParticleManager__CreateParticle(uintptr __this, float x, float y, float z, float r, float g, float b, float a) {
	((void(__fastcall*)(uintptr, float, float, float, float, float, float, float))(GAME_ASSEMBLY_PTR + 0xa0f870))(__this, x, y, z, r, g, b, a);
}

inline void ParticleManager__CreateHit(uintptr __this, uintptr _player, int hitbox, float x, float y, float z) {
	((void(__fastcall*)(uintptr, uintptr, int, float, float, float))(GAME_ASSEMBLY_PTR + 0xa0f6e0))(__this, _player, hitbox, x, y, z);
}

inline void ParticleManager__CreateFlame(uintptr __this, UNITYENGINE_VECTOR3 pos, uintptr parent) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, uintptr))(GAME_ASSEMBLY_PTR + 0xa0f530))(__this, pos, parent);
}

inline void ParticleManager__CreateAnimalEffect(uintptr __this, UNITYENGINE_VECTOR3 _position, float koef) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, float))(GAME_ASSEMBLY_PTR + 0xa0f260))(__this, _position, koef);
}

inline void ParticleManager__CreatePotionEffect(uintptr __this, UNITYENGINE_VECTOR3 _position) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0xa0f9c0))(__this, _position);
}

inline void ParticleManager__CreateGhostDeath(uintptr __this, UNITYENGINE_VECTOR3 pos) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0xa0f610))(__this, pos);
}

inline void ParticleManager__CreateBlasterProjectile(uintptr __this, uintptr _position, int _team) {
	((void(__fastcall*)(uintptr, uintptr, int))(GAME_ASSEMBLY_PTR + 0xa0f380))(__this, _position, _team);
}

inline void ParticleManager__Update(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0xa0fa90))(__this);
}

inline void ParticleManager__ctor(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x42cd60))(__this);
}
