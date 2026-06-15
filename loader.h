#ifndef LOADER_H
#define LOADER_H
#include "splashkit.h"
#include <fstream>
#include <string>
#include "enums.h"

struct loader
{
    bitmap full_apple, full_banana, full_kiwi, full_lemon, full_peach, full_pineapple, full_pomegrante, full_watermelon, bomb;
    bitmap apple_slice, banana_slice, kiwi_slice, lemon_slice, peach_slice, pineapple_slice, pomegrante_slice, watermelon_slice;
    bitmap gun_crosshair_bmp;
    bitmap full_life_bmp, lose_life_bmp, logo_bmp;
    font lora_font;
    sound_effect sizzling_bomb_sound, new_high_score_sound, fruit_cut_sound, game_over_sound, game_start_sound, menu_sound, playing_sound, gun_shot_sound, lose_life_sound, knife_slash_sound, fruit_spawn_sound;

    void load_fruits();
    void load_crosshair();
    void load_lives();
    void load_sounds();
    void load_fonts();
    void load_logo();
};

string fruit_name(fruit_type type);
string fruit_slice_name(fruit_type type);

#endif