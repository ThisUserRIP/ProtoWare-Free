#pragma once
#include "math3d.h"
struct bot_melee_target_data {
	bool success;
	int player_index;
	vec3 enemypos;
	vec3 hitpos;
	vec3 campos;
	vec3 ownpos;
};

namespace direct_melee {
	void initialize();
	bot_melee_target_data get_nearby_player(float weapon_distance);
};

