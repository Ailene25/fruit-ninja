#ifndef SESSION_H
#define SESSION_H
#include "splashkit.h"
#include "splashkit-arrays.h"
#include <fstream>
#include <string>
#include "enums.h"
#include "game_data.h"
#include "spawner.h"

void save_previous_session(game_data &data, levels current_level, const spawner &fruit_spawner);
void load_previous_session(game_data &data, reason &game_over, levels &current_level, WEAPON &current_weapon, spawner &fruit_spawner);
void clear_previous_session();
bool active_previous_session();

#endif