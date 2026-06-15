#include "combo.h"

combo::combo()
{
    consecutive_hits = 0;
    combo_active = false;
    multiplier = 1;
}

void combo::register_hit()
{
    if (consecutive_hits == 0)
    {
        combo_active = true;
    }
    multiplier += 0.05;
    consecutive_hits += 1;
    }

void combo::reset() // in my hit fruit, I need to check if the combo_active is active, if a blank shot is fired, combo is lost or go according to a timer
{
    consecutive_hits = 0;
    combo_active = false;
    multiplier = 1;
}

void combo::draw_combo(loader &load_fonts)
{
    draw_text("Consecutive hits: "+to_string(consecutive_hits), COLOR_WHITE, "Lora", 30, SCREEN_WIDTH/2, 100);
}