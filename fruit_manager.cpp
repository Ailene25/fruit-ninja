#include "fruit_manager.h"

void fruit_movement(game_data &data, dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slice, spawner &fruit_spawner, combo &current_combo, gun &player_gun, loader &load_sound, levels current_level, knife &player_knife)
{
    switch (current_level)
    {
    case FIRST:
        for (int i = 0; i < length(fruit); i++)
            {
                if (fruit[i].active)
                {
                    double y = sprite_y(fruit[i].fruit_object);
                    // draw the changing positions
                    sprite_set_y(fruit[i].fruit_object, y+fruit[i].y_velocity);

                    fruit[i].y_velocity+=0.035;

                    if(sprite_y(fruit[i].fruit_object)>SCREEN_HEIGHT)
                    {
                        if(fruit[i].type!=BOMB)
                        {
                            data.lose_life(true, load_sound);
                        }
                        else
                        {
                            stop_sound_effect("bomb");
                        }
                        fruit[i].active = false;
                        free_sprite(fruit[i].fruit_object);
                        remove_at(fruit,i);
                        i--;
                    }
                }
            }

            player_gun.fruit_shot(fruit, slice, fruit_spawner, data, current_combo, load_sound);
        break;
    case SECOND:
            for (int i = 0; i < length(fruit); i++)
            {
                if (fruit[i].active)
                {
                    double y = sprite_y(fruit[i].fruit_object);
                    // draw the changing positions
                    sprite_set_y(fruit[i].fruit_object, y+fruit[i].y_velocity);

                    fruit[i].y_velocity+=0.035;

                    if(sprite_y(fruit[i].fruit_object)>SCREEN_HEIGHT)
                    {
                        if(fruit[i].type!=BOMB)
                        {
                            data.lose_life(true, load_sound);
                        }
                        else
                        {
                            stop_sound_effect("bomb");
                        }
                        fruit[i].active = false;
                        free_sprite(fruit[i].fruit_object);
                        remove_at(fruit,i);
                        i--;
                    }
                }
            }

            player_knife.update(fruit,slice,fruit_spawner,data,current_combo,load_sound);

            break;
    case THIRD:
            // handle the movement for all active fruits
            for (int i = 0; i < length(fruit); i++)
            {
                if (fruit[i].active)
                {
                    fruit[i].t+=fruit[i].t_speed; //how far along the fruit is on the path according to their movement speed
                    
                    //bezier formula: B(t) = (1-t)^2 P0 + 2(1-t)tP1 + t^2P2
                    double result = 1-fruit[i].t;

                    // Get current sprite position
                    double new_y = (result*result*fruit[i].p0.y) + (2*result*fruit[i].t*fruit[i].p1.y) + (fruit[i].t*fruit[i].t*fruit[i].p2.y);
                    double new_x = (result*result*fruit[i].p0.x) + (2*result*fruit[i].t*fruit[i].p1.x) + (fruit[i].t*fruit[i].t*fruit[i].p2.x);

                    // draw the changing positions
                    sprite_set_y(fruit[i].fruit_object, new_y);
                    sprite_set_x(fruit[i].fruit_object, new_x);

                    if(sprite_y(fruit[i].fruit_object)>SCREEN_HEIGHT)
                    {
                        if(fruit[i].type!=BOMB)
                        {
                            data.lose_life(true, load_sound);
                        }
                        else
                        {
                            stop_sound_effect("bomb");
                        }
                        fruit[i].active = false;
                        free_sprite(fruit[i].fruit_object);
                        remove_at(fruit,i);
                        i--;
                    }
                }
            }

            player_knife.update(fruit,slice,fruit_spawner,data,current_combo,load_sound);
            break;
    case FOURTH:
             // handle the movement for all active fruits
            for (int i = 0; i < length(fruit); i++)
            {
                if (fruit[i].active)
                {
                    fruit[i].t+=fruit[i].t_speed; //how far along the fruit is on the path according to their movement speed
                    
                    //bezier formula: B(t) = (1-t)^2 P0 + 2(1-t)tP1 + t^2P2
                    double result = 1-fruit[i].t;

                    // Get current sprite position
                    double new_y = (result*result*fruit[i].p0.y) + (2*result*fruit[i].t*fruit[i].p1.y) + (fruit[i].t*fruit[i].t*fruit[i].p2.y);
                    double new_x = (result*result*fruit[i].p0.x) + (2*result*fruit[i].t*fruit[i].p1.x) + (fruit[i].t*fruit[i].t*fruit[i].p2.x);

                    // draw the changing positions
                    sprite_set_y(fruit[i].fruit_object, new_y);
                    sprite_set_x(fruit[i].fruit_object, new_x);

                    if(sprite_y(fruit[i].fruit_object)>SCREEN_HEIGHT)
                    {
                        if(fruit[i].type!=BOMB)
                        {
                            data.lose_life(true, load_sound);
                        }
                        else
                        {
                            stop_sound_effect("bomb");
                        }
                        fruit[i].active = false;
                        free_sprite(fruit[i].fruit_object);
                        remove_at(fruit,i);
                        i--;
                    }
                }
            }

            player_gun.fruit_shot(fruit, slice, fruit_spawner, data, current_combo, load_sound);
            break;
    default:
        break;
    }
}

void slice_movement(game_data &data, dynamic_array<slice_data> &slice)
{
    for (int i = length(slice) - 1; i >= 0; i--)
            {
                if (length(slice) == 0)
                {
                    break;
                }

                if (slice[i].active)
                {
                    // Get current sprite position
                    double y_left_slice = sprite_y(slice[i].left_slice);
                    double y_right_slice = sprite_y(slice[i].right_slice);

                    // draw the changing y position
                    sprite_set_y(slice[i].left_slice, y_left_slice + slice[i].y_velocity);
                    sprite_set_y(slice[i].right_slice, y_right_slice + slice[i].y_velocity);
                    // add to the y value to make it come down
                    slice[i].y_velocity += 0.4;

                    double x_left_slice = sprite_x(slice[i].left_slice);
                    double x_right_slice = sprite_x(slice[i].right_slice);

                    sprite_set_x(slice[i].left_slice, x_left_slice + slice[i].x_velocity_left);
                    sprite_set_x(slice[i].right_slice, x_right_slice + slice[i].x_velocity_right);

                    sprite_set_rotation(slice[i].left_slice, sprite_rotation(slice[i].left_slice) - slice[i].rotation_speed);
                    sprite_set_rotation(slice[i].right_slice, sprite_rotation(slice[i].right_slice) - slice[i].rotation_speed);

                    if (sprite_y(slice[i].left_slice) > SCREEN_HEIGHT && sprite_y(slice[i].right_slice) > SCREEN_HEIGHT)
                    {
                        slice[i].active = false;
                        free_sprite(slice[i].left_slice);
                        free_sprite(slice[i].right_slice);
                        remove_at(slice, i);
                    }
                }
            }
}