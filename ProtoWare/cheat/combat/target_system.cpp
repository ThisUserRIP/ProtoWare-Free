#include "pch.h"
#include "target_system.h"
#include "unmanaged_list.hpp"
#include "fast_raycast.h"
#include "config.h"

#include "game.h"
#include "gameoffsets.h"
#include "globals.h"
#include "minhook.h"
#include "movement.h"

#include "component.h"
#include "internal_camera.h"
#include "internal_component.h"
#include "internal_gameobject.h"
#include "internal_transform.h"

#include "stWeaponSystem.hpp"
#include "stPlayerHitboxData.hpp"
#include "stServerPlayersController.hpp"
#include "stServerBotData.hpp"
#include "stClient.hpp"
#include "stVP_FPController.hpp"
#include "stVP_FPCamera.hpp"
#include "stBotPoseController.hpp"

#include "mdClient.hpp"
#include "mdCamera.hpp"
#include "mdRandom.hpp"
#include "mdPhysics.hpp"
#include "mdRaycastHit.hpp"
#include "mdParticleManager.hpp"
#include "mdWeaponSystem.hpp"
#include "mdObscuredInt.hpp"

unmanaged_list<vec3> target_system_player_verticles;
unmanaged_list<vec3> target_system_camera_verticles;
unmanaged_list<vec3> target_system_advanced_player_verticles;

void target_system__try_generate_player_verticles();
void target_system__try_generate_camera_verticles();
void target_system__try_generate_advanced_player_verticles();

void target_system::initialize() {
    target_system__try_generate_player_verticles();
    target_system__try_generate_camera_verticles();
    target_system__try_generate_advanced_player_verticles();
}

void target_system::update() {
    Client* client = game::get_client();
    ServerPlayersController* pcontroller = game::get_pcontroller();
    if (!client || !pcontroller) return;

    float dist = 0.0f;
    WeaponSystem* ws = (WeaponSystem*)pcontroller->csws;
    if (!ws) dist = 256.0f;
    else {
        if (ws->CURRENT_WEAPON_ID == ws->mwid)
            dist = 4.0f;
        else dist = 256.0f;
    }

    //if (game::get_mode() == E_MODE_MELEE) {
    //    auto melee_target = direct_melee::
    //}
    cached_target = get_nearby_player(dist);
    target_valid = (cached_target.bot_data != nullptr);
    current_target_index = target_valid ? cached_target.bot_index : -1;
}

bot_aim_target_data target_system::get_cached_target() {
    return cached_target;
}

bot_aim_target_data target_system::get_nearby_player(float weapon_distance) {
    ServerPlayersController* pcontroller = game::get_pcontroller();
    Client* client = game::get_client();
    if (!client || !pcontroller || !pcontroller->RemotePlayersList || !pcontroller->FPController) return {};

    vp_FPController* fpcontroller = (vp_FPController*)pcontroller->FPController;
    if (!fpcontroller->m_FPSCamera) return {};
    vp_FPCamera* fpcamera = (vp_FPCamera*)fpcontroller->m_FPSCamera;
    if (!fpcamera->MyCamera) return {};
    component* camera = (component*)fpcamera->MyCamera;
    if (!camera || !camera->internal_component) return {};
    internal_camera* internalcam = (internal_camera*)camera->internal_component;
    if (!internalcam) return {};

    if (!client->__internalObj || isptrinvalid((uintptr)client->__internalObj)) return {};
    internal_component* clientInternal = (internal_component*)client->__internalObj;
    if (!clientInternal->gameobject) return {};
    internal_transform* clientTransform = clientInternal->gameobject->get_transform();
    if (!clientTransform) return {};
    vec3 ownpos = clientTransform->get_kernel_pos();

    fast_raycast::update();

    matrix4x4 projmatrix = internalcam->projmatrix;
    matrix4x4 viewmatrix = internalcam->viewmatrix;
    matrix4x4 vpmatrix = projmatrix * viewmatrix;

    tarray* players = pcontroller->RemotePlayersList;

    vec2 screen_center = vec2(screen_width / 2, screen_height / 2);
    float best_fov = config::aim_fov + 1;

    bot_aim_target_data aim_targeted_bot;
    aim_targeted_bot.bot_data = 0;
    aim_targeted_bot.bot_index = 0;
    aim_targeted_bot.compromated_hit = false;
    aim_targeted_bot.compromated_campos = false;

    component* mainCam = (component*)Camera__get_main();
    if (!mainCam || !mainCam->internal_component) return aim_targeted_bot;
    vec3 screenCenter = vec3(screen_width / 2.0f, screen_height / 2.0f, 0);

    internal_camera* mainCamInternal = (internal_camera*)mainCam->internal_component;
    if (!mainCamInternal || !mainCamInternal->go) return aim_targeted_bot;
    internal_transform* camera_transform = mainCamInternal->go->get_transform();
    if (!camera_transform) return aim_targeted_bot;

    vec3 original_origin = camera_transform->get_pos();
    vec3 center_origin = config::use_server_positions ? movement::own_server_position : camera_transform->get_kernel_pos();

    if (!pcontroller->csws) return aim_targeted_bot;
    int layermask = ((WeaponSystem*)pcontroller->csws)->layerMask;

#define _raycast(_start, _end) fast_raycast::slow_raycast(_start, _end, layermask)
    //#define _raycast(_start, _end) fast_raycast::linecast(_start, _end)
    //#define _raycast(_start, _end) fast_raycast::linecast_chk(_start, _end)

    ServerBotData* ownbot = (ServerBotData*)players->element(client->myindex);
    deffor(i, players->max_size) {
        if (i == client->myindex) continue;

        ServerBotData* bot = (ServerBotData*)players->element(i);
        if (isptrinvalid((uintptr)bot) || isptrinvalid((uintptr)bot->Name) || isptrinvalid(bot->botPoser)) continue;
        if (!bot->Active || bot->Dead) continue;
        if (bot->Team == ownbot->Team) continue;
        if (config::InFriends(bot->Name)) continue;
        bool in_targets = config::InTargets(bot->Name);

        component* botposer = (component*)bot->botPoser;
        BotPoseController* poseController = (BotPoseController*)botposer;
        if (!botposer->internal_component) continue;
        if (poseController->isProtected) continue;

        internal_transform* transform = ((internal_component*)botposer->internal_component)->gameobject->get_transform();
        vec3 position = config::use_server_positions ? bot->position : transform->get_kernel_pos();
        vec3 head_position = position + vec3(0, 1.63f, 0);
        vec2 scrvec = vpmatrix.worldtoscreen(position);

        float fovdist = screen_center.get_distance(scrvec);
        if (fovdist > config::aim_fov) continue;
        if (fovdist > best_fov) continue;

        if (ownpos.get_distance(head_position) > weapon_distance)
            goto PROCESS_COMPRAMETED_HIT;

        if (_raycast(original_origin, head_position)) {
        PROCESS_COMPRAMETED_HIT:
            if (config::walls_stage1) {
                for (vec3 vert : in_targets ? target_system_advanced_player_verticles : target_system_player_verticles) {
                    vec3 hit_pos = (position + vert);
                    float vertdist = hit_pos.get_distance(original_origin);
                    if (vertdist > weapon_distance) continue;

                    if (_raycast(original_origin, hit_pos))
                        continue;

                    best_fov = fovdist;

                    aim_targeted_bot.bot_index = i;
                    aim_targeted_bot.bot_data = bot;
                    aim_targeted_bot.bot_pos = position;
                    aim_targeted_bot.compromated_hit = true;
                    aim_targeted_bot.compromated_campos = true;
                    aim_targeted_bot.hit_pos = hit_pos;
                    aim_targeted_bot.cam_pos = original_origin;
                    if (in_targets)
                        return aim_targeted_bot;
                    goto ITER_END;
                }
            }
            if (config::walls_stage2) {
                for (vec3 vert : target_system_camera_verticles) {
                    vec3 modcampos = center_origin + vert;
                    if (modcampos.get_distance(head_position) > weapon_distance) continue;

                    if (fast_raycast::contains_block(modcampos + vec3(0.5f, 0.5f, 0.5f))) continue;
                    if (_raycast(modcampos, head_position))
                        continue;

                    best_fov = fovdist;

                    aim_targeted_bot.bot_index = i;
                    aim_targeted_bot.bot_data = bot;
                    aim_targeted_bot.bot_pos = position;
                    aim_targeted_bot.compromated_hit = true;
                    aim_targeted_bot.compromated_campos = true;
                    aim_targeted_bot.cam_pos = modcampos;
                    aim_targeted_bot.hit_pos = head_position;
                    if (in_targets)
                        return aim_targeted_bot;
                    goto ITER_END;
                }
            }
            if (config::walls_stage3) {
                for (vec3 cam_vert : target_system_camera_verticles) {
                    for (vec3 hit_vert : in_targets ? target_system_advanced_player_verticles : target_system_player_verticles) {
                        vec3 modcampos = center_origin + cam_vert;
                        vec3 modhitpos = position + hit_vert;
                        if (modcampos.get_distance(modhitpos) > weapon_distance) continue;

                        if (fast_raycast::contains_block(modcampos + vec3(0.5f, 0.5f, 0.5f))) continue;
                        //if (fast_raycast::contains_block(modhitpos + vec3(0.5f, 0.5f, 0.5f))) continue;
                        if (_raycast(modcampos, modhitpos))
                            continue;

                        best_fov = fovdist;

                        aim_targeted_bot.bot_index = i;
                        aim_targeted_bot.bot_data = bot;
                        aim_targeted_bot.bot_pos = position;
                        aim_targeted_bot.compromated_hit = true;
                        aim_targeted_bot.compromated_campos = true;
                        aim_targeted_bot.hit_pos = modhitpos;
                        aim_targeted_bot.cam_pos = modcampos;
                        if (in_targets)
                            return aim_targeted_bot;
                        goto ITER_END;
                    }
                }
            }
        ITER_END:
            continue;
        }

        best_fov = fovdist;

        aim_targeted_bot.compromated_campos = true;
        aim_targeted_bot.compromated_hit = true;
        aim_targeted_bot.bot_index = i;
        aim_targeted_bot.bot_data = bot;
        aim_targeted_bot.bot_pos = position;
        aim_targeted_bot.cam_pos = original_origin;
        aim_targeted_bot.hit_pos = head_position;
        if (in_targets)
            return aim_targeted_bot;
    }

    target_system::current_target_index = aim_targeted_bot.bot_data ? aim_targeted_bot.bot_index : -1;

    return aim_targeted_bot;
}

void target_system__generate_sphere(float sphere_size, int segments, unmanaged_list<vec3>& verticles) {
    int vertices_count = (segments + 1) * (segments + 1);
    if (!verticles.set_reserve_space_checked(vertices_count)) return;
    verticles.clearfast();
    verticles.count = vertices_count;
    int vertex_index = 0;

    for (int lat = 0; lat <= segments; lat++)
    {
        float normalizedLatitude = lat / (float)segments;
        float theta = normalizedLatitude * PI;

        for (int lon = 0; lon <= segments; lon++)
        {
            float normalizedLongitude = lon / (float)segments;
            float phi = normalizedLongitude * 2 * PI;

            float x = sinf(theta) * cosf(phi) * sphere_size;
            float y = cosf(theta) * sphere_size;
            float z = sinf(theta) * sinf(phi) * sphere_size;

            verticles[vertex_index] = vec3(x, y, z);

            vertex_index++;
        }
    }
}
void target_system__try_generate_player_verticles() {
    target_system_player_verticles.clearfast();

    target_system_player_verticles.push(vec3(0, 0, 0));
    target_system_player_verticles.push(vec3(0, 1.63f, 0));

#define add_direct_point(width, height) \
    target_system_player_verticles.push(vec3(0, height, 0)); \
    target_system_player_verticles.push(vec3(0, -height, 0));\
    target_system_player_verticles.push(vec3(width, 0, 0)); \
    target_system_player_verticles.push(vec3(0, 0, width)); \
    target_system_player_verticles.push(vec3(-width, 0, 0)); \
    target_system_player_verticles.push(vec3(0, 0, -width));

    add_direct_point(0.8f, 1.0f);
    add_direct_point(1.5f, 1.5f);
    add_direct_point(2.5f, 2.5f);
    //add_direct_point(2.75f, 2.75f);
    add_direct_point(3.35f, 3.35f);
    add_direct_point(3.55f, 3.55f);
}

void target_system__try_generate_camera_verticles() {
    target_system_camera_verticles.clearfast();

    target_system_camera_verticles.push(vec3(0, 0.1f, 0));
    target_system_camera_verticles.push(vec3(0, 1.63f, 0));
    target_system_camera_verticles.push(vec3(0, 2.2f, 0));
    target_system_camera_verticles.push(vec3(0, 2.75f, 0));
    target_system_camera_verticles.push(vec3(0, 3.45f, 0));
    target_system_camera_verticles.push(vec3(0, -1.05f, 0));
    target_system_camera_verticles.push(vec3(0, -1.6f, 0));
    target_system_camera_verticles.push(vec3(0, -2.2f, 0));

#define add_direct_point(width, height) \
    target_system_camera_verticles.push(vec3(0, height, 0)); \
    target_system_camera_verticles.push(vec3(0, -height, 0));\
    target_system_camera_verticles.push(vec3(width, 0, 0)); \
    target_system_camera_verticles.push(vec3(0, 0, width)); \
    target_system_camera_verticles.push(vec3(-width, 0, 0)); \
    target_system_camera_verticles.push(vec3(0, 0, -width));

    add_direct_point(0.755f, 1.05f);
    add_direct_point(1.55f, 1.55f);
    add_direct_point(2.25f, 2.55f);
}

void target_system__try_generate_advanced_player_verticles() {
    target_system_advanced_player_verticles.clearfast();

    target_system_advanced_player_verticles.push(vec3(0, 0.1f, 0));
    target_system_advanced_player_verticles.push(vec3(0, 1.63f, 0));

#define add_direct_point(width, height) \
    target_system_advanced_player_verticles.push(vec3(0, height, 0)); \
    target_system_advanced_player_verticles.push(vec3(0, -height, 0));\
    target_system_advanced_player_verticles.push(vec3(width, 0, 0)); \
    target_system_advanced_player_verticles.push(vec3(0, 0, width)); \
    target_system_advanced_player_verticles.push(vec3(-width, 0, 0)); \
    target_system_advanced_player_verticles.push(vec3(0, 0, -width));

#define add_avard_point(width, height) \
    target_system_advanced_player_verticles.push(vec3(width, 0, width)); \
    target_system_advanced_player_verticles.push(vec3(width, 0, -width)); \
    target_system_advanced_player_verticles.push(vec3(-width, 0, width)); \
    target_system_advanced_player_verticles.push(vec3(-width, 0, -width)); \
    target_system_advanced_player_verticles.push(vec3(width, height, width)); \
    target_system_advanced_player_verticles.push(vec3(width, height, -width)); \
    target_system_advanced_player_verticles.push(vec3(-width, height, width)); \
    target_system_advanced_player_verticles.push(vec3(-width, height, -width)); \
    target_system_advanced_player_verticles.push(vec3(width, -height, width)); \
    target_system_advanced_player_verticles.push(vec3(width, -height, -width)); \
    target_system_advanced_player_verticles.push(vec3(-width, -height, width)); \
    target_system_advanced_player_verticles.push(vec3(-width, -height, -width));

    add_direct_point(0.8f, 1.05f);
    add_direct_point(1.55f, 1.5f);
    add_direct_point(2.55f, 2.5f);
    add_direct_point(3.35f, 3.35f);
    add_direct_point(3.75f, 3.75f);

    add_avard_point(0.8f, 1.05f);
    add_avard_point(1.55f, 1.5f);
    add_avard_point(2.55f, 2.5f);
    add_avard_point(3.35f, 3.35f);
    add_avard_point(3.55f, 3.55f);
}