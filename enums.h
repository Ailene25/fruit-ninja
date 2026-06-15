#ifndef ENUMS_H
#define ENUMS_H
#include "splashkit.h"
#include <fstream>
#include <string>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1020;
const int MAX_FRUIT = 8;
const int POMEGRANTE_HEALTH = 2; // in the game it's a close up and then as many slashes possible within a timer
const int NORMAL_HEALTH = 1;
const int MAX_LIVES = 3;
const std::string PREVIOUS_SESSION_FILE = "previous_session.txt";

// the current game state
enum game_state
{
    MENU,
    PLAYING,
    PAUSE,
    GAME_OVER,
    CONTINUE,
    EXIT
};

// the reason why the game ended
enum reason
{
    NO,
    BOMB_HIT,
    NO_LIVES
};

enum fruit_type
{
    APPLE,
    BANANA,
    KIWI,
    LEMON,
    PEACH,
    PINEAPPLE,
    WATERMELON,
    BOMB,
    POMEGRANTE
};

enum fruit_slices
{
    APPLE_SLICE,
    BANANA_SLICE,
    KIWI_SLICE,
    LEMON_SLICE,
    PEACH_SLICE,
    PINEAPPLE_SLICE,
    WATERMELON_SLICE,
    POMEGRANTE_SLICE
};

enum WEAPON
{
    GUN,
    KNIFE
};

enum levels
{
    FIRST,
    SECOND,
    THIRD,
    FOURTH,
    NO_LEVEL
};

#endif