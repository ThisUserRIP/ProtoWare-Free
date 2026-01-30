#include "pch.h"
#include "playeresp.h"
#include "imgui.h"

#include "game.h"
#include "config.h"
#include "target_system.h"
#include "component.h"
#include "internal_component.h"
#include "internal_camera.h"
#include "internal_transform.h"
#include "internal_gameobject.h"

#include "stServerPlayersController.hpp"
#include "stServerBotData.hpp"
#include "stClient.hpp"
#include "mdClient.hpp"
#include "stVP_FPController.hpp"
#include "stVP_FPCamera.hpp"
#include "stBotPoseController.hpp"
#include <playerhealth.h>
#include <algorithm>
#include <vector>

char playeresp__monostring_buf[128];

char* playeresp__transform_monostring( monostring* str ) {
	WideCharToMultiByte(CP_UTF8, 0, str->wstring, -1, playeresp__monostring_buf, 128, 0, 0);
	return playeresp__monostring_buf;
}

struct TrailPoint {
    vec3 pos;
    float time;
};

struct BacktrackRecord {
    int tick;
    float time;
    vec3 head_pos;
    std::vector<vec3> joints;

    bool IsValid(int currentClientTick) const {
        int delta = currentClientTick - tick;
        return delta > 0 && delta < 25;
    }
};

inline std::map<int, std::deque<TrailPoint>> player_trails;
std::map<int, std::deque<BacktrackRecord>> backtrack_records;

void playeresp::draw() {
    if (!config::esp_enable) return;

#define TOIMV(a) ImVec2(a.x, a.y)

    ServerPlayersController* pcontroller = game::get_pcontroller();
    Client* client = game::get_client();
    if (!client || !pcontroller || !pcontroller->RemotePlayersList || !pcontroller->FPController) return;

    vp_FPController* fpcontroller = (vp_FPController*)pcontroller->FPController;
    if (!fpcontroller->m_FPSCamera) return;
    vp_FPCamera* fpcamera = (vp_FPCamera*)fpcontroller->m_FPSCamera;
    if (!fpcamera->MyCamera) return;
    component* camera = (component*)fpcamera->MyCamera;
    internal_camera* internalcam = (internal_camera*)camera->internal_component;
    if (isptrinvalid((uintptr)internalcam)) return;

    vec3 ownpos = internalcam->go->get_transform()->get_kernel_pos();
    matrix4x4 vpmatrix = internalcam->projmatrix * internalcam->viewmatrix;
    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

    ImVec2 screenSize = ImGui::GetIO().DisplaySize;
    float time = ImGui::GetTime();

    tarray* players = pcontroller->RemotePlayersList;
    ServerBotData* ownbot = (ServerBotData*)players->element(client->myindex);

    deffor(i, players->max_size) {
        if (i == client->myindex) continue;

        ServerBotData* bot = (ServerBotData*)players->element(i);

        if (isptrinvalid((uintptr)bot) || isptrinvalid((uintptr)bot->Name) || isptrinvalid(bot->botPoser)) {
            player_trails[i].clear();
            continue;
        }

        if (config::show_targeted || config::show_friends) {
            bool found = false;
            char* current_name = playeresp__transform_monostring(bot->Name);

            if (config::show_targeted) {
                for (int t = 0; t < config::targets.count; t++) {
                    if (strcmp(current_name, config::targets[t].nickname_u8) == 0) {
                        found = true;
                        break;
                    }
                }
            }

            if (!found && config::show_friends) {
                for (int f = 0; f < config::friends.count; f++) {
                    if (strcmp(current_name, config::friends[f].nickname_u8) == 0) {
                        found = true;
                        break;
                    }
                }
            }

            if (!found) {
                player_trails[i].clear();
                continue;
            }
        }

        if (!bot->Active || bot->Dead) {
            player_trails[i].clear();
            continue;
        }

        if (config::esp_team_check && ownbot && bot->Team == ownbot->Team) {
            player_trails[i].clear();
            continue;
        }

        component* botposer = (component*)bot->botPoser;
        if (!botposer->internal_component) continue;
        internal_transform* transform = botposer->internal_component->gameobject->get_transform();
        BotPoseController* poseController = (BotPoseController*)botposer;

        vec3 root_pos = transform->get_kernel_pos();
        if (root_pos.x == 0.f && root_pos.y == 0.f && root_pos.z == 0.f) continue;
        if (root_pos.y < -500.f) continue;

        vec3 head_pos_3d = transform->get_pos(16) + vec3(0.0f, 0.2f, 0.0f);

        ImVec2 root_scr = TOIMV(vpmatrix.worldtoscreen(root_pos));
        ImVec2 head_scr = TOIMV(vpmatrix.worldtoscreen(head_pos_3d));

        if (root_scr.x == 0 && root_scr.y == 0) continue;
        if (head_scr.x == 0 && head_scr.y == 0) continue;

        float dist = ownpos.get_distance(root_pos);
        if (dist < 1.0f) dist = 1.0f;

        bool isFriend = config::InFriends(bot->Name);
        bool isTarget = (config::aimbot_enabled && target_system::current_target_index == i);
        bool isProtected = poseController->isProtected;

        ImColor mainColor = IM_COL32(255, 0, 0, 255);
        if (isProtected) mainColor = IM_COL32(255, 215, 0, 255);
        else if (isTarget) mainColor = IM_COL32(0, 255, 0, 255);
        else if (isFriend) mainColor = IM_COL32(0, 200, 255, 255);


        auto& records = backtrack_records[i];
        int currentTick = client->clientTik;

        if (records.empty() || currentTick > records.front().tick) {
            BacktrackRecord new_record;
            new_record.tick = currentTick;
            new_record.time = time;
            new_record.head_pos = head_pos_3d;
            new_record.joints.reserve(17);

            int joint_indices[] = { 4, 5, 6, 9, 10, 11, 14, 15, 0xDA, 0xDB, 0xDC, 0xDD, 0xE6, 0xE7, 0xE8, 0xE9, 16 };
            for (int idx : joint_indices) {
                new_record.joints.push_back(transform->get_pos(idx));
            }

            records.push_front(new_record);
        }

        while (!records.empty()) {
            if ((currentTick - records.back().tick > 26) || (time - records.back().time > 0.5f)) {
                records.pop_back();
            }
            else {
                break;
            }
        }

        if (!records.empty() && config::backtrack_enable) {
            for (const auto& rec : records) {
                if (!rec.IsValid(currentTick)) continue;

                if (rec.joints.size() < 17) continue;

                std::vector<ImVec2> s(17);
                bool all_points_valid = true;

                for (int k = 0; k < 17; k++) {
                    s[k] = TOIMV(vpmatrix.worldtoscreen(rec.joints[k]));
                    if (s[k].x == 0 && s[k].y == 0) {
                        all_points_valid = false;
                        break;
                    }
                }
                if (!all_points_valid) continue;


                float deltaTick = (float)(currentTick - rec.tick);
                float alpha = 1.0f - (deltaTick / 25.0f);
                if (alpha < 0.1f) alpha = 0.1f;

                ImColor btCol = IM_COL32(0, 255, 255, (int)(150 * alpha)); 

                auto l = [&](int a, int b) {
                    draw_list->AddLine(s[a], s[b], btCol, 1.0f);
                    };

                l(0, 1); l(1, 2); // Руки L
                l(3, 4); l(4, 5); // Руки R
                l(6, 7); l(7, 16); // Спина-Голова
                l(0, 6); l(3, 6); // Плечи
                l(7, 8); l(8, 9); l(9, 10); l(10, 11); // Нога L
                l(7, 12); l(12, 13); l(13, 14); l(14, 15); // Нога R

                draw_list->AddCircleFilled(s[16], 2.0f, IM_COL32(255, 255, 0, (int)(200 * alpha)));
            }
        }

        float boxWidth = 0.45f;
        float boxHeight = 1.8f;

        vec3 points[8] = {
            root_pos + vec3(boxWidth, 0, boxWidth), root_pos + vec3(boxWidth, 0, -boxWidth),
            root_pos + vec3(-boxWidth, 0, boxWidth), root_pos + vec3(-boxWidth, 0, -boxWidth),
            root_pos + vec3(boxWidth, boxHeight, boxWidth), root_pos + vec3(boxWidth, boxHeight, -boxWidth),
            root_pos + vec3(-boxWidth, boxHeight, boxWidth), root_pos + vec3(-boxWidth, boxHeight, -boxWidth)
        };

        float minX = screenSize.x, minY = screenSize.y, maxX = 0, maxY = 0;
        ImVec2 scr_points[8];

        for (int j = 0; j < 8; j++) {
            scr_points[j] = TOIMV(vpmatrix.worldtoscreen(points[j]));
            if (scr_points[j].x < minX) minX = scr_points[j].x;
            if (scr_points[j].y < minY) minY = scr_points[j].y;
            if (scr_points[j].x > maxX) maxX = scr_points[j].x;
            if (scr_points[j].y > maxY) maxY = scr_points[j].y;
        }
        if (head_scr.y < minY) minY = head_scr.y - 5.0f;
        float h = maxY - minY;
        float w = maxX - minX;

        if (config::esp_trails) {
            auto& trail = player_trails[i];
            vec3 footPos = transform->get_pos(0) + vec3(0, 0.1f, 0);

            if (trail.empty() || ownpos.get_distance(footPos) < 150.0f) {
                trail.push_front({ footPos, time });
            }
            if (trail.size() > 40) trail.pop_back();

            for (size_t k = 0; k < trail.size() - 1; k++) {
                ImVec2 p1 = TOIMV(vpmatrix.worldtoscreen(trail[k].pos));
                ImVec2 p2 = TOIMV(vpmatrix.worldtoscreen(trail[k + 1].pos));

                if (p1.x != 0 && p2.x != 0) {
                    float hue = fmodf(time * 0.5f + (k * 0.05f), 1.0f);
                    ImColor rainbow;
                    ImGui::ColorConvertHSVtoRGB(hue, 1.0f, 1.0f, rainbow.Value.x, rainbow.Value.y, rainbow.Value.z);
                    rainbow.Value.w = 1.0f - ((float)k / trail.size());
                    draw_list->AddLine(p1, p2, rainbow, 2.0f);
                }
            }
        }

        if (config::esp_chams || config::esp_skeleton || config::esp_glow) {
            vec3 joints[] = {
                transform->get_pos(4), transform->get_pos(5), transform->get_pos(6),
                transform->get_pos(9), transform->get_pos(10), transform->get_pos(11),
                transform->get_pos(14), transform->get_pos(15), head_pos_3d,
                transform->get_pos(0xDA), transform->get_pos(0xDB), transform->get_pos(0xDC), transform->get_pos(0xDD),
                transform->get_pos(0xE6), transform->get_pos(0xE7), transform->get_pos(0xE8), transform->get_pos(0xE9)
            };
            ImVec2 s[17];
            for (int k = 0; k < 17; k++) s[k] = TOIMV(vpmatrix.worldtoscreen(joints[k]));

            int pairs[][2] = {
                {0,1}, {1,2}, {3,4}, {4,5}, {0,6}, {3,6}, {6,7}, {7,8},
                {7,9}, {9,10}, {10,11}, {11,12}, {7,13}, {13,14}, {14,15}, {15,16}
            };

            if (config::esp_glow) {
                float baseThick = (150.0f / dist);
                if (baseThick > 8.0f) baseThick = 8.0f;
                ImColor glowCol = mainColor;
                for (int pass = 0; pass < 3; pass++) {
                    glowCol.Value.w = 0.15f + (pass * 0.1f);
                    float th = baseThick + ((2 - pass) * 3.0f);
                    for (auto& p : pairs) draw_list->AddLine(s[p[0]], s[p[1]], glowCol, th);
                }
            }

            if (config::esp_chams || config::esp_skeleton) {
                float thickness = config::esp_chams ? (200.0f / dist) : 1.0f;
                if (config::esp_chams) {
                    if (thickness < 2.0f) thickness = 2.0f;
                    if (thickness > 12.0f) thickness = 12.0f;
                }

                ImColor col = mainColor;
                if (config::esp_chams && config::esp_chams_flat) col.Value.w = 0.7f;

                for (auto& p : pairs) draw_list->AddLine(s[p[0]], s[p[1]], col, thickness);

                if (config::esp_chams) {
                    ImVec2 neck = s[7];
                    if (neck.x != 0) draw_list->AddCircleFilled(neck, thickness * 1.3f, col);
                }
            }

            if (config::esp_skeleton_joints) {
                for (int k = 0; k < 17; k++) draw_list->AddCircleFilled(s[k], 2.5f, IM_COL32(255, 255, 255, 255));
            }
        }

        if (config::esp_china_hat) {
            vec3 hatTop = head_pos_3d + vec3(0, 0.3f, 0);
            ImVec2 topScr = TOIMV(vpmatrix.worldtoscreen(hatTop));
            ImVec2 baseScr = TOIMV(vpmatrix.worldtoscreen(head_pos_3d));

            if (topScr.x != 0 && baseScr.x != 0) {
                float radius = 0.35f;
                ImVec2 prevP;
                bool first = true;
                ImColor hatCol = mainColor;
                hatCol.Value.w = 0.6f;

                for (int a = 0; a <= 12; a++) {
                    float ang = (float)a * (6.283f / 12.0f);
                    vec3 p = head_pos_3d + vec3(cosf(ang) * radius, 0, sinf(ang) * radius);
                    ImVec2 pScr = TOIMV(vpmatrix.worldtoscreen(p));

                    if (pScr.x != 0) {
                        if (!first) {
                            draw_list->AddTriangleFilled(topScr, prevP, pScr, hatCol);
                            draw_list->AddLine(prevP, pScr, IM_COL32(0, 0, 0, 255), 1.0f);
                        }
                        prevP = pScr;
                        first = false;
                    }
                }
            }
        }

        if (config::esp_box_fill)
            draw_list->AddRectFilled(ImVec2(minX, minY), ImVec2(maxX, maxY), ImColor(0, 0, 0, 70));

        if (config::esp_box_2d) {
            draw_list->AddRect(ImVec2(minX, minY), ImVec2(maxX, maxY), mainColor, 0.0f, 0, 1.0f);
            draw_list->AddRect(ImVec2(minX - 1, minY - 1), ImVec2(maxX + 1, maxY + 1), IM_COL32(0, 0, 0, 255));
            draw_list->AddRect(ImVec2(minX + 1, minY + 1), ImVec2(maxX - 1, maxY - 1), IM_COL32(0, 0, 0, 255));
        }

        if (config::esp_box_corner) {
            float lineW = w / 4, lineH = h / 4;
            auto line = [&](float x1, float y1, float x2, float y2) {
                draw_list->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), mainColor, 1.5f);
                };
            line(minX, minY, minX + lineW, minY); line(minX, minY, minX, minY + lineH);
            line(maxX, minY, maxX - lineW, minY); line(maxX, minY, maxX, minY + lineH);
            line(minX, maxY, minX + lineW, maxY); line(minX, maxY, minX, maxY - lineH);
            line(maxX, maxY, maxX - lineW, maxY); line(maxX, maxY, maxX, maxY - lineH);
        }

        if (config::esp_box_3d) {
            auto l = [&](int i1, int i2) { draw_list->AddLine(scr_points[i1], scr_points[i2], mainColor); };
            l(0, 1); l(0, 2); l(3, 1); l(3, 2); l(4, 5); l(4, 6); l(7, 5); l(7, 6);
            l(0, 4); l(1, 5); l(2, 6); l(3, 7);
        }

        if (config::esp_snaplines) {
            ImVec2 from;
            if (config::esp_snapline_type == 0) from = ImVec2(screenSize.x / 2, screenSize.y);
            else if (config::esp_snapline_type == 1) from = ImVec2(screenSize.x / 2, screenSize.y / 2);
            else from = ImVec2(screenSize.x / 2, 0);
            draw_list->AddLine(from, ImVec2(minX + w / 2, maxY), mainColor);
        }

        if (config::esp_head_circle) {
            draw_list->AddCircle(head_scr, (maxY - minY) / 12.0f, IM_COL32(255, 255, 255, 255));
        }

        if (config::esp_health_bar) {
            int plrhealth = playerhealth::get_player_health(i);
            float hp = (plrhealth == -1) ? 100.0f : (float)plrhealth;
            float max_hp = 100.0f;
            float hp_percent = std::clamp(hp / max_hp, 0.0f, 1.0f);

            float barWidth = 4.0f;
            float offset = 5.0f;
            ImVec2 tl = ImVec2(minX - offset - barWidth, minY);
            ImVec2 br = ImVec2(minX - offset, maxY);
            float bh = (maxY - minY) * hp_percent;

            draw_list->AddRectFilled(tl, br, IM_COL32(0, 0, 0, 220));
            ImColor hpCol = IM_COL32((int)(255 * (1 - hp_percent) * 2), (int)(255 * hp_percent), 0, 255);
            draw_list->AddRectFilled(ImVec2(tl.x + 1, maxY - bh + 1), ImVec2(br.x - 1, maxY - 1), hpCol);
            draw_list->AddRect(tl, br, IM_COL32(0, 0, 0, 255));

            if (hp < max_hp) {
                char hpBuf[8]; snprintf(hpBuf, 8, "%d", (int)hp);
                ImVec2 tsz = ImGui::CalcTextSize(hpBuf);
                ImVec2 tpos = ImVec2(tl.x - tsz.x - 2, maxY - bh - (tsz.y / 2));
                if (tpos.y < minY) tpos.y = minY;
                draw_list->AddText(ImVec2(tpos.x + 1, tpos.y + 1), IM_COL32(0, 0, 0, 255), hpBuf);
                draw_list->AddText(tpos, IM_COL32(255, 255, 255, 255), hpBuf);
            }
        }

        float textY = minY - 5.0f;
        if (config::esp_name) {
            char* nick = playeresp__transform_monostring(bot->Name);
            ImVec2 sz = ImGui::CalcTextSize(nick);
            textY -= sz.y;
            draw_list->AddText(ImVec2(minX + (w / 2) - (sz.x / 2) + 1, textY + 1), IM_COL32(0, 0, 0, 255), nick);
            draw_list->AddText(ImVec2(minX + (w / 2) - (sz.x / 2), textY), IM_COL32(255, 255, 255, 255), nick);
        }

        float botY = maxY + 2.0f;
        if (config::esp_distance) {
            char db[32]; snprintf(db, 32, "[%.0f m]", dist);
            ImVec2 sz = ImGui::CalcTextSize(db);
            draw_list->AddText(ImVec2(minX + (w / 2) - (sz.x / 2) + 1, botY + 1), IM_COL32(0, 0, 0, 255), db);
            draw_list->AddText(ImVec2(minX + (w / 2) - (sz.x / 2), botY), IM_COL32(200, 200, 200, 255), db);
        }

        if (config::esp_flags && isProtected) {
            const char* txt = "PROTECTED";
            ImVec2 sz = ImGui::CalcTextSize(txt);
            ImVec2 cpos = ImVec2(minX + (w / 2) - (sz.x / 2), minY + (h / 3));
            draw_list->AddText(ImVec2(cpos.x + 1, cpos.y + 1), IM_COL32(0, 0, 0, 255), txt);
            draw_list->AddText(cpos, IM_COL32(255, 215, 0, 255), txt);
        }
    }
}