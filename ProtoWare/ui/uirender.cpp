#include "pch.h"
#include "globals.h"
#include "uirender.h"
#include "uimenu.h"

#include "playeresp.h"
#include "visuals.h"
#include "movement.h"
#include "hitnotify.h"
#include "targethud.h"
#include "tracers.h"
#include "attack_util.h"

#include "mdScreen.hpp"

void uirender::draw() {
	screen_width = Screen__get_width();
	screen_height = Screen__get_height();

	visuals::update();
	playeresp::draw();
	targethud::draw();
	hitnotify::draw();
	tracers::draw();
	attack_util::draw_shoot_delays();

	uimenu::draw();
	uimenu::DrawSpectatorList();
}