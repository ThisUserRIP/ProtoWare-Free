#pragma once
#include "math3d.h"

struct ServerBotData;

struct bot_aim_target_data {
    ServerBotData* bot_data;
    vec3 bot_pos;
    vec3 bot_snd_pos;
    int bot_index;

    bool compromated_hit;
    bool compromated_campos;
    vec3 hit_pos;
    vec3 cam_pos;

    bot_aim_target_data() {
        bot_data = 0;
        bot_index = 0;
    }
};

namespace target_system {
    inline int current_target_index = -1;
    inline bot_aim_target_data cached_target;
    inline bool target_valid = false;

    void initialize();
    void update();  
    bot_aim_target_data get_cached_target();  
    bot_aim_target_data get_nearby_player(float weapon_distance);
};

