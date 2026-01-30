#pragma once
namespace playerhealth {
	void initialize();
	void update();
	void registrate_health(int idx, int health, int tykva);
	int get_player_health(int index);
	bool get_player_tykva(int index);
};

