#pragma once
struct Client;
struct WeaponSystem;

namespace attack_util {

	float get_melee_attack_time(WeaponSystem* ws, Client* client);
	float get_pwid_attack_time(WeaponSystem* ws, Client* client);
	float get_swid_attack_time(WeaponSystem* ws, Client* client);

	bool try_shoot_melee(WeaponSystem* ws, Client* client);
	bool try_shoot_pwid(WeaponSystem* ws, Client* client);
	bool try_shoot_swid(WeaponSystem* ws, Client* client);

	void draw_shoot_delays();

	inline float melee_next_attack_time = 0.0f;
	inline float melee_start_attack_time = 0.0f;
	inline float pwid_next_attack_time = 0.0f;
	inline float pwid_start_attack_time = 0.0f;
	inline float swid_next_attack_time = 0.0f;
	inline float swid_start_attack_time = 0.0f;
};

