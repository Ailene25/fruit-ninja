#ifndef SPAWNER_H
#define SPAWNER_H
#include "splashkit.h"
#include <fstream>
#include <string>
#include "enums.h"
#include "game_data.h"
#include "loader.h"
#include "fruit_data.h"
#include "splashkit.h"
#include "splashkit-arrays.h"

class spawner
{
    private:
        double current_frame;
        double spawn_interval;
        int difficulty;

        void update_difficulty(game_data &data);
        fruit_data spawn_fruit(loader &load_sound, levels current_level);
        fruit_data spawn_pomegrante(levels current_level, loader &load_sound);
    public:
        int next_pomegrante = 10;

        spawner();
        void reset();
        void update(dynamic_array<fruit_data> &fruit, game_data &data, loader &load_sound, levels current_level);
        slice_data spawn_fruit_slice(const fruit_data &fruit);
        void add_fruit(dynamic_array<fruit_data> &fruit, fruit_data new_fruit);
        void add_fruit_slice(dynamic_array<slice_data> &slice, slice_data new_slice);
};

#endif