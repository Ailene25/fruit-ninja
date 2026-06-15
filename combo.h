#ifndef COMBO_H
#define COMBO_H
#include "splashkit.h"
#include <fstream>
#include <string>
#include "enums.h"
#include "loader.h"

struct combo
{
    int consecutive_hits;
    bool combo_active;
    double multiplier;

    combo();
    void register_hit();
    void reset();
    void draw_combo(loader &load_fonts);
};

#endif