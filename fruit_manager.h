#ifndef FRUIT_MANAGER_H
#define FRUIT_MANAGER_H
#include "splashkit.h"
#include "splashkit-arrays.h"
#include <fstream>
#include <string>
#include "combo.h"
#include "weapon.h"
#include "game_data.h"
#include "fruit_data.h"
#include "spawner.h"
#include "enums.h"
#include <iostream>

void fruit_movement(game_data &data, dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slice, spawner &fruit_spawner, combo &current_combo, gun &player_gun, loader &load_sound, levels current_level, knife &player_knife);
void slice_movement(game_data &data, dynamic_array<slice_data> &slice);

#endif