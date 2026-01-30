#include "pch.h"
#include "globals.h"
#include "monostring.h"
#include "tarray.h"
#include "math3d.h"

#define GAME_ASSEMBLY_PTR gameassembly
#define IL2CPP_STRING monostring*
#define IL2CPP_ARRAY tarray*
#define UNITYENGINE_VECTOR2 vec2*
#define UNITYENGINE_VECTOR3 vec3*
#define UNITYENGINE_VECTOR4 quat*
#define UNITYENGINE_QUATERNION quat*


inline void Camera__ctor(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2889f40))(__this);
}

inline float Camera__get_nearClipPlane(uintptr __this) {
	return ((float(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a520))(__this);
}

inline void Camera__set_nearClipPlane(uintptr __this, float value) {
	((void(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x288b000))(__this, value);
}

inline float Camera__get_farClipPlane(uintptr __this) {
	return ((float(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a390))(__this);
}

inline void Camera__set_farClipPlane(uintptr __this, float value) {
	((void(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x288ad90))(__this, value);
}

inline float Camera__get_fieldOfView(uintptr __this) {
	return ((float(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a3d0))(__this);
}

inline void Camera__set_fieldOfView(uintptr __this, float value) {
	((void(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x288ade0))(__this, value);
}

inline uintptr Camera__get_actualRenderingPath(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2889f50))(__this);
}

inline bool Camera__get_allowHDR(uintptr __this) {
	return ((bool(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2889fd0))(__this);
}

inline bool Camera__get_allowMSAA(uintptr __this) {
	return ((bool(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a010))(__this);
}

inline bool Camera__get_allowDynamicResolution(uintptr __this) {
	return ((bool(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2889f90))(__this);
}

inline float Camera__get_orthographicSize(uintptr __this) {
	return ((float(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a5a0))(__this);
}

inline void Camera__set_orthographicSize(uintptr __this, float value) {
	((void(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x288b0f0))(__this, value);
}

inline bool Camera__get_orthographic(uintptr __this) {
	return ((bool(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a5e0))(__this);
}

inline void Camera__set_orthographic(uintptr __this, bool value) {
	((void(__fastcall*)(uintptr, bool))(GAME_ASSEMBLY_PTR + 0x288b140))(__this, value);
}

inline uintptr Camera__get_opaqueSortMode(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a560))(__this);
}

inline float Camera__get_depth(uintptr __this) {
	return ((float(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a310))(__this);
}

inline void Camera__set_depth(uintptr __this, float value) {
	((void(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x288ad40))(__this, value);
}

inline float Camera__get_aspect(uintptr __this) {
	return ((float(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a050))(__this);
}

inline int Camera__get_cullingMask(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a260))(__this);
}

inline void Camera__set_cullingMask(uintptr __this, int value) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x288acc0))(__this, value);
}

inline int Camera__get_eventMask(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a350))(__this);
}

inline uintptr Camera__get_cameraType(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a1e0))(__this);
}

inline IL2CPP_ARRAY Camera__GetLayerCullDistances(uintptr __this) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2888f50))(__this);
}

inline void Camera__SetLayerCullDistances(uintptr __this, IL2CPP_ARRAY d) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x28898c0))(__this, d);
}

inline IL2CPP_ARRAY Camera__get_layerCullDistances(uintptr __this) {
	return ((IL2CPP_ARRAY(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2888f50))(__this);
}

inline void Camera__set_layerCullDistances(uintptr __this, IL2CPP_ARRAY value) {
	((void(__fastcall*)(uintptr, IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x288aec0))(__this, value);
}

inline uintptr Camera__get_backgroundColor(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a0e0))(__this);
}

inline void Camera__set_backgroundColor(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288ac30))(__this, value);
}

inline uintptr Camera__get_clearFlags(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a220))(__this);
}

inline void Camera__set_clearFlags(uintptr __this, int value) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x288ac80))(__this, value);
}

inline uintptr Camera__get_depthTextureMode(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a2d0))(__this);
}

inline void Camera__set_depthTextureMode(uintptr __this, int value) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x288ad00))(__this, value);
}

inline bool Camera__get_usePhysicalProperties(uintptr __this) {
	return ((bool(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288aaf0))(__this);
}

inline void Camera__set_usePhysicalProperties(uintptr __this, bool value) {
	((void(__fastcall*)(uintptr, bool))(GAME_ASSEMBLY_PTR + 0x288b4a0))(__this, value);
}

inline UNITYENGINE_VECTOR2 Camera__get_sensorSize(uintptr __this) {
	return ((UNITYENGINE_VECTOR2(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a960))(__this);
}

inline void Camera__set_sensorSize(uintptr __this, UNITYENGINE_VECTOR2 value) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x288b3c0))(__this, value);
}

inline UNITYENGINE_VECTOR2 Camera__get_lensShift(uintptr __this) {
	return ((UNITYENGINE_VECTOR2(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a4a0))(__this);
}

inline void Camera__set_lensShift(uintptr __this, UNITYENGINE_VECTOR2 value) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x288afc0))(__this, value);
}

inline void Camera__set_focalLength(uintptr __this, float value) {
	((void(__fastcall*)(uintptr, float))(GAME_ASSEMBLY_PTR + 0x288ae30))(__this, value);
}

inline uintptr Camera__get_gateFit(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a410))(__this);
}

inline void Camera__set_gateFit(uintptr __this, int value) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x288ae80))(__this, value);
}

inline uintptr Camera__get_rect(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a840))(__this);
}

inline void Camera__set_rect(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b320))(__this, value);
}

inline uintptr Camera__get_pixelRect(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a6b0))(__this);
}

inline void Camera__set_pixelRect(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b1e0))(__this, value);
}

inline int Camera__get_pixelWidth(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a700))(__this);
}

inline int Camera__get_pixelHeight(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a620))(__this);
}

inline int Camera__get_scaledPixelWidth(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a8d0))(__this);
}

inline int Camera__get_scaledPixelHeight(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a890))(__this);
}

inline uintptr Camera__get_targetTexture(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288aab0))(__this);
}

inline void Camera__set_targetTexture(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b400))(__this, value);
}

inline int Camera__get_targetDisplay(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288aa70))(__this);
}

inline uintptr Camera__get_cameraToWorldMatrix(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a180))(__this);
}

inline uintptr Camera__get_worldToCameraMatrix(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288ab80))(__this);
}

inline void Camera__set_worldToCameraMatrix(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b540))(__this, value);
}

inline uintptr Camera__get_projectionMatrix(uintptr __this) {
	return ((uintptr(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a790))(__this);
}

inline void Camera__set_projectionMatrix(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b280))(__this, value);
}

inline void Camera__set_nonJitteredProjectionMatrix(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b0a0))(__this, value);
}

inline void Camera__set_useJitteredProjectionMatrixForTransparentRendering(uintptr __this, bool value) {
	((void(__fastcall*)(uintptr, bool))(GAME_ASSEMBLY_PTR + 0x288b450))(__this, value);
}

inline void Camera__ResetWorldToCameraMatrix(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2889410))(__this);
}

inline void Camera__ResetProjectionMatrix(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2889350))(__this);
}

inline UNITYENGINE_VECTOR3 Camera__WorldToScreenPoint(uintptr __this, UNITYENGINE_VECTOR3 position, int eye) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, int))(GAME_ASSEMBLY_PTR + 0x2889d60))(__this, position, eye);
}

inline UNITYENGINE_VECTOR3 Camera__WorldToViewportPoint(uintptr __this, UNITYENGINE_VECTOR3 position, int eye) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, int))(GAME_ASSEMBLY_PTR + 0x2889ed0))(__this, position, eye);
}

inline UNITYENGINE_VECTOR3 Camera__ViewportToWorldPoint(uintptr __this, UNITYENGINE_VECTOR3 position, int eye) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, int))(GAME_ASSEMBLY_PTR + 0x2889bf0))(__this, position, eye);
}

inline UNITYENGINE_VECTOR3 Camera__ScreenToWorldPoint(uintptr __this, UNITYENGINE_VECTOR3 position, int eye) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, int))(GAME_ASSEMBLY_PTR + 0x28897c0))(__this, position, eye);
}

inline UNITYENGINE_VECTOR3 Camera__WorldToScreenPoint(uintptr __this, UNITYENGINE_VECTOR3 position) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2889cd0))(__this, position);
}

inline UNITYENGINE_VECTOR3 Camera__WorldToViewportPoint(uintptr __this, UNITYENGINE_VECTOR3 position) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2889e40))(__this, position);
}

inline UNITYENGINE_VECTOR3 Camera__ViewportToWorldPoint(uintptr __this, UNITYENGINE_VECTOR3 position) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2889b60))(__this, position);
}

inline UNITYENGINE_VECTOR3 Camera__ScreenToWorldPoint(uintptr __this, UNITYENGINE_VECTOR3 position) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2889830))(__this, position);
}

inline UNITYENGINE_VECTOR3 Camera__ScreenToViewportPoint(uintptr __this, UNITYENGINE_VECTOR3 position) {
	return ((UNITYENGINE_VECTOR3(__fastcall*)(uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x28896f0))(__this, position);
}

inline uintptr Camera__ScreenPointToRay(uintptr __this, UNITYENGINE_VECTOR2 pos, int eye) {
	return ((uintptr(__fastcall*)(uintptr, UNITYENGINE_VECTOR2, int))(GAME_ASSEMBLY_PTR + 0x2889620))(__this, pos, eye);
}

inline uintptr Camera__ScreenPointToRay(uintptr __this, UNITYENGINE_VECTOR3 pos, int eye) {
	return ((uintptr(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, int))(GAME_ASSEMBLY_PTR + 0x2889570))(__this, pos, eye);
}

inline uintptr Camera__ScreenPointToRay(uintptr retptr, uintptr __this, UNITYENGINE_VECTOR3 pos) {
	return ((uintptr(__fastcall*)(uintptr, uintptr, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x28894c0))(retptr, __this, pos);
}

inline float Camera__FieldOfViewToFocalLength(float fieldOfView, float sensorSize) {
	return ((float(__fastcall*)(float, float))(GAME_ASSEMBLY_PTR + 0x2888bd0))(fieldOfView, sensorSize);
}

inline uintptr Camera__get_main() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x288a4f0))();
}

inline uintptr Camera__get_current() {
	return ((uintptr(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x288a2a0))();
}

inline bool Camera__get_stereoEnabled(uintptr __this) {
	return ((bool(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a9f0))(__this);
}

inline uintptr Camera__get_stereoTargetEye(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288aa30))(__this);
}

inline uintptr Camera__get_stereoActiveEye(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x288a9b0))(__this);
}

inline uintptr Camera__GetStereoNonJitteredProjectionMatrix(uintptr __this, int eye) {
	return ((uintptr(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x2888fe0))(__this, eye);
}

inline void Camera__CopyStereoDeviceProjectionMatrixToNonJittered(uintptr __this, int eye) {
	((void(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x2888b90))(__this, eye);
}

inline uintptr Camera__GetStereoProjectionMatrix(uintptr __this, int eye) {
	return ((uintptr(__fastcall*)(uintptr, int))(GAME_ASSEMBLY_PTR + 0x28890a0))(__this, eye);
}

inline void Camera__SetStereoProjectionMatrix(uintptr __this, int eye, uintptr matrix) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x2889960))(__this, eye, matrix);
}

inline void Camera__ResetStereoProjectionMatrices(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2889390))(__this);
}

inline void Camera__SetStereoViewMatrix(uintptr __this, int eye, uintptr matrix) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x2889a00))(__this, eye, matrix);
}

inline void Camera__ResetStereoViewMatrices(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x28893d0))(__this);
}

inline int Camera__GetAllCamerasCount() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2888d40))();
}

inline int Camera__GetAllCamerasImpl(IL2CPP_ARRAY cam) {
	return ((int(__fastcall*)(IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x2888d70))(cam);
}

inline int Camera__get_allCamerasCount() {
	return ((int(__fastcall*)())(GAME_ASSEMBLY_PTR + 0x2888d40))();
}

inline int Camera__GetAllCameras(IL2CPP_ARRAY cameras) {
	return ((int(__fastcall*)(IL2CPP_ARRAY))(GAME_ASSEMBLY_PTR + 0x2888db0))(cameras);
}

inline int Camera__GetFilterMode(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2888f10))(__this);
}

inline uintptr Camera__get_sceneViewFilterMode(uintptr __this) {
	return ((int(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2888f10))(__this);
}

inline void Camera__Render(uintptr __this) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2889310))(__this);
}

inline void Camera__RenderWithShader(uintptr __this, uintptr shader, IL2CPP_STRING replacementTag) {
	((void(__fastcall*)(uintptr, uintptr, IL2CPP_STRING))(GAME_ASSEMBLY_PTR + 0x28892b0))(__this, shader, replacementTag);
}

inline void Camera__SetupCurrent(uintptr cur) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2889a50))(cur);
}

inline void Camera__CopyFrom(uintptr __this, uintptr other) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x2888b40))(__this, other);
}

inline void Camera__AddCommandBufferImpl(uintptr __this, int evt, uintptr buffer) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x28889a0))(__this, evt, buffer);
}

inline void Camera__RemoveCommandBufferImpl(uintptr __this, int evt, uintptr buffer) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x2889110))(__this, evt, buffer);
}

inline void Camera__AddCommandBuffer(uintptr __this, int evt, uintptr buffer) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x28889f0))(__this, evt, buffer);
}

inline void Camera__RemoveCommandBuffer(uintptr __this, int evt, uintptr buffer) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x2889160))(__this, evt, buffer);
}

inline void Camera__FireOnPreCull(uintptr cam) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2888c80))(cam);
}

inline void Camera__FireOnPreRender(uintptr cam) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2888ce0))(cam);
}

inline void Camera__FireOnPostRender(uintptr cam) {
	((void(__fastcall*)(uintptr))(GAME_ASSEMBLY_PTR + 0x2888c20))(cam);
}

inline bool Camera__TryGetCullingParameters(uintptr __this, bool stereoAware, uintptr cullingParameters) {
	return ((bool(__fastcall*)(uintptr, bool, uintptr))(GAME_ASSEMBLY_PTR + 0x2889a90))(__this, stereoAware, cullingParameters);
}

inline bool Camera__GetCullingParameters_Internal(uintptr camera, bool stereoAware, uintptr cullingParameters, int managedCullingParametersSize) {
	return ((bool(__fastcall*)(uintptr, bool, uintptr, int))(GAME_ASSEMBLY_PTR + 0x2888ea0))(camera, stereoAware, cullingParameters, managedCullingParametersSize);
}

inline void Camera__get_backgroundColor_Injected(uintptr __this, uintptr ret) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288a090))(__this, ret);
}

inline void Camera__set_backgroundColor_Injected(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288abe0))(__this, value);
}

inline void Camera__get_sensorSize_Injected(uintptr __this, UNITYENGINE_VECTOR2 ret) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x288a910))(__this, ret);
}

inline void Camera__set_sensorSize_Injected(uintptr __this, UNITYENGINE_VECTOR2 value) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x288b370))(__this, value);
}

inline void Camera__get_lensShift_Injected(uintptr __this, UNITYENGINE_VECTOR2 ret) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x288a450))(__this, ret);
}

inline void Camera__set_lensShift_Injected(uintptr __this, UNITYENGINE_VECTOR2 value) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR2))(GAME_ASSEMBLY_PTR + 0x288af70))(__this, value);
}

inline void Camera__get_rect_Injected(uintptr __this, uintptr ret) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288a7f0))(__this, ret);
}

inline void Camera__set_rect_Injected(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b2d0))(__this, value);
}

inline void Camera__get_pixelRect_Injected(uintptr __this, uintptr ret) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288a660))(__this, ret);
}

inline void Camera__set_pixelRect_Injected(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b190))(__this, value);
}

inline void Camera__get_cameraToWorldMatrix_Injected(uintptr __this, uintptr ret) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288a130))(__this, ret);
}

inline void Camera__get_worldToCameraMatrix_Injected(uintptr __this, uintptr ret) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288ab30))(__this, ret);
}

inline void Camera__set_worldToCameraMatrix_Injected(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b4f0))(__this, value);
}

inline void Camera__get_projectionMatrix_Injected(uintptr __this, uintptr ret) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288a740))(__this, ret);
}

inline void Camera__set_projectionMatrix_Injected(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b230))(__this, value);
}

inline void Camera__set_nonJitteredProjectionMatrix_Injected(uintptr __this, uintptr value) {
	((void(__fastcall*)(uintptr, uintptr))(GAME_ASSEMBLY_PTR + 0x288b050))(__this, value);
}

inline void Camera__WorldToScreenPoint_Injected(uintptr __this, UNITYENGINE_VECTOR3 position, int eye, UNITYENGINE_VECTOR3 ret) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, int, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2889c60))(__this, position, eye, ret);
}

inline void Camera__WorldToViewportPoint_Injected(uintptr __this, UNITYENGINE_VECTOR3 position, int eye, UNITYENGINE_VECTOR3 ret) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, int, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2889dd0))(__this, position, eye, ret);
}

inline void Camera__ViewportToWorldPoint_Injected(uintptr __this, UNITYENGINE_VECTOR3 position, int eye, UNITYENGINE_VECTOR3 ret) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, int, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2889af0))(__this, position, eye, ret);
}

inline void Camera__ScreenToWorldPoint_Injected(uintptr __this, UNITYENGINE_VECTOR3 position, int eye, UNITYENGINE_VECTOR3 ret) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, int, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2889750))(__this, position, eye, ret);
}

inline void Camera__ScreenToViewportPoint_Injected(uintptr __this, UNITYENGINE_VECTOR3 position, UNITYENGINE_VECTOR3 ret) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR3, UNITYENGINE_VECTOR3))(GAME_ASSEMBLY_PTR + 0x2889690))(__this, position, ret);
}

inline void Camera__ScreenPointToRay_Injected(uintptr __this, UNITYENGINE_VECTOR2 pos, int eye, uintptr ret) {
	((void(__fastcall*)(uintptr, UNITYENGINE_VECTOR2, int, uintptr))(GAME_ASSEMBLY_PTR + 0x2889450))(__this, pos, eye, ret);
}

inline void Camera__GetStereoNonJitteredProjectionMatrix_Injected(uintptr __this, int eye, uintptr ret) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x2888f90))(__this, eye, ret);
}

inline void Camera__GetStereoProjectionMatrix_Injected(uintptr __this, int eye, uintptr ret) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x2889050))(__this, eye, ret);
}

inline void Camera__SetStereoProjectionMatrix_Injected(uintptr __this, int eye, uintptr matrix) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x2889910))(__this, eye, matrix);
}

inline void Camera__SetStereoViewMatrix_Injected(uintptr __this, int eye, uintptr matrix) {
	((void(__fastcall*)(uintptr, int, uintptr))(GAME_ASSEMBLY_PTR + 0x28899b0))(__this, eye, matrix);
}
