#include "pch.h"
#include "globals.h"
#include "tarray.h"
#include "math3d.h"

#define GAME_ASSEMBLY_PTR gameassembly
#define IL2CPP_ARRAY tarray*
#define UNITYENGINE_VECTOR2 vec2*
#define UNITYENGINE_VECTOR3 vec3*
#define UNITYENGINE_VECTOR4 quat*
#define UNITYENGINE_QUATERNION quat*


inline void Physics__OnSceneContactModify(uintptr scene, uintptr buffer, int count, bool isCCD) {
	((void(__fastcall*)(uintptr, uintptr, int, bool))(GAME_ASSEMBLY_PTR + 0x2931950))(scene, buffer, count, isCCD);
}

inline UNITYENGINE_VECTOR3 Physics__get_gravity() {
	return ((UNITYENGINE_VECTOR3(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2934a60))();
}

inline uintptr Physics__get_defaultPhysicsScene() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x29349e0))();
}

inline void Physics__IgnoreCollision(uintptr collider1, uintptr collider2, bool ignore) {
	((void(__fastcall*)(uintptr, uintptr, bool))(GAME_ASSEMBLY_PTR + 0x29314b0))(collider1, collider2, ignore);
}

inline void Physics__IgnoreCollision(uintptr collider1, uintptr collider2) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x2931510))(collider1, collider2);
}

inline void Physics__IgnoreLayerCollision(int layer1, int layer2, bool ignore) {
	((void(__fastcall*)(int, int, bool))(GAME_ASSEMBLY_PTR + 0x29315b0))(layer1, layer2, ignore);
}

inline void Physics__IgnoreLayerCollision(int layer1, int layer2) {
	((void(__fastcall*)(int, int))(GAME_ASSEMBLY_PTR + 0x2931560))(layer1, layer2);
}

inline bool Physics__Raycast(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, float, int, int))(GAME_ASSEMBLY_PTR + 0x2933160))(origin, direction, maxDistance, layerMask, queryTriggerInteraction);
}

inline bool Physics__Raycast(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, float maxDistance, int layerMask) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, float, int))(GAME_ASSEMBLY_PTR + 0x2932cd0))(origin, direction, maxDistance, layerMask);
}

inline bool Physics__Raycast(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, float maxDistance) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, float))(GAME_ASSEMBLY_PTR + 0x2934050))(origin, direction, maxDistance);
}

inline bool Physics__Raycast(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2933bd0))(origin, direction);
}

inline bool Physics__Raycast(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, uintptr hitInfo, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, uintptr, float, int, int))(GAME_ASSEMBLY_PTR + 0x2933a40))(origin, direction, hitInfo, maxDistance, layerMask, queryTriggerInteraction);
}

inline bool Physics__Raycast(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, uintptr hitInfo, float maxDistance, int layerMask) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, uintptr, float, int))(GAME_ASSEMBLY_PTR + 0x29332d0))(origin, direction, hitInfo, maxDistance, layerMask);
}

inline bool Physics__Raycast(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, uintptr hitInfo, float maxDistance) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, uintptr, float))(GAME_ASSEMBLY_PTR + 0x2932b40))(origin, direction, hitInfo, maxDistance);
}

inline bool Physics__Raycast(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, uintptr hitInfo) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, uintptr))(GAME_ASSEMBLY_PTR + 0x2932e40))(origin, direction, hitInfo);
}

inline bool Physics__Raycast(uintptr ray, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(uintptr, float, int, int))(GAME_ASSEMBLY_PTR + 0x29338d0))(ray, maxDistance, layerMask, queryTriggerInteraction);
}

inline bool Physics__Raycast(uintptr ray, float maxDistance, int layerMask) {
	return ((bool(__fastcall*)(uintptr, float, int))(GAME_ASSEMBLY_PTR + 0x2933460))(ray, maxDistance, layerMask);
}

inline bool Physics__Raycast(uintptr ray, float maxDistance) {
	return ((bool(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x29335d0))(ray, maxDistance);
}

inline bool Physics__Raycast(uintptr ray) {
	return ((bool(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x29341c0))(ray);
}

inline bool Physics__Raycast(uintptr ray, uintptr hitInfo, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(uintptr, uintptr, float, int, int))(GAME_ASSEMBLY_PTR + 0x2933ec0))(ray, hitInfo, maxDistance, layerMask, queryTriggerInteraction);
}

inline bool Physics__Raycast(uintptr ray, uintptr hitInfo, float maxDistance, int layerMask) {
	return ((bool(__fastcall*)(uintptr, uintptr, float, int))(GAME_ASSEMBLY_PTR + 0x2932fc0))(ray, hitInfo, maxDistance, layerMask);
}

inline bool Physics__Raycast(uintptr ray, uintptr hitInfo, float maxDistance) {
	return ((bool(__fastcall*)(uintptr, uintptr, float))(GAME_ASSEMBLY_PTR + 0x2933740))(ray, hitInfo, maxDistance);
}

inline bool Physics__Raycast(uintptr ray, uintptr hitInfo) {
	return ((bool(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x2933d40))(ray, hitInfo);
}

inline bool Physics__Linecast(UNITYENGINE_VECTOR3 start, UNITYENGINE_VECTOR3 end, uintptr hitInfo, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, uintptr, int, int))(GAME_ASSEMBLY_PTR + 0x29316e0))(start, end, hitInfo, layerMask, queryTriggerInteraction);
}

inline bool Physics__Linecast(UNITYENGINE_VECTOR3 start, UNITYENGINE_VECTOR3 end, uintptr hitInfo, int layerMask) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, uintptr, int))(GAME_ASSEMBLY_PTR + 0x2931900))(start, end, hitInfo, layerMask);
}

inline bool Physics__Linecast(UNITYENGINE_VECTOR3 start, UNITYENGINE_VECTOR3 end, uintptr hitInfo) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, uintptr))(GAME_ASSEMBLY_PTR + 0x29318b0))(start, end, hitInfo);
}

inline bool Physics__CapsuleCast(UNITYENGINE_VECTOR3 point1, UNITYENGINE_VECTOR3 point2, float radius, UNITYENGINE_VECTOR3 direction, uintptr hitInfo, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, float, UNITYENGINE_VECTOR3, uintptr, float, int, int))(GAME_ASSEMBLY_PTR + 0x2930fa0))(point1, point2, radius, direction, hitInfo, maxDistance, layerMask, queryTriggerInteraction);
}

inline bool Physics__CapsuleCast(UNITYENGINE_VECTOR3 point1, UNITYENGINE_VECTOR3 point2, float radius, UNITYENGINE_VECTOR3 direction, uintptr hitInfo, float maxDistance, int layerMask) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, float, UNITYENGINE_VECTOR3, uintptr, float, int))(GAME_ASSEMBLY_PTR + 0x2930e10))(point1, point2, radius, direction, hitInfo, maxDistance, layerMask);
}

inline bool Physics__SphereCast(UNITYENGINE_VECTOR3 origin, float radius, UNITYENGINE_VECTOR3 direction, uintptr hitInfo, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, float, UNITYENGINE_VECTOR3, uintptr, float, int, int))(GAME_ASSEMBLY_PTR + 0x29346a0))(origin, radius, direction, hitInfo, maxDistance, layerMask, queryTriggerInteraction);
}

inline bool Physics__SphereCast(UNITYENGINE_VECTOR3 origin, float radius, UNITYENGINE_VECTOR3 direction, uintptr hitInfo, float maxDistance, int layerMask) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, float, UNITYENGINE_VECTOR3, uintptr, float, int))(GAME_ASSEMBLY_PTR + 0x2934450))(origin, radius, direction, hitInfo, maxDistance, layerMask);
}

inline bool Physics__SphereCast(uintptr ray, float radius, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(uintptr, float, float, int, int))(GAME_ASSEMBLY_PTR + 0x29344c0))(ray, radius, maxDistance, layerMask, queryTriggerInteraction);
}

inline bool Physics__SphereCast(uintptr ray, float radius, float maxDistance, int layerMask) {
	return ((bool(__fastcall*)(uintptr, float, float, int))(GAME_ASSEMBLY_PTR + 0x29345b0))(ray, radius, maxDistance, layerMask);
}

inline bool Physics__SphereCast(uintptr ray, float radius, uintptr hitInfo, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(uintptr, float, uintptr, float, int, int))(GAME_ASSEMBLY_PTR + 0x2934800))(ray, radius, hitInfo, maxDistance, layerMask, queryTriggerInteraction);
}

inline bool Physics__SphereCast(uintptr ray, float radius, uintptr hitInfo, float maxDistance, int layerMask) {
	return ((bool(__fastcall*)(uintptr, float, uintptr, float, int))(GAME_ASSEMBLY_PTR + 0x29348d0))(ray, radius, hitInfo, maxDistance, layerMask);
}

inline IL2CPP_ARRAY Physics__Internal_RaycastAll(uintptr physicsScene, uintptr ray, float maxDistance, int mask, int queryTriggerInteraction) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, uintptr, float, int, int))(GAME_ASSEMBLY_PTR + 0x2931670))(physicsScene, ray, maxDistance, mask, queryTriggerInteraction);
}

inline IL2CPP_ARRAY Physics__RaycastAll(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((IL2CPP_ARRAY(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, float, int, int))(GAME_ASSEMBLY_PTR + 0x2932050))(origin, direction, maxDistance, layerMask, queryTriggerInteraction);
}

inline IL2CPP_ARRAY Physics__RaycastAll(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, float maxDistance, int layerMask) {
	return ((IL2CPP_ARRAY(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, float, int))(GAME_ASSEMBLY_PTR + 0x2932000))(origin, direction, maxDistance, layerMask);
}

inline IL2CPP_ARRAY Physics__RaycastAll(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, float maxDistance) {
	return ((IL2CPP_ARRAY(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, float))(GAME_ASSEMBLY_PTR + 0x2932280))(origin, direction, maxDistance);
}

inline IL2CPP_ARRAY Physics__RaycastAll(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction) {
	return ((IL2CPP_ARRAY(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x29322d0))(origin, direction);
}

inline IL2CPP_ARRAY Physics__RaycastAll(uintptr ray, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, float, int, int))(GAME_ASSEMBLY_PTR + 0x29321d0))(ray, maxDistance, layerMask, queryTriggerInteraction);
}

inline IL2CPP_ARRAY Physics__RaycastAll(uintptr ray, float maxDistance, int layerMask) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, float, int))(GAME_ASSEMBLY_PTR + 0x2931f60))(ray, maxDistance, layerMask);
}

inline IL2CPP_ARRAY Physics__RaycastAll(uintptr ray, float maxDistance) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x2931ec0))(ray, maxDistance);
}

inline IL2CPP_ARRAY Physics__RaycastAll(uintptr ray) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2932330))(ray);
}

inline int Physics__RaycastNonAlloc(uintptr ray, IL2CPP_ARRAY results, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((int(__fastcall*)(uintptr, IL2CPP_ARRAY, float, int, int))(GAME_ASSEMBLY_PTR + 0x2932880))(ray, results, maxDistance, layerMask, queryTriggerInteraction);
}

inline int Physics__RaycastNonAlloc(uintptr ray, IL2CPP_ARRAY results, float maxDistance, int layerMask) {
	return ((int(__fastcall*)(uintptr, IL2CPP_ARRAY, float, int))(GAME_ASSEMBLY_PTR + 0x29325c0))(ray, results, maxDistance, layerMask);
}

inline int Physics__RaycastNonAlloc(uintptr ray, IL2CPP_ARRAY results, float maxDistance) {
	return ((int(__fastcall*)(uintptr, IL2CPP_ARRAY, float))(GAME_ASSEMBLY_PTR + 0x29323c0))(ray, results, maxDistance);
}

inline int Physics__RaycastNonAlloc(uintptr ray, IL2CPP_ARRAY results) {
	return ((int(__fastcall*)(uintptr, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x29324c0))(ray, results);
}

inline int Physics__RaycastNonAlloc(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, IL2CPP_ARRAY results, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((int(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, IL2CPP_ARRAY, float, int, int))(GAME_ASSEMBLY_PTR + 0x2932990))(origin, direction, results, maxDistance, layerMask, queryTriggerInteraction);
}

inline int Physics__RaycastNonAlloc(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, IL2CPP_ARRAY results, float maxDistance, int layerMask) {
	return ((int(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, IL2CPP_ARRAY, float, int))(GAME_ASSEMBLY_PTR + 0x29327a0))(origin, direction, results, maxDistance, layerMask);
}

inline int Physics__RaycastNonAlloc(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, IL2CPP_ARRAY results, float maxDistance) {
	return ((int(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, IL2CPP_ARRAY, float))(GAME_ASSEMBLY_PTR + 0x29326d0))(origin, direction, results, maxDistance);
}

inline int Physics__RaycastNonAlloc(UNITYENGINE_VECTOR3 origin, UNITYENGINE_VECTOR3 direction, IL2CPP_ARRAY results) {
	return ((int(__fastcall*)(UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x2932a70))(origin, direction, results);
}

inline IL2CPP_ARRAY Physics__OverlapSphere_Internal(uintptr physicsScene, UNITYENGINE_VECTOR3 position, float radius, int layerMask, int queryTriggerInteraction) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, float, int, int))(GAME_ASSEMBLY_PTR + 0x2931b40))(physicsScene, position, radius, layerMask, queryTriggerInteraction);
}

inline IL2CPP_ARRAY Physics__OverlapSphere(UNITYENGINE_VECTOR3 position, float radius, int layerMask, int queryTriggerInteraction) {
	return ((IL2CPP_ARRAY(__fastcall*)(UNITYENGINE_VECTOR3, float, int, int))(GAME_ASSEMBLY_PTR + 0x2931c60))(position, radius, layerMask, queryTriggerInteraction);
}

inline IL2CPP_ARRAY Physics__OverlapSphere(UNITYENGINE_VECTOR3 position, float radius, int layerMask) {
	return ((IL2CPP_ARRAY(__fastcall*)(UNITYENGINE_VECTOR3, float, int))(GAME_ASSEMBLY_PTR + 0x2931bb0))(position, radius, layerMask);
}

inline IL2CPP_ARRAY Physics__OverlapSphere(UNITYENGINE_VECTOR3 position, float radius) {
	return ((IL2CPP_ARRAY(__fastcall*)(UNITYENGINE_VECTOR3, float))(GAME_ASSEMBLY_PTR + 0x2931d20))(position, radius);
}

inline bool Physics__Query_ComputePenetration(uintptr colliderA, UNITYENGINE_VECTOR3 positionA, UNITYENGINE_QUATERNION rotationA, uintptr colliderB, UNITYENGINE_VECTOR3 positionB, UNITYENGINE_QUATERNION rotationB, UNITYENGINE_VECTOR3 direction, float distance) {
	return ((bool(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, UNITYENGINE_QUATERNION, uintptr, UNITYENGINE_VECTOR3, UNITYENGINE_QUATERNION, UNITYENGINE_VECTOR3, float))(GAME_ASSEMBLY_PTR + 0x2931e30))(colliderA, positionA, rotationA, colliderB, positionB, rotationB, direction, distance);
}

inline bool Physics__ComputePenetration(uintptr colliderA, UNITYENGINE_VECTOR3 positionA, UNITYENGINE_QUATERNION rotationA, uintptr colliderB, UNITYENGINE_VECTOR3 positionB, UNITYENGINE_QUATERNION rotationB, UNITYENGINE_VECTOR3 direction, float distance) {
	return ((bool(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, UNITYENGINE_QUATERNION, uintptr, UNITYENGINE_VECTOR3, UNITYENGINE_QUATERNION, UNITYENGINE_VECTOR3, float))(GAME_ASSEMBLY_PTR + 0x2931380))(colliderA, positionA, rotationA, colliderB, positionB, rotationB, direction, distance);
}

inline int Physics__OverlapSphereNonAlloc(UNITYENGINE_VECTOR3 position, float radius, IL2CPP_ARRAY results, int layerMask, int queryTriggerInteraction) {
	return ((int(__fastcall*)(UNITYENGINE_VECTOR3, float, IL2CPP_ARRAY, int, int))(GAME_ASSEMBLY_PTR + 0x2931a10))(position, radius, results, layerMask, queryTriggerInteraction);
}

inline bool Physics__CheckSphere_Internal(uintptr physicsScene, UNITYENGINE_VECTOR3 position, float radius, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, float, int, int))(GAME_ASSEMBLY_PTR + 0x29311a0))(physicsScene, position, radius, layerMask, queryTriggerInteraction);
}

inline bool Physics__CheckSphere(UNITYENGINE_VECTOR3 position, float radius, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, float, int, int))(GAME_ASSEMBLY_PTR + 0x2931210))(position, radius, layerMask, queryTriggerInteraction);
}

inline bool Physics__CheckSphere(UNITYENGINE_VECTOR3 position, float radius, int layerMask) {
	return ((bool(__fastcall*)(UNITYENGINE_VECTOR3, float, int))(GAME_ASSEMBLY_PTR + 0x29312d0))(position, radius, layerMask);
}

inline int Physics__SphereCastNonAlloc(UNITYENGINE_VECTOR3 origin, float radius, UNITYENGINE_VECTOR3 direction, IL2CPP_ARRAY results, float maxDistance, int layerMask, int queryTriggerInteraction) {
	return ((int(__fastcall*)(UNITYENGINE_VECTOR3, float, UNITYENGINE_VECTOR3, IL2CPP_ARRAY, float, int, int))(GAME_ASSEMBLY_PTR + 0x2934320))(origin, radius, direction, results, maxDistance, layerMask, queryTriggerInteraction);
}

inline void Physics__get_gravity_Injected(UNITYENGINE_VECTOR3 ret) {
	((void(__fastcall*)(UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2934a20))(ret);
}

inline void Physics__get_defaultPhysicsScene_Injected(uintptr ret) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x29349a0))(ret);
}

inline IL2CPP_ARRAY Physics__Internal_RaycastAll_Injected(uintptr physicsScene, uintptr ray, float maxDistance, int mask, int queryTriggerInteraction) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, uintptr, float, int, int))(GAME_ASSEMBLY_PTR + 0x2931600))(physicsScene, ray, maxDistance, mask, queryTriggerInteraction);
}

inline IL2CPP_ARRAY Physics__OverlapSphere_Internal_Injected(uintptr physicsScene, UNITYENGINE_VECTOR3 position, float radius, int layerMask, int queryTriggerInteraction) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, float, int, int))(GAME_ASSEMBLY_PTR + 0x2931ad0))(physicsScene, position, radius, layerMask, queryTriggerInteraction);
}

inline bool Physics__Query_ComputePenetration_Injected(uintptr colliderA, UNITYENGINE_VECTOR3 positionA, UNITYENGINE_QUATERNION rotationA, uintptr colliderB, UNITYENGINE_VECTOR3 positionB, UNITYENGINE_QUATERNION rotationB, UNITYENGINE_VECTOR3 direction, float distance) {
	return ((bool(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, UNITYENGINE_QUATERNION, uintptr, UNITYENGINE_VECTOR3, UNITYENGINE_QUATERNION, UNITYENGINE_VECTOR3, float))(GAME_ASSEMBLY_PTR + 0x2931dc0))(colliderA, positionA, rotationA, colliderB, positionB, rotationB, direction, distance);
}

inline bool Physics__CheckSphere_Internal_Injected(uintptr physicsScene, UNITYENGINE_VECTOR3 position, float radius, int layerMask, int queryTriggerInteraction) {
	return ((bool(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, float, int, int))(GAME_ASSEMBLY_PTR + 0x2931130))(physicsScene, position, radius, layerMask, queryTriggerInteraction);
}
