#include "pch.h"
#include "tracers.h"

#include "component.h"
#include "internal_component.h"
#include "internal_camera.h"
#include "internal_transform.h"
#include "internal_gameobject.h"
#include "game.h"

#include "imgui.h"
#include "unmanaged_list.hpp"

#include "mdTime.hpp"
#include "stServerPlayersController.hpp"
#include "stVP_FPController.hpp"
#include "stVP_FPCamera.hpp"

struct internal_draw_tracer {
	vec3 start;
	vec3 end;
	float start_time;
	float end_time;
};

unmanaged_list<internal_draw_tracer> internal_tracers_list;

void tracers::draw() {
#define TOIMV(a) ImVec2(a.x, a.y)

	ServerPlayersController* pcontroller = game::get_pcontroller();
	if (!pcontroller || !pcontroller->RemotePlayersList || !pcontroller->FPController) return;

	vp_FPController* fpcontroller = (vp_FPController*)pcontroller->FPController;
	if (!fpcontroller->m_FPSCamera) return;
	vp_FPCamera* fpcamera = (vp_FPCamera*)fpcontroller->m_FPSCamera;
	if (!fpcamera->MyCamera) return;
	component* camera = (component*)fpcamera->MyCamera;
	internal_camera* internalcam = (internal_camera*)camera->internal_component;
	if (isptrinvalid((uintptr)internalcam)) return;

	internal_transform* cam_trs = internalcam->go->get_transform();
	vec3 cam_pos = cam_trs->get_pos();
	vec3 cam_forward = vec3(fpcamera->m_Pitch, fpcamera->m_Yaw, 0).get_forward();

	matrix4x4 projmatrix = internalcam->projmatrix;
	matrix4x4 viewmatrix = internalcam->viewmatrix;
	matrix4x4 vpmatrix = projmatrix * viewmatrix;

	ImDrawList* draw_list = ImGui::GetForegroundDrawList();

	float current_time = Time__get_realtimeSinceStartup();
	revfor(i, internal_tracers_list.count) {
		internal_draw_tracer& tracer = internal_tracers_list[i];
		if (tracer.end_time < current_time) {
			internal_tracers_list.delete_at_fast(i);
			continue;
		}
		
		vec3 firstBulletPosition = tracer.start;
		vec3 secondBulletPosition = tracer.end;

		float w1 = vec3::compute_w(firstBulletPosition, vpmatrix);
		float w2 = vec3::compute_w(secondBulletPosition, vpmatrix);

		if (w1 < 0 && w2 < 0)
			continue;

		if (w1 < 0) firstBulletPosition = vec3::clip_behind_camera(secondBulletPosition, firstBulletPosition, cam_pos, cam_forward);
		if (w2 < 0) secondBulletPosition = vec3::clip_behind_camera(firstBulletPosition, secondBulletPosition, cam_pos, cam_forward);

		vec2 firstBulletScr = vpmatrix.worldtoscreen(firstBulletPosition);
		vec2 secondBulletScr = vpmatrix.worldtoscreen(secondBulletPosition);

		if (firstBulletScr.x == 0 && firstBulletScr.y == 0) continue;
		if (secondBulletScr.x == 0 && secondBulletScr.y == 0) continue;

		float percent = (tracer.end_time - current_time) / (tracer.end_time - tracer.start_time);
		draw_list->AddLine(TOIMV(firstBulletScr), TOIMV(secondBulletScr), IM_COL32(0, 255, 255, (int)(255.0f * percent)), 1.0f);
		
	}
}
void tracers::punch(vec3 start, vec3 end) {
	float realtime = Time__get_realtimeSinceStartup();
	internal_tracers_list.push({ start, end, realtime, realtime + 4.0f });
}