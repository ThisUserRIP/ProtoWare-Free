#include "pch.h"
#include "hitnotify.h"
#include "imgui.h"
#include "config.h"
#include "globals.h"
#include <cmath>
#include <map>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef IM_PI
#define IM_PI 3.14159265358979323846f
#endif

struct HitNotification {
    char playerName[32];
    char hitzone[16];
    float damage;
    float distance;
    float timeLeft;
    float totalTime;
    float animScale;
    bool isAnimatingIn;
    bool isDeath; // Новое поле для death уведомлений
    
    HitNotification() {
        playerName[0] = '\0';
        hitzone[0] = '\0';
        damage = 0.0f;
        distance = 0.0f;
        timeLeft = 0.0f;
        totalTime = 0.0f;
        animScale = 0.0f;
        isAnimatingIn = true;
        isDeath = false;
    }
};

// Структура для отслеживания урона по игрокам
struct PlayerDamage {
    float totalDamage;
    float lastHitTime;
    
    PlayerDamage() : totalDamage(0.0f), lastHitTime(0.0f) {}
};

// Карта для отслеживания урона по игрокам
static std::map<std::string, PlayerDamage> playerDamageMap;

static HitNotification notifications[5]; // Максимум 5 уведомлений
static int notificationCount = 0;
static const float NOTIFICATION_DURATION = 5.0f; // 5 секунд
static const float ANIMATION_DURATION = 0.4f; // 400ms анимация

void hitnotify::initialize() {
    notificationCount = 0;
    for (int i = 0; i < 5; i++) {
        notifications[i] = HitNotification();
    }
}

void hitnotify::add_hit(const char* player_name, const char* hitzone, float damage, float distance) {
    if (!config::show_hitnotify) return;
    
    std::string playerKey(player_name);
    float currentTime = ImGui::GetTime();
    
    // Обновляем урон для игрока
    PlayerDamage& playerDmg = playerDamageMap[playerKey];
    
    // Если прошло больше 10 секунд с последнего хита - сбрасываем урон
    if (currentTime - playerDmg.lastHitTime > 10.0f) {
        playerDmg.totalDamage = 0.0f;
    }
    
    playerDmg.totalDamage += damage;
    playerDmg.lastHitTime = currentTime;
    
    // Сдвигаем существующие уведомления вниз
    for (int i = 4; i > 0; i--) {
        notifications[i] = notifications[i - 1];
    }
    
    // Добавляем новое уведомление в начало
    HitNotification& newHit = notifications[0];
    strncpy_s(newHit.playerName, player_name, 31);
    strncpy_s(newHit.hitzone, hitzone, 15);
    newHit.damage = damage;
    newHit.distance = distance;
    newHit.timeLeft = NOTIFICATION_DURATION;
    newHit.totalTime = NOTIFICATION_DURATION;
    newHit.animScale = 0.0f;
    newHit.isAnimatingIn = true;
    newHit.isDeath = false;
    
    if (notificationCount < 5) notificationCount++;
    
    // Проверяем на смерть (обычно 100+ урона означает смерть)
    if (playerDmg.totalDamage >= 100.0f) {
        add_death(player_name, 0);
        playerDmg.totalDamage = 0.0f; // Сбрасываем после смерти
    }
}

void hitnotify::add_death(const char* player_name, float distance) {
    if (!config::show_hitnotify) return;
    
    // Сдвигаем существующие уведомления вниз
    for (int i = 4; i > 0; i--) {
        notifications[i] = notifications[i - 1];
    }
    
    // Добавляем death уведомление
    HitNotification& deathHit = notifications[0];
    strncpy_s(deathHit.playerName, player_name, 31);
    strncpy_s(deathHit.hitzone, "killed", 15);
    deathHit.damage = 0.0f;
    deathHit.distance = distance;
    deathHit.timeLeft = NOTIFICATION_DURATION + 1.0f; // Показываем дольше
    deathHit.totalTime = NOTIFICATION_DURATION + 1.0f;
    deathHit.animScale = 0.0f;
    deathHit.isAnimatingIn = true;
    deathHit.isDeath = true;
    
    if (notificationCount < 5) notificationCount++;
}

// Функция для рисования супер плавного кругового прогресс-бара
void DrawCircularProgress(ImDrawList* draw, ImVec2 center, float radius, float progress, ImU32 color, float thickness) {
    if (progress <= 0.0f) return;
    
    const int segments = 128; // Еще больше сегментов для максимальной плавности
    const float angleStep = (2.0f * IM_PI) / segments;
    const float startAngle = -IM_PI / 2.0f; // Начинаем сверху
    
    // Плавное заполнение с интерполяцией
    float totalAngle = 2.0f * IM_PI * progress;
    int fullSegments = (int)(segments * progress);
    float partialSegment = (segments * progress) - fullSegments;
    
    // Рисуем полные сегменты
    for (int i = 0; i < fullSegments; i++) {
        float angle1 = startAngle + angleStep * i;
        float angle2 = startAngle + angleStep * (i + 1);
        
        ImVec2 p1 = ImVec2(center.x + std::cosf(angle1) * radius, center.y + std::sinf(angle1) * radius);
        ImVec2 p2 = ImVec2(center.x + std::cosf(angle2) * radius, center.y + std::sinf(angle2) * radius);
        
        draw->AddLine(p1, p2, color, thickness);
    }
    
    // Рисуем частичный сегмент для плавности
    if (partialSegment > 0.0f && fullSegments < segments) {
        float angle1 = startAngle + angleStep * fullSegments;
        float angle2 = angle1 + angleStep * partialSegment;
        
        ImVec2 p1 = ImVec2(center.x + std::cosf(angle1) * radius, center.y + std::sinf(angle1) * radius);
        ImVec2 p2 = ImVec2(center.x + std::cosf(angle2) * radius, center.y + std::sinf(angle2) * radius);
        
        // Плавное затухание альфы для частичного сегмента
        ImU32 fadeColor = (color & 0x00FFFFFF) | ((ImU32)(((color >> 24) & 0xFF) * partialSegment) << 24);
        draw->AddLine(p1, p2, fadeColor, thickness);
    }
}

void hitnotify::draw() {
    if (!config::show_hitnotify || notificationCount == 0) return;
    
    float deltaTime = ImGui::GetIO().DeltaTime;
    ImVec2 screenSize = ImGui::GetIO().DisplaySize;
    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    
    float notifWidth = 350.0f;
    float notifHeight = 45.0f;
    float spacing = 6.0f;
    float startY = 60.0f;
    float rightMargin = 15.0f;
    
    // Обновляем и рисуем уведомления
    for (int i = 0; i < notificationCount; i++) {
        HitNotification& notif = notifications[i];
        
        // Обновляем время
        notif.timeLeft -= deltaTime;
        
        // Анимация появления/исчезновения
        if (notif.isAnimatingIn) {
            notif.animScale += deltaTime / ANIMATION_DURATION;
            if (notif.animScale >= 1.0f) {
                notif.animScale = 1.0f;
                notif.isAnimatingIn = false;
            }
        } else if (notif.timeLeft <= ANIMATION_DURATION) {
            notif.animScale = notif.timeLeft / ANIMATION_DURATION;
        }
        
        // Удаляем истёкшие уведомления
        if (notif.timeLeft <= 0.0f) {
            for (int j = i; j < notificationCount - 1; j++) {
                notifications[j] = notifications[j + 1];
            }
            notificationCount--;
            i--;
            continue;
        }
        
        // Easing анимация
        float t = notif.animScale;
        t = 1.0f - std::powf(1.0f - t, 3.0f);
        
        // Позиция уведомления
        float posY = startY + i * (notifHeight + spacing);
        float posX = screenSize.x - rightMargin - (notifWidth * t);
        
        int alpha = (int)(255 * t);
        
        // Современный градиентный фон
        ImVec2 bgMin = ImVec2(posX, posY);
        ImVec2 bgMax = ImVec2(posX + notifWidth * t, posY + notifHeight * t);
        
        // Основной фон с градиентом
        draw->AddRectFilledMultiColor(
            bgMin, bgMax,
            IM_COL32(20, 25, 30, (int)(220 * t)),  // Темнее слева
            IM_COL32(25, 30, 35, (int)(220 * t)),  // Светлее справа
            IM_COL32(25, 30, 35, (int)(220 * t)),
            IM_COL32(20, 25, 30, (int)(220 * t))
        );
        
        // Тонкая рамка
        draw->AddRect(bgMin, bgMax, IM_COL32(40, 45, 50, alpha), 6.0f * t, 0, 1.0f);
        
        // Цветная полоска слева - cyan для хитов, красная для death
        ImU32 accentColor = notif.isDeath ? IM_COL32(255, 80, 80, alpha) : IM_COL32(0, 200, 200, alpha);
        draw->AddRectFilled(
            ImVec2(posX, posY),
            ImVec2(posX + 3.0f * t, posY + notifHeight * t),
            accentColor,
            0.0f
        );
        
        // Рисуем текст
        if (t > 0.2f) {
            float padding = 12.0f * t;
            
            // [ProtoWare] в cyan цвете
            ImVec2 brandPos = ImVec2(posX + padding + 3.0f * t, posY + padding);
            draw->AddText(brandPos, IM_COL32(0, 200, 200, alpha), "[ProtoWare]");
            
            // Основной текст - разный для death и обычных хитов
            char hitText[128];
            ImVec2 hitPos = ImVec2(posX + padding + 3.0f * t, posY + padding + 16.0f * t);
            
            if (notif.isDeath) {
                // Death уведомление - красным цветом
                snprintf(hitText, sizeof(hitText), "Killed %s, distance %.1fm", notif.playerName, notif.distance);
                draw->AddText(hitPos, IM_COL32(255, 80, 80, alpha), hitText);
                
                // Добавляем иконку черепа
                //ImVec2 skullPos = ImVec2(posX + notifWidth * t - 35.0f * t, posY + padding + 16.0f * t);
                //draw->AddText(skullPos, IM_COL32(255, 80, 80, alpha), "💀");
            } else {
                // Обычное hit уведомление
                snprintf(hitText, sizeof(hitText), "Hit %s in %s for %.1f damage (%.1fm)", 
                        notif.playerName, notif.hitzone, notif.damage, notif.distance);
                draw->AddText(hitPos, IM_COL32(255, 255, 255, alpha), hitText);
            }
        }
        
        // Круговой прогресс-бар справа
        if (t > 0.1f) {
            float circleRadius = 8.0f * t; // Возвращаем к 8px
            ImVec2 circleCenter = ImVec2(posX + notifWidth * t - 22.0f * t, posY + notifHeight * t * 0.5f);
            
            // Фон круга (темнее)
            draw->AddCircleFilled(circleCenter, circleRadius + 1.2f, IM_COL32(10, 15, 20, alpha), 32);
            
            // Прогресс (от 0 до 1, где 1 = полный круг = время истекло)
            float progress = 1.0f - (notif.timeLeft / notif.totalTime);
            
            // Применяем easing для более плавного заполнения
            float smoothProgress = progress * progress * (3.0f - 2.0f * progress); // Smooth step
            
            // Фоновая дорожка (серая)
            draw->AddCircle(circleCenter, circleRadius, IM_COL32(25, 30, 35, alpha), 32, 1.8f * t);
            
            // Рисуем прогресс-бар с плавным заполнением
            if (smoothProgress > 0.0f) {
                DrawCircularProgress(draw, circleCenter, circleRadius, smoothProgress, IM_COL32(0, 220, 220, alpha), 2.2f * t);
            }
            
            // Внутренний круг для контраста
            draw->AddCircleFilled(circleCenter, circleRadius - 2.5f * t, IM_COL32(18, 23, 28, (int)(160 * t)), 24);
        }
    }
}