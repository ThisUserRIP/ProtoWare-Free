#include "pch.h"
#include "uimenu.h"
#include "imgui.h"
#include "config.h"

#include "game.h"
#include "monostring.h"

#include "stServerPlayersController.hpp"
#include "stServerBotData.hpp"
#include "stPlayerProfile.hpp"

#include <Vector>
#include <unordered_set>
#include <filesystem>
#include <string>

static bool uimenu_show = false;
static int current_tab = 0;
static float rgb_hue = 0.0f;
char uimenu__monostring_buf[128];

namespace fs = std::filesystem;
typedef monostring* (*t_il2cpp_string_new)(const char* str);

monostring* CreateGameString(const char* str) {
    static t_il2cpp_string_new func_ptr = nullptr;

    if (!func_ptr) {
        HMODULE hGame = GetModuleHandleA("GameAssembly.dll");
        if (hGame) {
            func_ptr = (t_il2cpp_string_new)GetProcAddress(hGame, "il2cpp_string_new");
        }
    }

    if (func_ptr) {
        return func_ptr(str);
    }
    return nullptr;
}
inline char cfg_input[64] = "";
inline std::vector<std::string> cfg_files;
inline int cfg_idx = -1;
inline std::string cfg_path = "C:\\ANTICHEATER";

static char auth_buf[256];
char* to_utf8(monostring* str) {
    if (!str) return (char*)"(null)";
    WideCharToMultiByte(CP_UTF8, 0, str->wstring, -1, auth_buf, 256, 0, 0);
    return auth_buf;
}

void RefreshList() {
    cfg_files.clear();
    if (!fs::exists(cfg_path)) fs::create_directories(cfg_path);
    for (const auto& entry : fs::directory_iterator(cfg_path)) {
        if (entry.path().extension() == ".ini") {
            cfg_files.push_back(entry.path().stem().string());
        }
    }
}

void SaveINI(std::string name) {
    std::string path = cfg_path + "\\" + name + ".ini";
    auto w_b = [&](const char* s, const char* k, bool v) { WritePrivateProfileStringA(s, k, v ? "1" : "0", path.c_str()); };
    auto w_f = [&](const char* s, const char* k, float v) { WritePrivateProfileStringA(s, k, std::to_string(v).c_str(), path.c_str()); };
    auto w_i = [&](const char* s, const char* k, int v) { WritePrivateProfileStringA(s, k, std::to_string(v).c_str(), path.c_str()); };

    w_b("Aim", "Enabled", config::aimbot_enabled);
    w_f("Aim", "FOV", config::aim_fov);
    w_b("Aim", "Walls1", config::walls_stage1);
    w_b("Aim", "Walls2", config::walls_stage2);
    w_b("Aim", "Walls3", config::walls_stage3);
    w_b("Aim", "CamRot", config::cam_rot_spoofing);
    w_b("Aim", "LookPoint", config::lookpoint_spoofing);
    w_b("Aim", "OwnLookY", config::own_look_y_spoofing);
    w_b("Aim", "CustomAtk", config::custom_attack);
    w_b("Aim", "CenterEn", config::center_enemypos);
    w_b("Aim", "ImpMelee", config::imperative_direct_melee);
    w_b("Aim", "RevMelee", config::reversive_direct_melee_check);
    w_b("Aim", "DoubleHit", config::double_secondary_hit);
    w_b("Aim", "ServPos", config::use_server_positions);

    w_f("Melee", "NearbyDist", config::nearby_hitpos_dist);
    w_f("Melee", "S_MaxPad", config::single_max_cam_padding);
    w_f("Melee", "S_Step", config::cam_single_padding_step);
    w_f("Melee", "MaxCamPad", config::max_cam_padding);
    w_f("Melee", "CamStep", config::cam_padding_step);
    w_f("Melee", "MaxHitPad", config::max_hitpos_padding);
    w_f("Melee", "HitStep", config::hitpos_padding_step);

    w_b("ESP", "Enabled", config::esp_enable);
    w_b("ESP", "Targeted", config::show_targeted);
    w_b("ESP", "Friends", config::show_friends);
    w_b("ESP", "Team", config::esp_team_check);
    w_b("ESP", "Box2D", config::esp_box_2d);
    w_b("ESP", "BoxCorn", config::esp_box_corner);
    w_b("ESP", "Box3D", config::esp_box_3d);
    w_b("ESP", "BoxFill", config::esp_box_fill);
    w_b("ESP", "Snap", config::esp_snaplines);
    w_i("ESP", "SnapT", config::esp_snapline_type);
    w_b("ESP", "Health", config::esp_health_bar);
    w_b("ESP", "Skel", config::esp_skeleton);
    w_b("ESP", "Joints", config::esp_skeleton_joints);
    w_b("ESP", "Head", config::esp_head_circle);
    w_b("ESP", "Chams", config::esp_chams);
    w_b("ESP", "ChamsF", config::esp_chams_flat);
    w_b("ESP", "Name", config::esp_name);
    w_b("ESP", "Dist", config::esp_distance);
    w_b("ESP", "Flags", config::esp_flags);
    w_b("ESP", "THUD", config::show_targethud);
    w_f("ESP", "THUD_X", config::targethud_pos_x);
    w_f("ESP", "THUD_Y", config::targethud_pos_y);
    w_b("ESP", "HitNotif", config::show_hitnotify);
    w_b("ESP", "Glow", config::esp_glow);
    w_b("ESP", "Hat", config::esp_china_hat);
    w_b("ESP", "Trails", config::esp_trails);

    w_b("Move", "Spam", config::chat_spam);
    w_b("Move", "NoWepStop", config::noWeaponStopMove);
    w_b("Move", "SpdMod", config::speedModifier);
    w_b("Move", "StopSend", config::stopSendPosition);
    w_b("Move", "AlwaysShf", config::allwaysShift);
    w_b("Move", "FakeBack", config::fakeBackward);
    w_b("Move", "Spin", config::spin);
    w_b("Move", "FakeDuck", config::fakeDuck);
    w_b("Move", "FakeDown", config::fakeDown);
    w_b("Move", "Ghost", config::ghost);
    w_b("Move", "JumpMod", config::jumpModifier);
    w_b("Move", "GravMod", config::gravModifier);
    w_b("Move", "Strafec", config::strafec);
    w_b("Move", "Lag", config::fakeLag);
    w_f("Move", "SpeedM", config::speedm);
    w_f("Move", "JumpM", config::jumpm);
    w_f("Move", "GravM", config::gravm);
    w_f("Move", "SendSpd", config::sendPositionSpeed);
    w_f("Move", "SendPad", config::timeSendPadding);
    w_f("Move", "EulerB", config::EulerBackward);
    w_b("Move", "Magnet", config::magnet_player);
    w_b("Move", "MStrafe", config::melee_strafe);
    w_f("Move", "DStrafe", config::dist_strafe);
    w_f("Move", "SStrafe", config::strafeSpeed);

    w_b("Weapon", "FastRel", config::fast_reload);
    w_b("Weapon", "AutoFast", config::auto_fast_reload);
    w_b("Weapon", "Spinup", config::spinupMinigun);
    w_b("Weapon", "InstChg", config::instantChangeWeapon);

    w_b("FOVC", "Show", config::show_fov_circle);
    w_f("FOVC", "R", config::fov_color[0]);
    w_f("FOVC", "G", config::fov_color[1]);
    w_f("FOVC", "B", config::fov_color[2]);
    w_b("FOVC", "RGB", config::fov_rgb);
    w_b("FOVC", "Specs", config::show_spectators);

    w_b("Misc", "CustFOV", config::custom_fov);
    w_f("Misc", "GameFOV", config::game_fov);
    w_f("Misc", "ZoomFOV", config::zoom_fov);

    RefreshList();
}

void LoadINI(std::string name) {
    std::string path = cfg_path + "\\" + name + ".ini";
    auto r_b = [&](const char* s, const char* k, bool d) -> bool { return GetPrivateProfileIntA(s, k, d ? 1 : 0, path.c_str()) == 1; };
    auto r_f = [&](const char* s, const char* k, float d) -> float {
        char res[32]; GetPrivateProfileStringA(s, k, std::to_string(d).c_str(), res, 32, path.c_str()); return std::stof(res);
        };
    auto r_i = [&](const char* s, const char* k, int d) -> int { return GetPrivateProfileIntA(s, k, d, path.c_str()); };

    config::aimbot_enabled = r_b("Aim", "Enabled", true);
    config::aim_fov = r_f("Aim", "FOV", 500.f);
    config::walls_stage1 = r_b("Aim", "Walls1", false);
    config::walls_stage2 = r_b("Aim", "Walls2", false);
    config::walls_stage3 = r_b("Aim", "Walls3", true);
    config::cam_rot_spoofing = r_b("Aim", "CamRot", true);
    config::lookpoint_spoofing = r_b("Aim", "LookPoint", false);
    config::own_look_y_spoofing = r_b("Aim", "OwnLookY", true);
    config::custom_attack = r_b("Aim", "CustomAtk", true);
    config::center_enemypos = r_b("Aim", "CenterEn", true);
    config::imperative_direct_melee = r_b("Aim", "ImpMelee", false);
    config::reversive_direct_melee_check = r_b("Aim", "RevMelee", false);
    config::double_secondary_hit = r_b("Aim", "DoubleHit", false);
    config::use_server_positions = r_b("Aim", "ServPos", true);

    config::nearby_hitpos_dist = r_f("Melee", "NearbyDist", 2.75f);
    config::single_max_cam_padding = r_f("Melee", "S_MaxPad", 2.8f);
    config::cam_single_padding_step = r_f("Melee", "S_Step", 0.4f);
    config::max_cam_padding = r_f("Melee", "MaxCamPad", 3.7f);
    config::cam_padding_step = r_f("Melee", "CamStep", 0.55f);
    config::max_hitpos_padding = r_f("Melee", "MaxHitPad", 3.7f);
    config::hitpos_padding_step = r_f("Melee", "HitStep", 0.55f);

    config::esp_enable = r_b("ESP", "Enabled", false);
    config::show_targeted = r_b("ESP", "Targeted", false);
    config::show_friends = r_b("ESP", "Friends", false);
    config::esp_team_check = r_b("ESP", "Team", false);
    config::esp_box_2d = r_b("ESP", "Box2D", false);
    config::esp_box_corner = r_b("ESP", "BoxCorn", false);
    config::esp_box_3d = r_b("ESP", "Box3D", false);
    config::esp_box_fill = r_b("ESP", "BoxFill", false);
    config::esp_snaplines = r_b("ESP", "Snap", false);
    config::esp_snapline_type = r_i("ESP", "SnapT", 0);
    config::esp_health_bar = r_b("ESP", "Health", false);
    config::esp_skeleton = r_b("ESP", "Skel", false);
    config::esp_skeleton_joints = r_b("ESP", "Joints", false);
    config::esp_head_circle = r_b("ESP", "Head", false);
    config::esp_chams = r_b("ESP", "Chams", false);
    config::esp_chams_flat = r_b("ESP", "ChamsF", true);
    config::esp_name = r_b("ESP", "Name", false);
    config::esp_distance = r_b("ESP", "Dist", false);
    config::esp_flags = r_b("ESP", "Flags", false);
    config::show_targethud = r_b("ESP", "THUD", true);
    config::targethud_pos_x = r_f("ESP", "THUD_X", -1.0f);
    config::targethud_pos_y = r_f("ESP", "THUD_Y", -1.0f);
    config::show_hitnotify = r_b("ESP", "HitNotif", true);
    config::esp_glow = r_b("ESP", "Glow", false);
    config::esp_china_hat = r_b("ESP", "Hat", false);
    config::esp_trails = r_b("ESP", "Trails", false);

    config::chat_spam = r_b("Move", "Spam", false);
    config::noWeaponStopMove = r_b("Move", "NoWepStop", false);
    config::speedModifier = r_b("Move", "SpdMod", false);
    config::stopSendPosition = r_b("Move", "StopSend", false);
    config::allwaysShift = r_b("Move", "AlwaysShf", false);
    config::fakeBackward = r_b("Move", "FakeBack", false);
    config::spin = r_b("Move", "Spin", false);
    config::fakeDuck = r_b("Move", "FakeDuck", false);
    config::fakeDown = r_b("Move", "FakeDown", false);
    config::ghost = r_b("Move", "Ghost", false);
    config::jumpModifier = r_b("Move", "JumpMod", false);
    config::gravModifier = r_b("Move", "GravMod", false);
    config::strafec = r_b("Move", "Strafec", false);
    config::fakeLag = r_b("Move", "Lag", false);
    config::speedm = r_f("Move", "SpeedM", 0.2475f);
    config::jumpm = r_f("Move", "JumpM", 0.2f);
    config::gravm = r_f("Move", "GravM", 0.2f);
    config::sendPositionSpeed = r_f("Move", "SendSpd", 0.0285f);
    config::timeSendPadding = r_f("Move", "SendPad", 0.0f);
    config::EulerBackward = r_f("Move", "EulerB", 0.f);
    config::magnet_player = r_b("Move", "Magnet", false);
    config::melee_strafe = r_b("Move", "MStrafe", false);
    config::dist_strafe = r_f("Move", "DStrafe", 2.5f);
    config::strafeSpeed = r_f("Move", "SStrafe", 2.5f);

    config::fast_reload = r_b("Weapon", "FastRel", false);
    config::auto_fast_reload = r_b("Weapon", "AutoFast", true);
    config::spinupMinigun = r_b("Weapon", "Spinup", false);
    config::instantChangeWeapon = r_b("Weapon", "InstChg", false);

    config::show_fov_circle = r_b("FOVC", "Show", false);
    config::fov_color[0] = r_f("FOVC", "R", 1.0f);
    config::fov_color[1] = r_f("FOVC", "G", 0.0f);
    config::fov_color[2] = r_f("FOVC", "B", 0.0f);
    config::fov_rgb = r_b("FOVC", "RGB", false);
    config::show_spectators = r_b("FOVC", "Specs", false);

    config::custom_fov = r_b("Misc", "CustFOV", true);
    config::game_fov = r_f("Misc", "GameFOV", 120.0f);
    config::zoom_fov = r_f("Misc", "ZoomFOV", 90.0f);
}
char* uimenu__transform_monostring(monostring* str) {
    WideCharToMultiByte(CP_UTF8, 0, str->wstring, -1, uimenu__monostring_buf, 128, 0, 0);
    return uimenu__monostring_buf;
}

void DrawSlider(const char* label, float* val, float min, float max);
ImU32 GetRainbowColor(float offset = 0.0f) {
    float hue = fmodf(rgb_hue + offset, 1.0f);
    float r, g, b;

    int i = (int)(hue * 6.0f);
    float f = hue * 6.0f - i;
    float q = 1.0f - f;

    switch (i % 6) {
    case 0: r = 1; g = f; b = 0; break;
    case 1: r = q; g = 1; b = 0; break;
    case 2: r = 0; g = 1; b = f; break;
    case 3: r = 0; g = q; b = 1; break;
    case 4: r = f; g = 0; b = 1; break;
    case 5: r = 1; g = 0; b = q; break;
    default: r = 1; g = 0; b = 0; break;
    }

    return IM_COL32((int)(r * 255), (int)(g * 255), (int)(b * 255), 255);
}

void ApplyStyle() {
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.10f, 0.12f, 0.95f);  
    colors[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.08f, 0.10f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.16f, 0.18f, 0.20f, 0.80f);     
    colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.78f, 0.78f, 0.20f); 
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.78f, 0.78f, 0.40f);

    colors[ImGuiCol_Button] = ImVec4(0.12f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.78f, 0.78f, 0.30f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.78f, 0.78f, 0.50f);

    colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.78f, 0.78f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.86f, 0.86f, 1.00f);

    colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.86f, 0.86f, 1.00f);

    colors[ImGuiCol_Header] = ImVec4(0.14f, 0.16f, 0.18f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.78f, 0.78f, 0.25f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.78f, 0.78f, 0.40f);

    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.55f, 1.00f);

    colors[ImGuiCol_Separator] = ImVec4(0.00f, 0.78f, 0.78f, 0.60f);

    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.08f, 0.10f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.32f, 0.34f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.78f, 0.78f, 1.00f);

    style->WindowRounding = 6.0f;
    style->ChildRounding = 4.0f;
    style->FrameRounding = 4.0f;
    style->GrabRounding = 4.0f;
    style->ScrollbarRounding = 4.0f;
    style->TabRounding = 4.0f;
    style->WindowPadding = ImVec2(12, 12);
    style->FramePadding = ImVec2(8, 4);
    style->ItemSpacing = ImVec2(8, 6);
    style->WindowBorderSize = 1.0f;
    style->ChildBorderSize = 1.0f;
    style->ScrollbarSize = 14.0f;
}


void DrawTab(const char* name, int idx) {
    bool selected = (current_tab == idx);
    if (selected) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.00f, 0.78f, 0.78f, 0.40f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.00f, 0.78f, 0.78f, 0.50f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.78f, 0.78f, 0.60f));
    }

    if (ImGui::Button(name, ImVec2(100, 35))) {
        current_tab = idx;
    }

    if (selected) {
        ImGui::PopStyleColor(3);
    }
}

void DrawHeader(const char* text) {
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.00f, 0.86f, 0.86f, 1.0f), text);
    ImGui::Separator();
    ImGui::Spacing();
}

void DrawCheckbox(const char* label, bool* value) {
    ImGui::Checkbox(label, value);
}

void DrawAimTab() {
    DrawHeader("[ AIMBOT ]");

    DrawCheckbox("Enable Aimbot", &config::aimbot_enabled);

    ImGui::Spacing();
    ImGui::Text("FOV Radius: %.0f", config::aim_fov);
    ImGui::SetNextItemWidth(-1);
    ImGui::SliderFloat("##fov", &config::aim_fov, 0.0f, 1000.0f, "");

    ImGui::Spacing();

    DrawCheckbox("Show FOV Circle", &config::show_fov_circle);
    ImGui::SameLine(250);

    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    float box_size = 18.0f;

    ImU32 col;
    if (config::fov_rgb) {
        col = GetRainbowColor(0.0f);
    }
    else {
        col = IM_COL32(
            (int)(config::fov_color[0] * 255),
            (int)(config::fov_color[1] * 255),
            (int)(config::fov_color[2] * 255),
            255
        );
    }

    if (ImGui::InvisibleButton("##colorbox", ImVec2(box_size, box_size))) {
        ImGui::OpenPopup("##fovcolorpicker");
    }

    dl->AddRectFilled(p, ImVec2(p.x + box_size, p.y + box_size), col);
    dl->AddRect(p, ImVec2(p.x + box_size, p.y + box_size), IM_COL32(0, 200, 200, 255), 4.0f, 0, 1.5f);

    if (ImGui::BeginPopup("##fovcolorpicker")) {
        ImGui::SetNextItemWidth(150);
        ImGui::ColorPicker3("##picker", config::fov_color,
            ImGuiColorEditFlags_NoSidePreview |
            ImGuiColorEditFlags_NoInputs |
            ImGuiColorEditFlags_NoAlpha |
            ImGuiColorEditFlags_PickerHueBar);
        ImGui::Separator();
        ImGui::Checkbox("RGB Mode", &config::fov_rgb);
        ImGui::EndPopup();
    }

    ImGui::Spacing();
    DrawHeader("[ PENETRATION ]");

    DrawCheckbox("Single hitpos padding", &config::walls_stage1);
    DrawCheckbox("Single camera padding", &config::walls_stage2);
    DrawCheckbox("Camera and hitpos padding", &config::walls_stage3);
    DrawCheckbox("Camera rotation spoofing", &config::cam_rot_spoofing);
    DrawCheckbox("Look point spoofing", &config::lookpoint_spoofing);
    DrawCheckbox("Own look Y spoofing", &config::own_look_y_spoofing);
    DrawCheckbox("Custom attack", &config::custom_attack);
    DrawCheckbox("Imperative direct melee", &config::imperative_direct_melee); 
    DrawCheckbox("Reversive direct melee check", &config::reversive_direct_melee_check);
    DrawCheckbox("Double secondary hit", &config::double_secondary_hit);
    DrawCheckbox("Use server positions", &config::use_server_positions);
    ImGui::Spacing();
    DrawSlider("Nearby hitpos dist: %.2f", &config::nearby_hitpos_dist, 0.0f, 6.0f);
    ImGui::Spacing();
    DrawSlider("Single max cam padding: %.2f", &config::single_max_cam_padding, 0.0f, 6.0f);
    DrawSlider("Cam single padding step: %.2f", &config::cam_single_padding_step, 0.0f, 6.0f);
    ImGui::Spacing();
    DrawSlider("Max cam padding: %.2f", &config::max_cam_padding, 0.0f, 6.0f);
    DrawSlider("Cam padding step: %.2f", &config::cam_padding_step, 0.0f, 6.0f);
    DrawSlider("Max hitpos padding: %.2f", &config::max_hitpos_padding, 0.0f, 6.0f);
    DrawSlider("Hitpos padding step: %.2f", &config::hitpos_padding_step, 0.0f, 6.0f);
    ImGui::Spacing();
    DrawCheckbox("Center Hitbox", &config::center_enemypos);
}

void DrawSlider(const char* label, float* val, float min, float max) {
    //char buf[128];
    //buf[0] = '#';
    //buf[1] = '#';
    //strcpy(buf + 2, label);
    //
    //ImGui::Text(label, *val);
    //ImGui::SetNextItemWidth(-1);
    //ImGui::SliderFloat(buf, val, min, max, "");
    ImGui::SetNextItemWidth(-1);
    ImGui::SliderFloat(label, val, min, max, "");
}

void DrawVisualsTab() {
    DrawHeader("[ GLOBAL ]");
    DrawCheckbox("Enable ESP", &config::esp_enable);
    DrawCheckbox("Team Check", &config::esp_team_check);
    DrawCheckbox("Show only targeted", &config::show_targeted);
    DrawCheckbox("Show friends", &config::show_friends);

    DrawHeader("[ MODEL & EFFECTS ]");
    DrawCheckbox("Chams Overlay", &config::esp_chams);
    DrawCheckbox("Chams Flat", &config::esp_chams_flat);
    DrawCheckbox("Glow Effect", &config::esp_glow);
    DrawCheckbox("China Hat", &config::esp_china_hat);
    DrawCheckbox("Rainbow Trails", &config::esp_trails);

    DrawHeader("[ BOXES ]");
    DrawCheckbox("2D Box", &config::esp_box_2d);
    DrawCheckbox("Corner Box", &config::esp_box_corner);
    DrawCheckbox("3D Box", &config::esp_box_3d);
    DrawCheckbox("Fill Box", &config::esp_box_fill);

    DrawHeader("[ SKELETON ]");
    DrawCheckbox("Skeleton", &config::esp_skeleton);
    DrawCheckbox("Joints", &config::esp_skeleton_joints);
    DrawCheckbox("Head Circle", &config::esp_head_circle);

    DrawHeader("[ INFO ]");
    DrawCheckbox("Name", &config::esp_name);
    DrawCheckbox("Distance", &config::esp_distance);
    DrawCheckbox("Health Bar", &config::esp_health_bar);
    DrawCheckbox("Show backtrack", &config::backtrack_enable);
    DrawCheckbox("Show protected", &config::esp_flags);

    DrawHeader("[ MISC ]");
    DrawCheckbox("Snaplines", &config::esp_snaplines);
    if (config::esp_snaplines) {
        ImGui::Combo("Origin", &config::esp_snapline_type, config::snapline_types, IM_ARRAYSIZE(config::snapline_types));
    }

    DrawHeader("[ HUD ]");
    DrawCheckbox("Spectator list", &config::show_spectators);
    DrawCheckbox("Target HUD", &config::show_targethud);
    DrawCheckbox("Hit Notifications", &config::show_hitnotify);
}

void DrawMiscTab() {
    DrawHeader("[ MOVEMENT ]");

    DrawCheckbox("Speed Hack", &config::speedModifier);
    if (config::speedModifier) {
        ImGui::Text("Speed: %.4f", config::speedm);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##speed", &config::speedm, 0.18f, 0.40f, "");
    }

    DrawCheckbox("Super Jump", &config::jumpModifier);
    if (config::jumpModifier) {
        ImGui::Text("Force: %.4f", config::jumpm);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##jump", &config::jumpm, 0.20f, 0.60f, "");
    }

    DrawCheckbox("Low Gravity", &config::gravModifier);
    if (config::gravModifier) {
        ImGui::Text("Gravity: %.4f", config::gravm);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##grav", &config::gravm, 0.0f, 0.25f, "");
    }

    DrawCheckbox("Fake lags", &config::fakeLag);
    if (config::fakeLag) {
        ImGui::Text("Send position delay: %.5f", config::sendPositionSpeed);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##sendposdelay", &config::sendPositionSpeed, 0.01f, 1.0f, "");
        ImGui::Text("Time send padding: %.5f", config::timeSendPadding);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##timesendpad", &config::timeSendPadding, -2.0f, 2.0f, "");

        ImGui::Indent();
        ImGui::Text("Legit Modes:");
        bool m3 = (config::fakeLagMode == 3);
        if (ImGui::Checkbox("Sine wave", &m3)) config::fakeLagMode = m3 ? 3 : 0;

        bool m5 = (config::fakeLagMode == 5);
        if (ImGui::Checkbox("Noise", &m5)) config::fakeLagMode = m5 ? 5 : 0;

        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "HvH:");

        bool m6 = (config::fakeLagMode == 6);
        if (ImGui::Checkbox("Binary jitter", &m6)) config::fakeLagMode = m6 ? 6 : 0;

        bool m7 = (config::fakeLagMode == 7);
        if (ImGui::Checkbox("Stutter Step", &m7)) config::fakeLagMode = m7 ? 7 : 0;

        bool m8 = (config::fakeLagMode == 8);
        if (ImGui::Checkbox("Random high choke", &m8)) config::fakeLagMode = m8 ? 8 : 0;

        bool m1 = (config::fakeLagMode == 1);
        if (ImGui::Checkbox("Jitter random", &m1)) config::fakeLagMode = m1 ? 1 : 0;

        bool m2 = (config::fakeLagMode == 2);
        if (ImGui::Checkbox("Switch", &m2)) config::fakeLagMode = m2 ? 2 : 0;

        bool m4 = (config::fakeLagMode == 4);
        if (ImGui::Checkbox("Step factor", &m4)) config::fakeLagMode = m4 ? 4 : 0;

        bool m9 = (config::fakeLagMode == 9);
        if (ImGui::Checkbox("Velocity based", &m9)) config::fakeLagMode = m9 ? 9 : 0;
        if (m9) ImGui::TextDisabled("  (Lags only when moving)");

        bool m10 = (config::fakeLagMode == 10);
        if (ImGui::Checkbox("Sawtooth", &m10)) config::fakeLagMode = m10 ? 10 : 0;

        bool m11 = (config::fakeLagMode == 11);
        if (ImGui::Checkbox("Burst pulse", &m11)) config::fakeLagMode = m11 ? 11 : 0;

        if (config::fakeLagMode == 0) ImGui::TextColored(ImVec4(0, 1, 0, 1), "Active: Default (Static)");

        ImGui::Unindent();
    }
    DrawCheckbox("Strafes", &config::strafec);
    DrawCheckbox("spider", &config::spider);
    DrawCheckbox("silent steps", &config::allwaysShift);
    DrawCheckbox("magnet player", &config::magnet_player);
    DrawCheckbox("melee strafes", &config::melee_strafe); 
    if (config::melee_strafe) {
        ImGui::Text("Distance: %1.f", config::dist_strafe);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##disstrafe", &config::dist_strafe, 0.f, 10.f, "");
        ImGui::Text("speed: %0.2f", config::strafeSpeed);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##speedstrafe", &config::strafeSpeed, 0.f, 3.f, "");
    }
    DrawCheckbox("Fake duck", &config::fakeDuck);
    DrawCheckbox("Fake down", &config::fakeDown);
    DrawCheckbox("Fake backward", &config::fakeBackward);
    if (config::fakeBackward) {
        ImGui::Indent();

        const char* aa_modes[] = {
            "Static Manual",
            "Rage Spin (Fast)",
            "Slow Spin",
            "Jitter (Desync)",
            "3-Way Jitter",
            "Hybrid (Spin+Switch)"
        };
        ImGui::SetNextItemWidth(200);
        ImGui::Combo("Yaw Mode", &config::aa_type, aa_modes, IM_ARRAYSIZE(aa_modes));

        if (config::aa_type == 0) {
            ImGui::Text("Manual Angle: %.0f", config::EulerBackward);
            ImGui::SetNextItemWidth(200);
            ImGui::SliderFloat("##euler", &config::EulerBackward, 0.f, 360.f, "");
        }

        const char* pitch_modes[] = {
            "Off (Legit)",
            "Down (Rage)",
            "Up (Rage)",
            "Zero (Forward)",
            "Jitter (Dance)"
        };
        ImGui::SetNextItemWidth(200);
        ImGui::Combo("Pitch Mode", &config::aa_pitch_type, pitch_modes, IM_ARRAYSIZE(pitch_modes));

        ImGui::Unindent();
    }

    DrawCheckbox("Fake ghost", &config::ghost);
    DrawCheckbox("stop send position", &config::stopSendPosition);
    DrawCheckbox("chat spam", &config::chat_spam);

    ImGui::Checkbox("Auto respawn", &config::auto_respawn);
    ImGui::Checkbox("Fast switch team", &config::auto_team_switch);
    if (config::auto_team_switch) {
        ImGui::Text("Target Team:");

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 1.0f, 1.0f)); 
        if (ImGui::Button("Blue")) config::auto_team_select = 0;
        ImGui::PopStyleColor();

        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.2f, 0.2f, 1.0f)); 
        if (ImGui::Button("Red")) config::auto_team_select = 1;
        ImGui::PopStyleColor();

        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.8f, 0.2f, 1.0f));
        if (ImGui::Button("Green")) config::auto_team_select = 2;
        ImGui::PopStyleColor();

        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.8f, 0.0f, 1.0f));
        if (ImGui::Button("Yellow")) config::auto_team_select = 3;
        ImGui::PopStyleColor();
    }

    ImGui::Spacing();
    DrawHeader("[ WEAPON ]");
    //DrawCheckbox("hide weapon", &config::hideWeapon);
    DrawCheckbox("no weapon stop move", &config::noWeaponStopMove);
    DrawCheckbox("instant change weapon", &config::instantChangeWeapon);
    DrawCheckbox("fast minigun", &config::spinupMinigun);
    DrawCheckbox("Instant reload", &config::fast_reload);
    DrawCheckbox("Auto fast reload", &config::auto_fast_reload);
    DrawCheckbox("Builds mode", &config::destroy_speed);
    if (config::destroy_speed) {
        ImGui::Text("Speed/Delay: %0.3f", config::SpeedBuild);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##speedDB", &config::SpeedBuild, 0.01f, 0.5f, "");

        ImGui::Text("Max Packets: %1.f", config::MaxPackets);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##mpackets", &config::MaxPackets, 1.f, 30.f, "");

        ImGui::Text("Range/Size: %1.f", config::radiusBuild);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##range", &config::radiusBuild, 1.f, 8.f, "");

        ImGui::Separator();
        ImGui::Text("BUILDER MODE (F2)");
        const char* b_items[] = {
            "Floor", "Cube", "Sphere", "Fort", "Cylinder", "Roof",
            "Pyramid", "Spiral", "Pillars", "Cage", "Cross", "Diagonal", "FillSphere",
            "Swastika", "Pillar Stack", "Wall (Front)"
        };
        ImGui::SetNextItemWidth(200);
        ImGui::Combo("##bmode", &config::buildMode, b_items, IM_ARRAYSIZE(b_items));

        ImGui::Separator();
        ImGui::Text("BREAKER MODE (F3)");
        const char* n_items[] = { "Aura (All)", "Flatten (Top)", "Tunnel (Front)" };
        ImGui::SetNextItemWidth(200);
        ImGui::Combo("##nmode", &config::nukerMode, n_items, IM_ARRAYSIZE(n_items));
    }

    ImGui::Spacing();
    DrawHeader("[ VISUALS ]");
    DrawCheckbox("Custom FOV", &config::custom_fov);
    if (config::custom_fov) {
        ImGui::Text("Game FOV: %.0f", config::game_fov);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##gamefov", &config::zoom_fov, 60.0f, 180.0f, "");
        ImGui::Text("Zoom FOV: %.0f", config::game_fov);
        ImGui::SetNextItemWidth(200);
        ImGui::SliderFloat("##zoomfov", &config::zoom_fov, 60.0f, 180.0f, "");
    }
}

void DeleteFriend(monostring* mstr) {
    revfor(i, config::friends.count) {
        if (wcscmp(config::friends[i].nickname_u16, mstr->wstring) == 0) {
            free(config::friends[i].nickname_u8);
            free(config::friends[i].nickname_u16);
            config::friends.delete_at(i);
            return;
        }
    }
}

void DeleteTarget(monostring* mstr) {
    revfor(i, config::targets.count) {
        if (wcscmp(config::targets[i].nickname_u16, mstr->wstring) == 0) {
            free(config::targets[i].nickname_u8);
            free(config::targets[i].nickname_u16);
            config::targets.delete_at(i);
            return;
        }
    }
}

void uimenu::DrawSpectatorList() {
    static std::vector<std::string> spectators;

    if (game::get_gs() == GS_MAINMENU) {
        spectators.clear();
        return;
    }

    if (game::get_gs() == GS_GAME) {
        if (!config::show_spectators) return;

        spectators.clear();
        ServerPlayersController* pcontroller = game::get_pcontroller();
        if (!pcontroller || !pcontroller->RemotePlayersList || !pcontroller->FPController) return;
        tarray* players = pcontroller->RemotePlayersList;
        spectators.reserve(players->max_size);

        std::unordered_set<std::string> used_names;

        deffor(i, players->max_size) {
            ServerBotData* bot = (ServerBotData*)players->element(i);

            if (isptrinvalid((uintptr)bot) || isptrinvalid((uintptr)bot->Name) || isptrinvalid((uintptr)bot->botPoser))
                continue;

            if (bot->Team != 255)
                continue;

            char* raw_nickname = uimenu__transform_monostring(bot->Name);
            if (!raw_nickname) continue;

            std::string nickname(raw_nickname);

            if (used_names.count(nickname))
                continue;

            used_names.insert(nickname);

            char* raw_clan = uimenu__transform_monostring(bot->ClanName);
            std::string display_name;

            if (raw_clan && raw_clan[0] != '\0') {
                display_name = nickname + " [" + std::string(raw_clan) + "]";
            }
            else {
                display_name = nickname;
            }

            spectators.push_back(display_name);
        }

        if (spectators.empty())
            return;

        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_AlwaysAutoResize;

        if (ImGui::Begin("Spectators", nullptr, flags)) {
            for (const auto& name : spectators) {
                ImGui::Text("%s", name.c_str());
            }
        }

        ImGui::End();
    }
}

void DrawPlayerList() {
    DrawHeader("[ PLAYER LIST ]");

    ServerPlayersController* pcontroller = game::get_pcontroller();
    if (!pcontroller || !pcontroller->RemotePlayersList || !pcontroller->FPController) return;

    tarray* players = pcontroller->RemotePlayersList;
    bool has_friends = config::friends.count > 0;

    if (ImGui::Button(has_friends ? "Remove All" : "Add All", ImVec2(-1, 25))) {
        if (has_friends) {
            for (auto& fr : config::friends) {
                if (fr.nickname_u8) free(fr.nickname_u8);
                if (fr.nickname_u16) free(fr.nickname_u16);
            }
            config::friends.count = 0;
        }
        else {
            deffor(i, players->max_size) {
                ServerBotData* bot = (ServerBotData*)players->element(i);
                if (isptrinvalid((uintptr)bot) || isptrinvalid((uintptr)bot->Name)) continue;
                if (!bot->Active) continue;
                if (config::InFriends(bot->Name)) continue;
                if (config::InTargets(bot->Name)) DeleteTarget(bot->Name);

                int str_len = bot->Name->length;
                int byte_size = (str_len * 2) + 2;
                wchar_t* dupped_nick = (wchar_t*)malloc(byte_size);
                char* dupped_u8_nick = (char*)malloc(byte_size);

                if (dupped_nick && dupped_u8_nick) {
                    memset(dupped_nick, 0, byte_size);
                    memset(dupped_u8_nick, 0, byte_size);
                    wcscpy(dupped_nick, bot->Name->wstring);
                    WideCharToMultiByte(CP_UTF8, 0, dupped_nick, -1, dupped_u8_nick, byte_size, 0, 0);
                    cheat_friend fr = { dupped_u8_nick, dupped_nick };
                    config::friends.push(fr);
                }
            }
        }
    }

    ImGui::Separator();

    std::vector<int> target_indices;
    std::vector<int> other_indices;

    deffor(i, players->max_size) {
        ServerBotData* bot = (ServerBotData*)players->element(i);
        if (isptrinvalid((uintptr)bot) || isptrinvalid((uintptr)bot->Name) || isptrinvalid(bot->botPoser)) continue;
        if (!bot->Active) continue;

        if (config::InTargets(bot->Name))
            target_indices.push_back(i);
        else
            other_indices.push_back(i);
    }

    auto DrawPlayerItem = [&](int i) {
        ServerBotData* bot = (ServerBotData*)players->element(i);
        ImGui::PushID(i);

        char* nickname = uimenu__transform_monostring(bot->Name);

        bool in_friends = config::InFriends(bot->Name);
        bool in_targets = config::InTargets(bot->Name);

        ImVec4 team_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        switch (bot->Team) {
        case 0: team_color = ImVec4(0.2f, 0.6f, 1.0f, 1.0f); break;
        case 1: team_color = ImVec4(1.0f, 0.2f, 0.2f, 1.0f); break;
        case 2: team_color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); break;
        case 3: team_color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); break;
        }

        ImGui::PushStyleColor(ImGuiCol_Text, team_color);
        if (ImGui::Button(nickname, ImVec2(160, 35))) {}
        ImGui::PopStyleColor();

        ImGui::SameLine();
        char buf[32];
        snprintf(buf, 32, "%s##fr_btn_%i", in_friends ? "Del FR" : "Add FR", i);
        if (ImGui::Button(buf, ImVec2(55, 25))) {
            if (in_friends) DeleteFriend(bot->Name);
            else {
                if (in_targets) DeleteTarget(bot->Name);
                int str_len = bot->Name->length;
                int byte_size = (str_len * 2) + 2;
                wchar_t* dn = (wchar_t*)malloc(byte_size);
                char* du8 = (char*)malloc(byte_size);
                if (dn && du8) {
                    memset(dn, 0, byte_size);
                    memset(du8, 0, byte_size);
                    wcscpy(dn, bot->Name->wstring);
                    WideCharToMultiByte(CP_UTF8, 0, dn, -1, du8, byte_size, 0, 0);
                    cheat_friend fr = { du8, dn };
                    config::friends.push(fr);
                }
            }
        }

        ImGui::SameLine();
        snprintf(buf, 32, "%s##dl_btn_%i", in_targets ? "Del TG" : "Add TG", i);
        if (ImGui::Button(buf, ImVec2(55, 25))) {
            if (in_targets) DeleteTarget(bot->Name);
            else {
                if (in_friends) DeleteFriend(bot->Name);
                int str_len = bot->Name->length;
                int byte_size = (str_len * 2) + 2;
                wchar_t* dn = (wchar_t*)malloc(byte_size);
                char* du8 = (char*)malloc(byte_size);
                if (dn && du8) {
                    memset(dn, 0, byte_size);
                    memset(du8, 0, byte_size);
                    wcscpy(dn, bot->Name->wstring);
                    WideCharToMultiByte(CP_UTF8, 0, dn, -1, du8, byte_size, 0, 0);
                    cheat_friend fr = { du8, dn };
                    config::targets.push(fr);
                }
            }
        }

        ImGui::PopID();
        };

    for (int idx : target_indices) {
        DrawPlayerItem(idx);
    }

    if (!target_indices.empty() && !other_indices.empty()) {
        ImGui::Separator();
    }

    for (int idx : other_indices) {
        DrawPlayerItem(idx);
    }
}

void DrawCFG() {
    static bool init = false;
    if (!init) { RefreshList(); init = true; }

    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnWidth(0, 220);

    ImGui::Text("Configuration List");
    if (ImGui::BeginListBox("##list", ImVec2(-1, 280))) {
        for (int i = 0; i < cfg_files.size(); i++) {
            if (ImGui::Selectable(cfg_files[i].c_str(), cfg_idx == i)) {
                cfg_idx = i;
                strcpy(cfg_input, cfg_files[i].c_str());
            }
        }
        ImGui::EndListBox();
    }

    if (ImGui::Button("Refresh List", ImVec2(-1, 25))) RefreshList();

    ImGui::NextColumn();

    ImGui::Text("Configuration Name");
    ImGui::PushItemWidth(-1);
    ImGui::InputTextWithHint("##cfg_input", "Enter name...", cfg_input, 64);
    ImGui::PopItemWidth();

    ImGui::Spacing();

    if (ImGui::Button("Create / Save", ImVec2(-1, 30))) {
        if (strlen(cfg_input) > 0) SaveINI(cfg_input);
    }

    if (cfg_idx != -1) {
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("Load Selected", ImVec2(-1, 30))) {
            LoadINI(cfg_files[cfg_idx]);
        }

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.1f, 0.1f, 1.0f));
        if (ImGui::Button("Delete Selected", ImVec2(-1, 30))) {
            std::string p = cfg_path + "\\" + cfg_files[cfg_idx] + ".ini";
            DeleteFileA(p.c_str());
            cfg_idx = -1;
            RefreshList();
        }
        ImGui::PopStyleColor();
    }

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 60);
    if (ImGui::Button("Open Folder", ImVec2(-1, 25))) {
        ShellExecuteA(NULL, "open", cfg_path.c_str(), NULL, NULL, SW_SHOW);
    }

    ImGui::Columns(1);
}

void DrawAUTH() {
    PlayerProfile* profile = (PlayerProfile*)game::get_profile();

    if (!profile) {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "PlayerProfile not found!");
        return;
    }

    ImGui::TextColored(ImVec4(0, 1, 1, 1), "CURRENT PROFILE INFO:");

    if (profile->id) {
        ImGui::Text("ID:");
        ImGui::SameLine();
        ImGui::TextDisabled("%s", to_utf8(profile->id));
    }

    if (profile->authkey) {
        ImGui::Text("AuthKey:");
        ImGui::SameLine();
        ImGui::TextDisabled("%s", to_utf8(profile->authkey));
    }

    if (profile->gameSession) {
        ImGui::Text("Session:");
        ImGui::SameLine();
        ImGui::TextDisabled("%s", to_utf8(profile->gameSession));
    }

    ImGui::Separator();

    static char input_id[128] = "";
    static char input_key[128] = "";
    static char input_gs[128] = "";
    static bool init = false;
    static bool spoofing_active = false;
    static bool data_applied = false; 

    static monostring* spoofed_id_str = nullptr;
    static monostring* spoofed_key_str = nullptr;
    static monostring* spoofed_gs_str = nullptr;

    if (!init && profile->id && profile->authkey) {
        strcpy_s(input_id, to_utf8(profile->id));
        strcpy_s(input_key, to_utf8(profile->authkey));
        if (profile->gameSession) strcpy_s(input_gs, to_utf8(profile->gameSession));
        init = true;
    }

    ImGui::Text("SPOOFING CONTROLS:");
    ImGui::InputText("New ID", input_id, 128);
    ImGui::InputText("New AuthKey", input_key, 128);
    ImGui::InputText("New GameSession", input_gs, 128);

    if (ImGui::Button("LOAD & LOCK DATA", ImVec2(-1, 30))) {
        spoofed_id_str = CreateGameString(input_id);
        spoofed_key_str = CreateGameString(input_key);
        spoofed_gs_str = CreateGameString(input_gs);
        spoofing_active = true;
        data_applied = false; 
    }

    if (spoofing_active) {
        if (game::get_gs() == GS_GAME) {
            if (!data_applied) {
                if (spoofed_id_str) {
                    profile->id = spoofed_id_str;
                    profile->launcherID = spoofed_id_str;
                }
                if (spoofed_key_str) {
                    profile->authkey = spoofed_key_str;
                    profile->launcherAuthkey = spoofed_key_str;
                }
                if (spoofed_gs_str) {
                    profile->gameSession = spoofed_gs_str;
                }

                profile->session = CreateGameString("0");
                profile->network = 2;
                profile->player_need_refresh = true; 
                
                data_applied = true;
            }
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "[ ACTIVE ] Data injected successfully!");
        }
        else {
            if (data_applied) {
                data_applied = false;
            }
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "[ STANDBY ] Waiting for state...");
        }
    }
}

void DrawFOVCircle() {
    if (!config::show_fov_circle || config::aim_fov <= 0) return;

    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    ImVec2 screen_size = ImGui::GetIO().DisplaySize;
    ImVec2 center = ImVec2(screen_size.x / 2.0f, screen_size.y / 2.0f);

    ImU32 color;
    if (config::fov_rgb) {
        color = GetRainbowColor(0.0f);
    }
    else {
        color = IM_COL32(
            (int)(config::fov_color[0] * 255),
            (int)(config::fov_color[1] * 255),
            (int)(config::fov_color[2] * 255),
            255
        );
    }

    draw->AddCircle(center, config::aim_fov, color, 64, 1.5f);
}

void uimenu::draw() {
    ApplyStyle();

    rgb_hue += 0.002f;
    if (rgb_hue > 1.0f) rgb_hue = 0.0f;

    DrawFOVCircle();

    if (GetAsyncKeyState(VK_INSERT) & 1) {
        uimenu_show = !uimenu_show;
    }
    if (!uimenu_show) return;

    ImGui::SetNextWindowSize(ImVec2(675, 450), ImGuiCond_Once);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;

    ImGui::Begin("##MainMenu", nullptr, flags);

    ImDrawList* draw = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetWindowSize();

    draw->AddRectFilledMultiColor(
        pos, ImVec2(pos.x + size.x, pos.y + size.y),
        IM_COL32(20, 25, 30, 220),  
        IM_COL32(25, 30, 35, 220),  
        IM_COL32(25, 30, 35, 220),
        IM_COL32(20, 25, 30, 220)
    );

    draw->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), IM_COL32(40, 45, 50, 255), 6.0f, 0, 1.0f);
    draw->AddRectFilled(
        pos,
        ImVec2(pos.x + 3.0f, pos.y + size.y),
        IM_COL32(0, 200, 200, 255),
        0.0f
    );

    ImGui::SetCursorPos(ImVec2(18, 15));
    ImGui::TextColored(ImVec4(0.00f, 0.86f, 0.86f, 1.0f), "[ANTICHEATER]");

    ImGui::SameLine(size.x - 80);
    ImGui::SetCursorPosY(15);
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "[Insert]");

    ImGui::SetCursorPosY(45);

    ImGui::SetCursorPos(ImVec2(18, 50));
    DrawTab("AIM", 0);
    ImGui::SameLine();
    DrawTab("VISUALS", 1);
    ImGui::SameLine();
    DrawTab("MISC", 2);
    ImGui::SameLine();
    DrawTab("PLAYER LIST", 3);
    ImGui::SameLine();
    DrawTab("CONFIGURATION", 4);
    ImGui::SameLine();
    DrawTab("AUTH", 5);

    ImGui::SetCursorPos(ImVec2(12, 95));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.04f, 0.06f, 0.08f, 0.8f));
    ImGui::BeginChild("##Content", ImVec2(size.x - 24, size.y - 107), true);

    switch (current_tab) {
    case 0: DrawAimTab(); break;
    case 1: DrawVisualsTab(); break;
    case 2: DrawMiscTab(); break;
    case 3: DrawPlayerList(); break;
    case 4: DrawCFG(); break;
    case 5: DrawAUTH(); break;
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::End();
}
