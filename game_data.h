#ifndef GAME_DATA_H
#define GAME_DATA_H
#include "splashkit.h"
#include "splashkit-arrays.h"
#include <fstream>
#include <string>
#include "enums.h"
#include "loader.h"

struct save_level
{
    int score = 0;
    int lives = MAX_LIVES;
    int next_pomegranate = 10;
    bool session_available = false;
};

struct game_data
{
    int score;
    int lives_remaining;
    reason game_over;
    int current_level_high_score;
    game_state current_state = MENU;
    bool is_high_score = false;
    bool in_progress = false;
    fixed_array<int,4> all_high_scores;
    levels level_selected = NO_LEVEL;
    fixed_array<save_level,4> save_sessions;

    game_data();
    string return_high_score_file(int level);
    void load_high_score();
    bool new_high_score(int score, loader &assets);
    int return_current_level_high_score(levels level_selected);
    void add_score(int points, double multiplier = 1.0);
    bool lose_life(bool fruit_missed, loader &assets);
    void bomb_game_over(bool bomb_hit, loader &assets);
    void game_is_over(loader &assets);
    void reset_stats();
    void draw_score(loader &load_fonts);
    void draw_lives(); 
};

#endif