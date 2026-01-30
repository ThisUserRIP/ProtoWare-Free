#include "pch.h"
#include "targethud.h"
#include "imgui.h"
#include "config.h"
#include "target_system.h"
#include "globals.h"
#include "playerhealth.h"

#include "game.h"
#include "component.h"
#include "internal_component.h"

#include "stServerPlayersController.hpp"
#include "stServerBotData.hpp"
#include "stClient.hpp"
#include "stBotPoseController.hpp"

static char targethud_name_buf[64] = "Unknown";

// Animation state
static bool positionInitialized = false;
static bool wasTargeting = false;
static float animationScale = 0.0f;
static float animationTime = 0.0f;
static const float ANIMATION_DURATION = 0.25f; // 250ms

static char* convert_monostring(monostring* str) {
    if (!str || isptrinvalid((uintptr)str)) {
        strcpy_s(targethud_name_buf, "Unknown");
        return targethud_name_buf;
    }
    WideCharToMultiByte(CP_UTF8, 0, str->wstring, -1, targethud_name_buf, 64, 0, 0);
    return targethud_name_buf;
}

void targethud::draw() {
    if (!config::show_targethud || !config::aimbot_enabled) return;
    
    // Получаем текущую цель
    auto target = target_system::get_cached_target();
    bool hasTarget = (target.bot_data != nullptr);
    
    // Анимация появления/исчезновения
    float deltaTime = ImGui::GetIO().DeltaTime;
    
    if (hasTarget && !wasTargeting) {
        // Начинаем анимацию появления
        animationTime = 0.0f;
        wasTargeting = true;
    } else if (!hasTarget && wasTargeting) {
        // Начинаем анимацию исчезновения
        animationTime = ANIMATION_DURATION;
        wasTargeting = false;
    }
    
    // Обновляем анимацию
    if (wasTargeting && animationTime < ANIMATION_DURATION) {
        animationTime += deltaTime;
        if (animationTime > ANIMATION_DURATION) animationTime = ANIMATION_DURATION;
    } else if (!wasTargeting && animationTime > 0.0f) {
        animationTime -= deltaTime;
        if (animationTime < 0.0f) animationTime = 0.0f;
    }
    
    // Вычисляем масштаб (easing out cubic)
    float t = animationTime / ANIMATION_DURATION;
    t = 1.0f - (1.0f - t) * (1.0f - t) * (1.0f - t); // cubic ease out
    animationScale = t;
    
    // Если анимация закончилась и цели нет - не рисуем
    if (animationScale <= 0.01f) return;
    
    if (!hasTarget) return; // Нет цели для отображения
    
    ServerBotData* bot = target.bot_data;
    if (isptrinvalid((uintptr)bot) || isptrinvalid((uintptr)bot->Name)) return;
    
    // Получаем HP из BotPoseController
    float maxHealth = 100.0f;
    float currentHealth = 100.0f;
    
    //if (bot->botPoser && isptrvalid(bot->botPoser)) {
        //BotPoseController* poseController = (BotPoseController*)bot->botPoser;
        //if (poseController->_maxHealth > 0) {
        //    maxHealth = poseController->_maxHealth;
        //    currentHealth = maxHealth; // В PG3D текущее HP не хранится локально
        //}
        int plrhealth = playerhealth::get_player_health(target.bot_index);
        currentHealth = (plrhealth == -1) ? 100 : plrhealth;
        if (game::get_mode() == E_MODE_ZOMBIE && bot->Team == 1) {
            maxHealth = 3000.0f;
        }
        
    //}
    
    char* nickname = convert_monostring(bot->Name);
    char nameplate[80];
    snprintf(nameplate, 80, "%s%s", nickname, playerhealth::get_player_tykva(target.bot_index) ? " [TY]" : "");

    float healthPercent = std::min(currentHealth / maxHealth, 1.0f);
    
    // Размеры HUD
    float baseWidth = 180.0f;
    float baseHeight = 55.0f;
    float hudWidth = baseWidth * animationScale;
    float hudHeight = baseHeight * animationScale;
    float padding = 8.0f * animationScale;
    float barHeight = 8.0f * animationScale;
    
    ImVec2 screenSize = ImGui::GetIO().DisplaySize;
    
    // Инициализация позиции по центру при первом запуске
    if (!positionInitialized || config::targethud_pos_x < 0) {
        config::targethud_pos_x = (screenSize.x - baseWidth) / 2.0f;
        config::targethud_pos_y = screenSize.y * 0.35f;
        positionInitialized = true;
    }
    
    // Центрируем анимацию относительно базовой позиции
    float offsetX = (baseWidth - hudWidth) / 2.0f;
    float offsetY = (baseHeight - hudHeight) / 2.0f;
    ImVec2 hudPos = ImVec2(config::targethud_pos_x + offsetX, config::targethud_pos_y + offsetY);
    
    // Создаём невидимое окно для перетаскивания (только если полностью видимо)
    if (animationScale > 0.95f) {
        ImGui::SetNextWindowPos(ImVec2(config::targethud_pos_x, config::targethud_pos_y), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(baseWidth, baseHeight), ImGuiCond_Always);
        
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
                                ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground |
                                ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
                                ImGuiWindowFlags_NoBringToFrontOnFocus;
        
        ImGui::Begin("##TargetHUD", nullptr, flags);
        
        // Обновляем позицию если окно перетащили
        ImVec2 windowPos = ImGui::GetWindowPos();
        config::targethud_pos_x = windowPos.x;
        config::targethud_pos_y = windowPos.y;
        
        // Пересчитываем позицию с учётом перетаскивания
        offsetX = (baseWidth - hudWidth) / 2.0f;
        offsetY = (baseHeight - hudHeight) / 2.0f;
        hudPos = ImVec2(config::targethud_pos_x + offsetX, config::targethud_pos_y + offsetY);
    }
    
    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    
    // Альфа для анимации
    int alpha = (int)(255 * animationScale);
    
    // Современный градиентный фон как в HitNotify
    ImVec2 bgMin = hudPos;
    ImVec2 bgMax = ImVec2(hudPos.x + hudWidth, hudPos.y + hudHeight);
    
    draw->AddRectFilledMultiColor(
        bgMin, bgMax,
        IM_COL32(20, 25, 30, (int)(220 * animationScale)),  // Темнее слева
        IM_COL32(25, 30, 35, (int)(220 * animationScale)),  // Светлее справа
        IM_COL32(25, 30, 35, (int)(220 * animationScale)),
        IM_COL32(20, 25, 30, (int)(220 * animationScale))
    );
    
    // Тонкая рамка
    draw->AddRect(bgMin, bgMax, IM_COL32(40, 45, 50, alpha), 6.0f * animationScale, 0, 1.0f);
    
    // Цветная полоска слева (cyan акцент)
    draw->AddRectFilled(
        ImVec2(hudPos.x, hudPos.y),
        ImVec2(hudPos.x + 3.0f * animationScale, hudPos.y + hudHeight),
        IM_COL32(0, 200, 200, alpha),
        0.0f
    );
    
    // Рисуем текст только если достаточно большой
    if (animationScale > 0.2f) {
        float textPadding = padding + 3.0f * animationScale; // Отступ от cyan полоски
        
        // [ProtoWare] в cyan цвете как в HitNotify
        ImVec2 brandPos = ImVec2(hudPos.x + textPadding, hudPos.y + padding);
        draw->AddText(brandPos, IM_COL32(0, 200, 200, alpha), "[ProtoWare]");
        
        // Ник игрока
        ImVec2 namePos = ImVec2(hudPos.x + textPadding, hudPos.y + padding + 16.0f * animationScale);
        draw->AddText(namePos, IM_COL32(255, 255, 255, alpha), nameplate);
        
        // HP бар фон (более современный)
        float barY = hudPos.y + hudHeight - padding - barHeight - 2.0f * animationScale;
        ImVec2 barBgMin = ImVec2(hudPos.x + textPadding, barY);
        ImVec2 barBgMax = ImVec2(hudPos.x + hudWidth - padding, barY + barHeight);
        
        draw->AddRectFilled(barBgMin, barBgMax, IM_COL32(15, 20, 25, alpha), 4.0f * animationScale);
        
        // HP бар с градиентом
        ImU32 barColor1, barColor2;
        if (healthPercent > 0.6f) {
            barColor1 = IM_COL32(60, 180, 100, alpha);  // Зелёный градиент
            barColor2 = IM_COL32(80, 220, 120, alpha);
        } else if (healthPercent > 0.3f) {
            barColor1 = IM_COL32(200, 160, 40, alpha);  // Жёлтый градиент
            barColor2 = IM_COL32(240, 200, 60, alpha);
        } else {
            barColor1 = IM_COL32(180, 50, 50, alpha);   // Красный градиент
            barColor2 = IM_COL32(220, 70, 70, alpha);
        }
        
        float barWidth = (hudWidth - textPadding - padding) * healthPercent;
        if (barWidth > 2.0f) {
            ImVec2 barMin = ImVec2(hudPos.x + textPadding, barY);
            ImVec2 barMax = ImVec2(hudPos.x + textPadding + barWidth, barY + barHeight);
            
            draw->AddRectFilledMultiColor(barMin, barMax, barColor1, barColor2, barColor2, barColor1);
        }
        
        // HP текст справа от бара
        char hpText[32];
        snprintf(hpText, sizeof(hpText), "%.0f HP", currentHealth);
        ImVec2 hpTextPos = ImVec2(hudPos.x + hudWidth - padding - 50.0f * animationScale, barY - 22.0f - 2.0f * animationScale);
        draw->AddText(hpTextPos, IM_COL32(180, 180, 180, alpha), hpText);
    }
    
    // Закрываем окно только если оно было открыто
    if (animationScale > 0.95f) {
        ImGui::End();
    }
}
