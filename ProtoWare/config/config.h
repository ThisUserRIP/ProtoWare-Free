#pragma once
#include "unmanaged_list.hpp"
#include "monostring.h"
#include <map>
#include <deque>

struct cheat_friend {
    char* nickname_u8;
    wchar_t* nickname_u16;
};

namespace config {
    // Aimbot
    inline bool aimbot_enabled = true;
    inline float aim_fov = 500;
    inline bool walls_stage1 = false;
    inline bool walls_stage2 = false;
    inline bool walls_stage3 = true;
    inline bool cam_rot_spoofing = true;
    inline bool lookpoint_spoofing = false;
    inline bool own_look_y_spoofing = true;
    inline bool custom_attack = true;
    inline bool center_enemypos = true;
    inline bool imperative_direct_melee = false;
    inline bool reversive_direct_melee_check = false;
    inline bool double_secondary_hit = false;
    inline bool use_server_positions = true;

    // Direct melee
    inline float nearby_hitpos_dist = 2.75f;
    inline float single_max_cam_padding = 2.8f;
    inline float cam_single_padding_step = 0.4f;
    inline float max_cam_padding = 3.7f;
    inline float cam_padding_step = 0.55f;
    inline float max_hitpos_padding = 3.7f;
    inline float hitpos_padding_step = 0.55f;

    // ESP
    inline bool backtrack_enable = false;
    inline bool show_targeted = false;
    inline bool show_friends = false;
    inline bool esp_enable = false;        
    inline bool esp_team_check = false;   
    inline bool esp_box_2d = false;  
    inline bool esp_box_corner = false;  
    inline bool esp_box_3d = false; 
    inline bool esp_box_fill = false;    
    inline bool esp_snaplines = false;
    inline int esp_snapline_type = 0;
    inline const char* snapline_types[] = { "Bottom", "Center", "Top" };
    inline bool esp_health_bar = false;    
    inline bool esp_skeleton = false;      
    inline bool esp_skeleton_joints = false;
    inline bool esp_head_circle = false;   
    inline bool esp_chams = false;   
    inline bool esp_chams_flat = true;
    inline bool esp_name = false;        
    inline bool esp_distance = false;   
    inline bool esp_flags = false;
    inline bool show_targethud = true;
    inline float targethud_pos_x = -1.0f;
    inline float targethud_pos_y = -1.0f;
    inline bool show_hitnotify = true;
    inline bool esp_glow = false;      
    inline bool esp_china_hat = false; 
    inline bool esp_trails = false;

    // Movement
    inline bool chat_spam = false;
    inline bool noWeaponStopMove = false;
    inline bool speedModifier = false;
    inline bool stopSendPosition = false;
    inline bool allwaysShift = false;
    inline bool fakeBackward = false;
    inline bool spin = false;
    inline bool fakeDuck = false;
    inline bool fakeDown = false;
    inline bool ghost = false;
    inline bool jumpModifier = false;
    inline bool gravModifier = false;
    inline bool strafec = false;
    inline bool fakeLag = false;
    inline float speedm = 0.2475f;
    inline float jumpm = 0.2f;
    inline float gravm = 0.2f;
    inline float sendPositionSpeed = 0.0285f;
    inline float timeSendPadding = 0.0f;
    inline float EulerBackward = 0.f;
    inline int aa_type = 0;
    inline int aa_pitch_type = 0;
    inline int fakeLagMode = 0;
    inline bool auto_team_switch = false;
    inline bool auto_respawn = false;
    inline bool magnet_player = false;
    inline bool melee_strafe = false;
    inline bool hideWeapon = false;
    inline bool spider = false;
    inline float dist_strafe = 2.5f;
    inline float strafeSpeed = 2.5f;
    inline int auto_team_select = 0;

    inline bool destroy_speed = false;
    inline float radiusBuild = 2.f;
    inline float MaxPackets = 2.f;
    inline float SpeedBuild = 0.1f;
    inline int buildMode = 0;
    inline int nukerMode = 0;

    // Weapon
    inline bool fast_reload = false;
    inline bool auto_fast_reload = true;
    inline bool spinupMinigun = false;
    inline bool instantChangeWeapon = false;

    // FOV Circle
    inline bool show_fov_circle = false;
    inline float fov_color[3] = { 1.0f, 0.0f, 0.0f };
    inline bool fov_rgb = false;
    inline bool show_spectators = false;

    // Custom FOV
    inline bool custom_fov = true;
    inline float game_fov = 120.0f;
    inline float zoom_fov = 90.0f;

    // Friend list
    inline unmanaged_list<cheat_friend> friends;
    inline unmanaged_list<cheat_friend> targets;

    inline bool InFriends(monostring* mstr) {
        for (cheat_friend fr : config::friends) {
            if (wcscmp(fr.nickname_u16, mstr->wstring) == 0)
                return true;
        }
        return false;
    }
    inline bool InTargets(monostring* mstr) {
        for (cheat_friend fr : config::targets) {
            if (wcscmp(fr.nickname_u16, mstr->wstring) == 0)
                return true;
        }
        return false;
    }
};
