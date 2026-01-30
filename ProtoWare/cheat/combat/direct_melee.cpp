#include "pch.h"
#include "direct_melee.h"
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

void direct_melee::initialize() {

}

bot_melee_target_data direct_melee::get_nearby_player(float weapon_distance) {
    ServerPlayersController* pcontroller = game::get_pcontroller();
    Client* client = game::get_client();
    if (!client || !pcontroller || !pcontroller->RemotePlayersList || !pcontroller->FPController) return {};

    vp_FPController* fpcontroller = (vp_FPController*)pcontroller->FPController;
    if (!fpcontroller->m_FPSCamera) return {};
    vp_FPCamera* fpcamera = (vp_FPCamera*)fpcontroller->m_FPSCamera;
    if (!fpcamera->MyCamera) return {};
    component* camera = (component*)fpcamera->MyCamera;
    internal_camera* internalcam = (internal_camera*)camera->internal_component;

    fast_raycast::update();

    matrix4x4 projmatrix = internalcam->projmatrix;
    matrix4x4 viewmatrix = internalcam->viewmatrix;
    matrix4x4 vpmatrix = projmatrix * viewmatrix;

    tarray* players = pcontroller->RemotePlayersList;

    vec2 screen_center = vec2(screen_width / 2, screen_height / 2);
    float best_fov = config::aim_fov + 1;

    bot_melee_target_data aim_targeted_bot;
    aim_targeted_bot.success = false;

    component* mainCam = (component*)Camera__get_main();
    vec3 screenCenter = vec3(screen_width / 2.0f, screen_height / 2.0f, 0);

    internal_transform* camera_transform = ((internal_camera*)mainCam->internal_component)->go->get_transform();
    vec3 original_origin = camera_transform->get_pos();
    vec3 center_origin = config::use_server_positions ? movement::own_server_position : camera_transform->get_kernel_pos();
    int layermask = ((WeaponSystem*)pcontroller->csws)->layerMask;
    layermask &= 0x3FFFFBFF;

#define _raycast(_start, _end) fast_raycast::slow_raycast(_start, _end, layermask)
    //#define _raycast(_start, _end) fast_raycast::linecast(_start, _end)

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
        vec3 smup_position = position + vec3(0, 0.1f, 0);
        vec3 head_position = position + vec3(0, 1.63f, 0);
        vec2 scrvec = vpmatrix.worldtoscreen(position);

        float fovdist = screen_center.get_distance(scrvec);
        if (fovdist > config::aim_fov) continue;
        if (fovdist > best_fov) continue;

        if (center_origin.get_distance(head_position) > weapon_distance)
            goto PROCESS_COMPRAMETED_HIT;

        if (_raycast(original_origin, head_position)) {
        PROCESS_COMPRAMETED_HIT:

        HITPOS_NEARBY_CHECK:
            if (center_origin.get_distance(position) < config::nearby_hitpos_dist) {
                aim_targeted_bot.success = true;
                aim_targeted_bot.player_index = i;
                aim_targeted_bot.campos = center_origin;
                aim_targeted_bot.ownpos = center_origin;
                aim_targeted_bot.hitpos = position;
                aim_targeted_bot.enemypos = position;
                if (in_targets)
                    return aim_targeted_bot;
                continue;
            }
        SINGLE_CAM_PADDING:
            vec3 cam_padding_dir = (head_position - center_origin).get_normalized();
            for (float f = config::cam_single_padding_step; f < config::single_max_cam_padding; f += config::cam_single_padding_step) {
                float rf = std::min(f, config::single_max_cam_padding);
                vec3 mod_campos = center_origin + (cam_padding_dir * rf);
                if (fast_raycast::contains_block(mod_campos + vec3(0.5f, 0.5f, 0.5f))) continue;
                if (mod_campos.get_distance(head_position) < weapon_distance && !_raycast(mod_campos, head_position)) {
                    aim_targeted_bot.success = true;
                    aim_targeted_bot.player_index = i;
                    aim_targeted_bot.campos = mod_campos;
                    aim_targeted_bot.ownpos = center_origin;
                    aim_targeted_bot.hitpos = head_position;
                    aim_targeted_bot.enemypos = head_position;
                    if (in_targets)
                        return aim_targeted_bot;
                    continue;
                }
                if (mod_campos.get_distance(smup_position) < weapon_distance && !_raycast(mod_campos, smup_position)) {
                    aim_targeted_bot.success = true;
                    aim_targeted_bot.player_index = i;
                    aim_targeted_bot.campos = mod_campos;
                    aim_targeted_bot.ownpos = center_origin;
                    aim_targeted_bot.hitpos = smup_position;
                    aim_targeted_bot.enemypos = smup_position;
                    if (in_targets)
                        return aim_targeted_bot;
                    continue;
                }
            }
        CAM_AND_HITPOS_PADDING:
            vec3 hitpos_padding_dir = (center_origin - position).get_normalized();
            cam_padding_dir = (position - center_origin).get_normalized();

            if (config::imperative_direct_melee) {
                for (float f2 = config::hitpos_padding_step; f2 < config::max_hitpos_padding; f2 += config::hitpos_padding_step) {
                    for (float f = config::cam_padding_step; f < config::max_cam_padding; f += config::cam_padding_step) {
                        //f = std::min(f2, config::max_cam_padding);
                        //f2 = std::min(f2, config::max_hitpos_padding);

                        vec3 mod_campos = center_origin + (cam_padding_dir * f);
                        vec3 mod_hitpos = smup_position + (hitpos_padding_dir * f2);
                        if (mod_campos.get_distance(mod_hitpos) < weapon_distance && !_raycast(mod_campos, mod_hitpos)) {
                            aim_targeted_bot.success = true;
                            aim_targeted_bot.player_index = i;
                            aim_targeted_bot.campos = mod_campos;
                            aim_targeted_bot.ownpos = center_origin;
                            aim_targeted_bot.hitpos = mod_hitpos;
                            aim_targeted_bot.enemypos = smup_position;
                            if (in_targets)
                                return aim_targeted_bot;
                            break;
                        }
                    }

                }
            }
            else {
                vec3 mod_campos;
                vec3 mod_hitpos;

                bool finded = false;
                float f2 = config::hitpos_padding_step;
                float f = config::cam_padding_step;
                while (f <= config::max_cam_padding && f2 <= config::max_hitpos_padding) {

                    if (config::reversive_direct_melee_check) {
                        float rf = std::min(f, config::max_cam_padding);
                        float rf2 = std::min(f2, config::max_hitpos_padding);
                        mod_campos = center_origin + (cam_padding_dir * rf);
                        mod_hitpos = smup_position + (hitpos_padding_dir * rf2);
                        if (mod_campos.get_distance(mod_hitpos) < weapon_distance && !fast_raycast::contains_block(mod_campos + vec3(0.5f, 0.5f, 0.5f)) && !_raycast(mod_campos, mod_hitpos)) {
                            aim_targeted_bot.success = true;
                            aim_targeted_bot.player_index = i;
                            aim_targeted_bot.campos = mod_campos;
                            aim_targeted_bot.ownpos = center_origin;
                            aim_targeted_bot.hitpos = mod_hitpos;
                            aim_targeted_bot.enemypos = smup_position;
                            finded = true;
                            if (in_targets)
                                return aim_targeted_bot;
                            break;
                        }

                        f += config::cam_padding_step;
                        rf = std::min(f, config::max_cam_padding);
                        mod_campos = center_origin + (cam_padding_dir * rf);
                        if (mod_campos.get_distance(mod_hitpos) < weapon_distance && !fast_raycast::contains_block(mod_campos + vec3(0.5f, 0.5f, 0.5f)) && !_raycast(mod_campos, mod_hitpos)) {
                            aim_targeted_bot.success = true;
                            aim_targeted_bot.player_index = i;
                            aim_targeted_bot.campos = mod_campos;
                            aim_targeted_bot.ownpos = center_origin;
                            aim_targeted_bot.hitpos = mod_hitpos;
                            aim_targeted_bot.enemypos = smup_position;
                            finded = true;
                            if (in_targets)
                                return aim_targeted_bot;
                            break;
                        }

                        f2 += config::hitpos_padding_step;
                    }
                    else {
                        float rf = std::min(f, config::max_cam_padding);
                        float rf2 = std::min(f2, config::max_hitpos_padding);
                        mod_campos = center_origin + (cam_padding_dir * rf);
                        mod_hitpos = smup_position + (hitpos_padding_dir * rf2);
                        if (mod_campos.get_distance(mod_hitpos) < weapon_distance && !fast_raycast::contains_block(mod_campos + vec3(0.5f, 0.5f, 0.5f)) && !_raycast(mod_campos, mod_hitpos)) {
                            aim_targeted_bot.success = true;
                            aim_targeted_bot.player_index = i;
                            aim_targeted_bot.campos = mod_campos;
                            aim_targeted_bot.ownpos = center_origin;
                            aim_targeted_bot.hitpos = mod_hitpos;
                            aim_targeted_bot.enemypos = smup_position;
                            finded = true;
                            if (in_targets)
                                return aim_targeted_bot;
                            break;
                        }

                        f2 += config::hitpos_padding_step;
                        rf2 = std::min(f2, config::max_hitpos_padding);
                        mod_hitpos = smup_position + (hitpos_padding_dir * rf2);
                        if (mod_campos.get_distance(mod_hitpos) < weapon_distance && !fast_raycast::contains_block(mod_campos + vec3(0.5f, 0.5f, 0.5f)) && !_raycast(mod_campos, mod_hitpos)) {
                            aim_targeted_bot.success = true;
                            aim_targeted_bot.player_index = i;
                            aim_targeted_bot.campos = mod_campos;
                            aim_targeted_bot.ownpos = center_origin;
                            aim_targeted_bot.hitpos = mod_hitpos;
                            aim_targeted_bot.enemypos = smup_position;
                            finded = true;
                            if (in_targets)
                                return aim_targeted_bot;
                            break;
                        }

                        f += config::cam_padding_step;
                    }
                }
                if (finded) // stupid
                    continue;
            }

            continue;
        }

        best_fov = fovdist;

        aim_targeted_bot.success = true;
        aim_targeted_bot.player_index = i;
        aim_targeted_bot.campos = original_origin;
        aim_targeted_bot.ownpos = center_origin;
        aim_targeted_bot.hitpos = head_position;
        aim_targeted_bot.enemypos = head_position;
    }

    return aim_targeted_bot;
}