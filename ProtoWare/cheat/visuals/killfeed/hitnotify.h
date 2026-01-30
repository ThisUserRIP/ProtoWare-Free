#pragma once

namespace hitnotify {
    void initialize();
    void draw();
    void add_hit(const char* player_name, const char* hitzone, float damage, float distance);
    void add_death(const char* player_name, float distance);
}