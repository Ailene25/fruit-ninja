#include "game_data.h"

game_data::game_data()
{
    score = 0;
    lives_remaining = MAX_LIVES;
    game_over = NO;
    current_level_high_score = 0;
    load_high_score();
}

string game_data::return_high_score_file(int level)
{
    switch(level)
    {
        case 0:
            return "level_one_high_score.txt";
            break;
        case 1:
            return "level_two_high_score.txt";
            break;
        case 2:
            return "level_three_high_score.txt";
            break;
        case 3:
            return "level_four_high_score.txt";
            break;
        default:
            return "error";
            break;
    }
}

void game_data::load_high_score()
{
    for(int i = 0; i<4; i++)
    {
        all_high_scores[i]=0;
    }

    for (int i = 0; i <4; i++)
    {
        std::ifstream file(return_high_score_file(i)); // ifstream is for reading the file
        if (file.is_open())
        {
            file >> all_high_scores[i];
            file.close();
        }
    }
}

int game_data::return_current_level_high_score(levels level_selected)
{
    load_high_score();
    return all_high_scores[level_selected];
}

bool game_data::new_high_score(int score, loader &assets)
{
    if (score > current_level_high_score)
    {
        stop_sound_effect("game over");
        play_sound_effect("new high score");
        current_level_high_score = score;
        all_high_scores[level_selected]=current_level_high_score;
        std::ofstream file(return_high_score_file(static_cast<int>(level_selected))); // ofstream is for writing to the file
        if (file.is_open())
        {
            file << current_level_high_score;
            file.close();
        }

        return true;
    }
    else
    {
        return false;
    }
}

void game_data::add_score(int points, double multiplier)
{
    score += static_cast<int>(points * multiplier); // use static_cast to convert double to a int
}

bool game_data::lose_life(bool fruit_missed, loader &assets) // this should only update the lose life not calculate whether the click missed a fruit
{
    if (fruit_missed == true)
    {
        lives_remaining -= 1; // make the X red
        play_sound_effect("lose life");
        if (lives_remaining == 0)
        {
            game_over = NO_LIVES;
            game_is_over(assets);
        }
        return true;
    }
    return false;
}

void game_data::bomb_game_over(bool bomb_hit, loader &assets) // can maybe call the special black screen effects
{
    if (bomb_hit == true)
    {
        game_over = BOMB_HIT;
        game_is_over(assets);
    }
}

void game_data::game_is_over(loader &assets) // save the high score to a text file
{
    if (game_over == NO)
    {
        return;
    }
    current_state = GAME_OVER;
    play_sound_effect("game over");
    is_high_score = new_high_score(score, assets);
}

void game_data::reset_stats()
{
    score = 0;
    lives_remaining = MAX_LIVES;
    game_over = NO;
    is_high_score = false;
}

void game_data::draw_score(loader &load_fonts)
{
    draw_text("Score: " + to_string(score), COLOR_WHITE, "Lora", 30, 250, 100);
}

void game_data::draw_lives()
{
    int x_position=SCREEN_WIDTH-500;
    int lose_lives = MAX_LIVES - lives_remaining;
    
    for (int i = 0; i < MAX_LIVES; i++)
    {
        if(i<lose_lives)
        {
            draw_bitmap(bitmap_named("lose life"),x_position,90);
        }
        else
        {
            draw_bitmap(bitmap_named("full life"),x_position,90);
        }

        x_position+=100;
    }
}