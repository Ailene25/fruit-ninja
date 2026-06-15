#ifndef WEAPON_H
#define WEAPON_H
#include "splashkit.h"
#include <fstream>
#include <string>
#include "enums.h"
#include "fruit_data.h"
#include "spawner.h"
#include "game_data.h"
#include "combo.h"
#include "splashkit.h"
#include "splashkit-arrays.h"
#include "loader.h"
#include <cmath>

const int TRAIL_LENGTH = 8;
const int SPEED_THRESHOLD = 12;

struct gun
{
    bool bomb_hit;
    bool fruit_hit;

    gun();
    void fruit_shot(dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slice, spawner &fruit_spawner, game_data &data, combo &current_combo, loader &load_sound);
    void draw_crosshair();
};


struct knife
{
    bool bomb_hit;
    bool fruit_hit;
    point_2d last_position;
    bool was_held;
    point_2d trail[TRAIL_LENGTH];
    int front_trail;
    int trail_count;
    bool waiting_to_draw_trail;

    knife();
    void update(dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slice, spawner &fruit_spawner, game_data &data, combo &current_combo, loader &assets);
    void draw_trail(loader &load_sounds);
    void reset_trail();
    bool check_slash(dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slice, spawner &fruit_spawner, game_data &data, combo &current_combo, loader &assets, point_2d last_position, point_2d current_position);
    bool line_circle_intersect(point_2d last_position, point_2d current_position, point_2d fruit_location, double radius);
};

#endif