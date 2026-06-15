#include "UI.h"

void restart_game(dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slices, game_data &data, WEAPON current_weapon, knife &player_knife, spawner &fruit_spawner)
{
    for (int i = length(fruit) - 1; i >= 0; i--)
    {
        remove_at(fruit, i);
    }

    for (int i = length(slices) - 1; i >= 0; i--)
    {
        remove_at(slices, i);
    }

    data.current_state = PLAYING;
    data.reset_stats();
    fruit_spawner.reset();
    if (current_weapon == KNIFE)
    {
        player_knife.reset_trail();
    }
}

game_state draw_pause(dynamic_array<fruit_data> &fruit, game_data &data, game_state previous_state, dynamic_array<slice_data> &slices, levels current_level, WEAPON current_weapon, knife &player_knife, spawner &fruit_spawner, combo &current_combo)
{

    fill_rectangle(rgba_color(0.0, 0.0, 0.0, 0.01), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (previous_state == PLAYING)
    {
        if (button("Restart", rectangle_from(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 25)))
        {
            restart_game(fruit, slices, data, current_weapon, player_knife, fruit_spawner);
            return PLAYING;
        }

        if (button("Main Menu", rectangle_from(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 200, 25)))
        {
            data.save_sessions[static_cast<int>(current_level)].score = data.score;
            data.save_sessions[static_cast<int>(current_level)].lives = data.lives_remaining;
            data.save_sessions[static_cast<int>(current_level)].next_pomegranate = fruit_spawner.next_pomegrante;
            data.save_sessions[static_cast<int>(current_level)].session_available = true;

            for (int i = length(fruit) - 1; i >= 0; i--)
            {
                remove_at(fruit, i);
            }

            for (int i = length(slices) - 1; i >= 0; i--)
            {
                remove_at(slices, i);
            }

            data.reset_stats();
            fruit_spawner.reset();
            current_combo.reset();

            return MENU;
        }

        if (button("Quit", rectangle_from(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50, 200, 25)))
        {
            
            data.save_sessions[static_cast<int>(current_level)].score = data.score;
            data.save_sessions[static_cast<int>(current_level)].lives = data.lives_remaining;
            data.save_sessions[static_cast<int>(current_level)].next_pomegranate = fruit_spawner.next_pomegrante;
            data.save_sessions[static_cast<int>(current_level)].session_available = true;

            for (int i = length(fruit) - 1; i >= 0; i--)
            {
                remove_at(fruit, i);
            }

            for (int i = length(slices) - 1; i >= 0; i--)
            {
                remove_at(slices, i);
            }

            save_previous_session(data, current_level, fruit_spawner);

            data.reset_stats();
            fruit_spawner.reset();
        
            return EXIT;
        }

        if (button("Back", rectangle_from(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 100, 200, 25)))
        {
            player_knife.waiting_to_draw_trail=true;
            return PLAYING;
        }
    }

    if (previous_state == MENU)
    {
        draw_text("Quit", COLOR_WHITE, SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 2 - 10);

        if (button("Yes", rectangle_from(SCREEN_WIDTH / 2 - 320, SCREEN_HEIGHT / 2, 200, 25)))
        {
            return EXIT;
        }

        if (button("No", rectangle_from(SCREEN_WIDTH / 2 + 125, SCREEN_HEIGHT / 2, 200, 25)))
        {
            return MENU;
        }
    }

    if (previous_state == GAME_OVER)
    {
        draw_text("Quit", COLOR_WHITE, SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 2 - 10);

        if (button("Yes", rectangle_from(SCREEN_WIDTH / 2 - 320, SCREEN_HEIGHT / 2, 200, 25)))
        {
            return EXIT;
        }

        if (button("No", rectangle_from(SCREEN_WIDTH / 2 + 120, SCREEN_HEIGHT / 2, 200, 25)))
        {
            return GAME_OVER;
        }
    }
    draw_interface();

    refresh_screen();

    return PAUSE;
}

levels draw_menu(bitmap background, game_state current_state, game_data &data, loader &assets)
{

    draw_bitmap(background, 0, 0);

    draw_bitmap(bitmap_named("logo"),600,100);

    draw_bitmap("full watermelon", 300, SCREEN_HEIGHT/2-10);
    draw_text("Level 1",COLOR_BLACK,  "Lora", 30, 340, SCREEN_HEIGHT/2+170);
    draw_text("Gun Mode", COLOR_BLACK,  "Lora", 30, 320, SCREEN_HEIGHT/2+210);
    draw_text("Vertical Movement", COLOR_BLACK,  "Lora", 30, 270, SCREEN_HEIGHT/2+250);
    draw_text("High Score: "+to_string(data.all_high_scores[0]),  COLOR_BLACK,  "Lora", 30, 310, SCREEN_HEIGHT/2+290);

    draw_bitmap("full pineapple", 700, SCREEN_HEIGHT/2-150);
    draw_text("Level 2",COLOR_BLACK,  "Lora", 30, 720, SCREEN_HEIGHT/2+170);
    draw_text("Knife Mode", COLOR_BLACK,  "Lora", 30, 700, SCREEN_HEIGHT/2+210);
    draw_text("Vertical Movement", COLOR_BLACK,  "Lora", 30, 650, SCREEN_HEIGHT/2+250);
    draw_text("High Score: "+to_string(data.all_high_scores[1]),  COLOR_BLACK,  "Lora", 30, 690, SCREEN_HEIGHT/2+290);

    draw_bitmap("full banana", 1100, SCREEN_HEIGHT/2);
    draw_text("Level 3",COLOR_BLACK,  "Lora", 30, 1130, SCREEN_HEIGHT/2+170);
    draw_text("Knife Mode", COLOR_BLACK,  "Lora", 30, 1100, SCREEN_HEIGHT/2+210);
    draw_text("Curved Movement", COLOR_BLACK,  "Lora", 30, 1050, SCREEN_HEIGHT/2+250);
    draw_text("High Score: "+to_string(data.all_high_scores[2]),  COLOR_BLACK,  "Lora", 30, 1100, SCREEN_HEIGHT/2+290);

    draw_bitmap("full apple", 1500, SCREEN_HEIGHT/2+20);
    draw_text("Level 4",COLOR_BLACK,  "Lora", 30, 1500, SCREEN_HEIGHT/2+170);
    draw_text("Gun Mode", COLOR_BLACK,  "Lora", 30, 1490, SCREEN_HEIGHT/2+210);
    draw_text("Curved Movement", COLOR_BLACK,  "Lora", 30, 1440, SCREEN_HEIGHT/2+250);
    draw_text("High Score: "+to_string(data.all_high_scores[3]),  COLOR_BLACK,  "Lora", 30, 1490, SCREEN_HEIGHT/2+290);

    if(mouse_clicked(LEFT_BUTTON))
    {
        if(bitmap_point_collision(assets.full_watermelon, 300, SCREEN_HEIGHT/2, mouse_position().x,mouse_position().y))
        {
            return FIRST;
        }
        if(bitmap_point_collision(assets.full_pineapple, 700, SCREEN_HEIGHT/2-100, mouse_position().x,mouse_position().y))
        {
            return SECOND;
        }
        if(bitmap_point_collision(assets.full_banana, 1100, SCREEN_HEIGHT/2, mouse_position().x,mouse_position().y))
        {
            return THIRD;
        }
        if(bitmap_point_collision(assets.full_apple, 1500, SCREEN_HEIGHT/2+20, mouse_position().x,mouse_position().y))
        {
            return FOURTH;
        }
    }

    refresh_screen();
    return NO_LEVEL;
}

void draw_game(bitmap background, const dynamic_array<fruit_data> &fruit, const dynamic_array<slice_data> &slice, game_data &data, gun &player_gun, combo &current_combo, loader &load_fonts, WEAPON current_weapon, knife &player_knife)
{
    clear_screen(COLOR_BROWN);
    draw_bitmap(background, 0, 0);

    hide_mouse();

    for (int i = 0; i < length(fruit); i++)
    {
        draw_sprite(fruit[i].fruit_object);
    }

    for (int i = 0; i < length(slice); i++)
    {
        draw_sprite(slice[i].left_slice);
        draw_sprite(slice[i].right_slice);
    }

    if(current_weapon==GUN)
    {
        player_gun.draw_crosshair();
    }

    if(current_weapon==KNIFE)
    {
        player_knife.draw_trail(load_fonts);
    }

    data.draw_score(load_fonts);
    data.draw_lives();
    current_combo.draw_combo(load_fonts);
    refresh_screen(60);
}

void draw_game_over(bitmap background, game_data &data, dynamic_array<fruit_data> &fruit, loader &load_font, dynamic_array<slice_data> &slices, WEAPON current_weapon, knife &player_knife, spawner &fruit_spawner)
{
    clear_screen();
    draw_bitmap(background, 0, 0);

    draw_text("GAME OVER", COLOR_RED, "Lora", 100, SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 150);
    draw_text("Score: " + to_string(data.score), COLOR_BLACK, "Lora", 30, SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2);
    draw_text("Best: " + to_string(data.current_level_high_score), COLOR_BLACK, "Lora", 30, SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 40);

    if (data.is_high_score)
    {
        fill_rectangle(rgba_color(0.5, 0.5, 0.5, 0.18), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        draw_text("NEW HIGH SCORE!", COLOR_YELLOW, "Lora", 100, SCREEN_WIDTH / 2 - 420, SCREEN_HEIGHT / 2 - 300);
    }

    if (button("Replay", rectangle_from(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 100, 200, 25)))
    {
        restart_game(fruit, slices, data, current_weapon, player_knife, fruit_spawner);
    }

    if (button("Main Menu", rectangle_from(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 150, 200, 25)))
    {
        data.current_state = MENU;
        for (int i = length(fruit) - 1; i >= 0; i--)
        {
            remove_at(fruit, i);
        }

        for (int i = length(slices) - 1; i >= 0; i--)
        {
            remove_at(slices, i);
        }
        data.reset_stats();
        fruit_spawner.reset();
    }

    draw_interface();

    refresh_screen();
}

game_state draw_continue(game_data &data, dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slices, WEAPON current_weapon, knife &player_knife, spawner &fruit_spawner, levels current_level)
{
    fill_rectangle(rgba_color(0.0, 0.0, 0.0, 0.01), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    draw_text("continue from previous game?", COLOR_WHITE, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 10);

    if (button("Yes", rectangle_from(SCREEN_WIDTH / 2 - 320, SCREEN_HEIGHT / 2, 200, 25)))
    {
        player_knife.waiting_to_draw_trail=true;
        data.score = data.save_sessions[static_cast<int>(current_level)].score;
        data.lives_remaining = data.save_sessions[static_cast<int>(current_level)].lives;
        fruit_spawner.next_pomegrante = data.save_sessions[static_cast<int>(current_level)].next_pomegranate;
        data.save_sessions[static_cast<int>(current_level)].session_available = false;
        return PLAYING;
    }

    if (button("No", rectangle_from(SCREEN_WIDTH / 2 + 120, SCREEN_HEIGHT / 2, 200, 25)))
    {
        if(data.in_progress)
        {
            restart_game(fruit, slices, data, current_weapon, player_knife, fruit_spawner);
            return PLAYING;
        }
        clear_previous_session();
        data.reset_stats();
        return MENU;
    }

    draw_interface();
    refresh_screen();

    return CONTINUE;
}
