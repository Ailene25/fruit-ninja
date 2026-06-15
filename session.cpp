#include "session.h"

void save_previous_session(game_data &data, levels current_level, const spawner &fruit_spawner)
{
    std::ofstream file(PREVIOUS_SESSION_FILE); // ofstream is for writing to the file
    if (file.is_open())
    {
        file << data.score << "\n";
        file << data.lives_remaining << "\n";
        file << fruit_spawner.next_pomegrante << "\n";
        file << (int)current_level << "\n";
        file.close();
    }
}

void load_previous_session(game_data &data, reason &game_over, levels &current_level, WEAPON &current_weapon, spawner &fruit_spawner)
{
    std::ifstream file(PREVIOUS_SESSION_FILE); // ifstream is for reading the file
    int level_int;
    if (file.is_open())
    {
        file >> data.score >> data.lives_remaining >> fruit_spawner.next_pomegrante >> level_int;
        current_level = static_cast<levels>(level_int);
        data.level_selected = current_level;
        data.current_level_high_score = data.return_current_level_high_score(current_level);
        file.close();
        game_over = NO;

        data.save_sessions[static_cast<int>(current_level)].score = data.score;
        data.save_sessions[static_cast<int>(current_level)].lives = data.lives_remaining;
        data.save_sessions[static_cast<int>(current_level)].next_pomegranate  = fruit_spawner.next_pomegrante;
        data.save_sessions[static_cast<int>(current_level)].session_available = true;

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
}

void clear_previous_session()
{
    std::ofstream(PREVIOUS_SESSION_FILE, std::ios::trunc);
}

bool active_previous_session()
{
    std::ifstream file(PREVIOUS_SESSION_FILE);
    return file.peek() != std::ifstream::traits_type::eof();;
}