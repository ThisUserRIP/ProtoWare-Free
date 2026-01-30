#include "pch.h"
#include "game.h"
#include "updatecycle.h"

#include "config.h"
#include "globals.h"
#include "minhook.h"

#include "movement.h"
#include "visuals.h"
#include "aim.h"
#include "target_system.h"
#include "playerhealth.h"

typedef __int64(__fastcall* DELEGATE_UnityBehaviourUpdate)();

DELEGATE_UnityBehaviourUpdate unitybehaviourupdate_o;

__int64 hkUpdateScriptRunBehaviour();
void updatecycle::initialize() {
	// abusing InitPlayerLoopCallbacks_::_2_::UpdateScriptRunBehaviourUpdateRegistrator::Forward
	MH_Initialize();
	MH_CreateHook((void*)(unityplayer + 0x4B2270), &hkUpdateScriptRunBehaviour, (void**)&unitybehaviourupdate_o);
	MH_EnableHook((void*)(unityplayer + 0x4B2270));
}

void updatecycle::update() {
	visuals::unityupdate();	
	movement::update();
	aim::update();
	playerhealth::update();
	if (config::aimbot_enabled) {
		target_system::update();
	}
	else {
		target_system::current_target_index = -1;
		target_system::target_valid = false;
	}
}

__int64 hkUpdateScriptRunBehaviour() {
	updatecycle::update();
	return unitybehaviourupdate_o();
}