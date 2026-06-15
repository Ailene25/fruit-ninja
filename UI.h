#ifndef UI_H
#define UI_H
#include "splashkit.h"
#include <fstream>
#include <string>
#include "splashkit.h"
#include "splashkit-arrays.h"
#include "fruit_data.h"
#include "game_data.h"
#include "session.h"
#include "weapon.h"
#include "enums.h"
#include "loader.h"

void restart_game(dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slices, game_data &data, WEAPON current_weapon, knife &player_knife, spawner &fruit_spawner);
game_state draw_pause(dynamic_array<fruit_data> &fruit, game_data &data, game_state previous_state, dynamic_array<slice_data> &slices, levels current_level, WEAPON current_weapon, knife &player_knife, spawner &fruit_spawner, combo &current_combo);
levels draw_menu(bitmap background, game_state current_state, game_data &data, loader &assets);
void draw_game(bitmap background, const dynamic_array<fruit_data> &fruit, const dynamic_array<slice_data> &slice, game_data &data, gun &player_gun, combo &current_combo, loader &load_fonts, WEAPON current_weapon, knife &player_knife);
void draw_game_over(bitmap background, game_data &data, dynamic_array<fruit_data> &fruit, loader &load_font, dynamic_array<slice_data> &slices, WEAPON current_weapon, knife &player_knife, spawner &fruit_spawner);
game_state draw_continue(game_data &data, dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slices, WEAPON current_weapon, knife &player_knife, spawner &fruit_spawner, levels current_level);

#endif