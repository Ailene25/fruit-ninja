#include "splashkit.h"
#include "splashkit-arrays.h"
#include "enums.h"
#include "fruit_data.h"
#include "game_data.h"
#include "combo.h"
#include "spawner.h"
#include "weapon.h"
#include "session.h"
#include "UI.h"
#include "loader.h"
#include "fruit_manager.h"
#include <iostream>
#include <fstream>
#include <cmath>

int main()
{
    open_window("Fruit Ninja", 1920, 1020);

    bitmap background = load_bitmap("wood", "wood_background.png");

    dynamic_array<fruit_data> fruit;
    dynamic_array<slice_data> slice;
    game_data data;
    spawner fruit_spawner;
    combo current_combo;
    gun player_gun;
    knife player_knife;
    game_state previous_state;
    loader load_fruit_bitmap;
    levels current_level = NO_LEVEL;
    WEAPON current_weapon = GUN;
    levels level_selected;

    load_fruit_bitmap.load_fruits();
    load_fruit_bitmap.load_crosshair();
    load_fruit_bitmap.load_lives();
    load_fruit_bitmap.load_sounds();
    load_fruit_bitmap.load_fonts();
    load_fruit_bitmap.load_logo();

    game_state last_state = PAUSE;

    if (active_previous_session())
    {
        load_previous_session(data, data.game_over, current_level, current_weapon, fruit_spawner);
        data.current_state = CONTINUE;
    }

    while (data.current_state != EXIT)
    {
        process_events();

        if (key_typed(ESCAPE_KEY)&&(data.current_state==PLAYING || data.current_state==MENU || data.current_state == GAME_OVER))
        {
            previous_state = data.current_state;
            data.current_state = PAUSE;
        }

        if (data.current_state != last_state)
        {
            if (data.current_state == MENU)
            {
                stop_sound_effect("playing");
                play_sound_effect("menu", -1);
            }

            if (data.current_state == PLAYING)
            {
                stop_sound_effect("menu");
                play_sound_effect("playing", -1);
            }

            last_state = data.current_state;
        }

        switch (data.current_state)
        {
        case MENU:
            show_mouse();
            level_selected = draw_menu(background, data.current_state, data, load_fruit_bitmap);
            if (level_selected != NO_LEVEL)
            {
                current_level = level_selected;
                data.level_selected=level_selected;
                data.current_level_high_score = data.return_current_level_high_score(level_selected);

                if(data.save_sessions[static_cast<int>(level_selected)].session_available)
                {
                    data.current_state = CONTINUE;
                }
                else
                {
                    data.reset_stats();
                    fruit_spawner.reset();
                    data.current_state = PLAYING;
                }

                switch (current_level)
                {
                case FIRST:
                    current_weapon = GUN;
                    break;
                case SECOND:
                    current_weapon = KNIFE;
                    break;
                case THIRD:
                    current_weapon = KNIFE;
                    break;
                case FOURTH:
                    current_weapon = GUN;
                    break;
                default:
                    break;
                }
            }
            break;
        case PLAYING:
            data.in_progress = true;
            fruit_movement(data, fruit, slice, fruit_spawner, current_combo, player_gun, load_fruit_bitmap, current_level, player_knife);
            slice_movement(data, slice);
            fruit_spawner.update(fruit, data, load_fruit_bitmap, current_level);
            draw_game(background, fruit, slice, data, player_gun, current_combo, load_fruit_bitmap, current_weapon, player_knife);
            break;
        case PAUSE:
            show_mouse();
            data.current_state = draw_pause(fruit, data, previous_state, slice, current_level, current_weapon, player_knife, fruit_spawner, current_combo);
            break;
        case GAME_OVER:
            show_mouse();
            stop_sound_effect("bomb");
            data.in_progress = false;
            current_combo.reset();
            draw_game_over(background, data, fruit, load_fruit_bitmap, slice, current_weapon, player_knife, fruit_spawner);
            clear_previous_session();
            break;
        case CONTINUE:
            data.current_state = draw_continue(data, fruit, slice, current_weapon, player_knife, fruit_spawner, current_level);
            break;
        case EXIT:
            break;
        }
    }
}