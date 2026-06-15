#include "loader.h"

void loader::load_fruits()
{
    full_apple = load_bitmap("full apple", "full_apple.png");
    full_banana = load_bitmap("full banana", "full_banana.png");
    full_kiwi = load_bitmap("full kiwi", "full_kiwi.png");
    full_lemon = load_bitmap("full lemon", "full_lemon.png");
    full_peach = load_bitmap("full peach", "full_peach.png");
    full_pineapple = load_bitmap("full pineapple", "full_pineapple.png");
    full_pomegrante = load_bitmap("full pomegrante", "full_pomegrante.png");
    full_watermelon = load_bitmap("full watermelon", "full_watermelon.png");
    bomb = load_bitmap("bomb", "bomb.png");
    apple_slice = load_bitmap("apple slice", "apple_slice.png");
    banana_slice = load_bitmap("banana slice", "banana_slice.png");
    kiwi_slice = load_bitmap("kiwi slice", "kiwi_slice.png");
    lemon_slice = load_bitmap("lemon slice", "lemon_slice.png");
    peach_slice = load_bitmap("peach slice", "peach_slice.png");
    pineapple_slice = load_bitmap("pineapple slice", "half_pineapple.png");
    pomegrante_slice = load_bitmap("pomegrante slice", "pomegrante_slice.png");
    watermelon_slice = load_bitmap("watermelon slice", "watermelon_slice.png");
}

void loader::load_crosshair()
{
    gun_crosshair_bmp = load_bitmap("crosshair", "gun_crosshair.png");
}

void loader::load_lives()
{
    full_life_bmp = load_bitmap("full life", "full_heart.png");
    lose_life_bmp = load_bitmap("lose life","empty_heart.png");
}

void loader:: load_sounds()
{
    sizzling_bomb_sound = load_sound_effect("bomb","sizzling_bomb.MP3");
    fruit_cut_sound = load_sound_effect("fruit_cut","fruit_cut.mp3");
    game_over_sound = load_sound_effect("game over","game_over.mp3");
    game_start_sound = load_sound_effect("game start", "game_start.mp3");
    gun_shot_sound = load_sound_effect("gunshot", "gun_shot.MP3");
    new_high_score_sound = load_sound_effect("new high score", "new_high_score.MP3");
    menu_sound = load_sound_effect("menu", "menu_ost.mp3");
    playing_sound = load_sound_effect("playing", "playing_ost.mp3");
    lose_life_sound = load_sound_effect("lose life","lose_life.MP3");
    knife_slash_sound = load_sound_effect("slash","knife_slash.MP3");
    fruit_spawn_sound = load_sound_effect("fruit spawn","fruit_spawn.MP3");
}

void loader:: load_logo()
{
    logo_bmp = load_bitmap("logo","logo.png");
}

void loader:: load_fonts()
{
    lora_font = load_font("Lora", "Lora-Bold.ttf");
}

string fruit_name(fruit_type type)
{
    switch (type)
    {
    case APPLE:
        return "full apple";
        break;
    case BANANA:
        return "full banana";
        break;
    case KIWI:
        return "full kiwi";
        break;
    case LEMON:
        return "full lemon";
        break;
    case PEACH:
        return "full peach";
        break;
    case PINEAPPLE:
        return "full pineapple";
        break;
    case WATERMELON:
        return "full watermelon";
        break;
    case BOMB:
        return "bomb";
        break;
    case POMEGRANTE:
        return "full pomegrante";
        break;
    default:
        return "error";
        break;
    }
}

string fruit_slice_name(fruit_type type)
{
    switch (type)
    {
    case APPLE:
        return "apple slice";
        break;
    case BANANA:
        return "banana slice";
        break;
    case KIWI:
        return "kiwi slice";
        break;
    case LEMON:
        return "lemon slice";
        break;
    case PEACH:
        return "peach slice";
        break;
    case PINEAPPLE:
        return "pineapple slice";
        break;
    case WATERMELON:
        return "watermelon slice";
        break;
    case POMEGRANTE:
        return "pomegrante slice";
        break;
    case BOMB:
        return "no";
    default:
        return "error";
        break;
    }
}
