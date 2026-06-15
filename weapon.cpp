#include "weapon.h"
#include <cmath>
using namespace std;

gun::gun()
{
    bomb_hit = false;
    fruit_hit = false;
}

void gun::fruit_shot(dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slice, spawner &fruit_spawner, game_data &data, combo &current_combo, loader &load_sound)
{
    if (!mouse_clicked(LEFT_BUTTON))
    {
        return;
    }

    play_sound_effect("gunshot");
    fruit_hit = false;

    for (int i = 0; i < length(fruit); i++)
    {
        if (sprite_point_collision(fruit[i].fruit_object, point_at(mouse_x(), mouse_y())))
        {

            if (fruit[i].type == BOMB)
            {
                bomb_hit = true;
                data.bomb_game_over(bomb_hit, load_sound);
                return;
            }

            if (fruit[i].type == POMEGRANTE)
            {
                fruit[i].health -= 1;
                if (fruit[i].health == 0)
                {
                    data.add_score(2, current_combo.multiplier);
                    fruit[i].active = false;
                    fruit_spawner.add_fruit_slice(slice, fruit_spawner.spawn_fruit_slice(fruit[i]));
                    fruit[i].active = false;
                    remove_at(fruit, i);
                }
                current_combo.register_hit();
                fruit_hit = true;
                return;
            }

            data.add_score(1, current_combo.multiplier);
            fruit_spawner.add_fruit_slice(slice, fruit_spawner.spawn_fruit_slice(fruit[i]));
            fruit[i].active = false;
            free_sprite(fruit[i].fruit_object);
            remove_at(fruit, i);
            current_combo.register_hit();
            fruit_hit = true;
            return;
        }
    }

    if(fruit_hit!=true)
    {
        current_combo.reset();
    }
}

void gun::draw_crosshair()
{
    point_2d mouse_pos = mouse_position();

    draw_bitmap("gun_crosshair.png", mouse_pos.x-(bitmap_width("crosshair")/2), mouse_pos.y-(bitmap_height("crosshair")/2));
}

knife::knife()
{
    bomb_hit = false;
    fruit_hit = false;
    last_position = mouse_position();
    was_held = false;
    front_trail = 0;
    trail_count = 0;
    waiting_to_draw_trail = false;
}

void knife::update(dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slice, spawner &fruit_spawner, game_data &data, combo &current_combo, loader &assets)
{
    point_2d current_position = mouse_position();
    bool held = mouse_down(LEFT_BUTTON);

    if(waiting_to_draw_trail)
    {
        if(!held)
        {
            waiting_to_draw_trail=false;
        }

        last_position = current_position;
        was_held = held;
        return;
    }

    trail[front_trail] = current_position;
    front_trail = (front_trail+1) % TRAIL_LENGTH; //circular queue
    if(trail_count<TRAIL_LENGTH)
    {
        trail_count++;
    }

    if(held && was_held)
    {
        double dx = current_position.x - last_position.x;
        double dy = current_position.y - last_position.y;
        double dist = sqrt((float)(dx * dx + dy * dy));  

        if(dist>=SPEED_THRESHOLD)
        {
            check_slash(fruit, slice, fruit_spawner, data, current_combo, assets, last_position, current_position);
        }
    }
    else if(!held)
    {
        trail_count = 0;
    }

    last_position = current_position;
    was_held = held;
}

void knife::draw_trail(loader &load_sounds)
{
    
    if(trail_count<2) //need at least 2 points to draw a trail
    {
        return; //can't draw a trail with 0 or just 1 point
    }

    //play_sound_effect("slash");

    for (int i = 0; i < trail_count; i++)
    {
        int idx_a = (front_trail - i - 1 + TRAIL_LENGTH) % TRAIL_LENGTH;
        int idx_b = (front_trail - i + TRAIL_LENGTH) % TRAIL_LENGTH;

        double alpha = static_cast<double>(trail_count - i) / trail_count;
        draw_line(rgba_color(1.0, 1.0, 1.0, alpha * 0.8), trail[idx_a].x, trail[idx_a].y, trail[idx_b].x, trail[idx_b].y);
    }
}

void knife::reset_trail()
{

    trail_count=0;
    bomb_hit = false;
    fruit_hit = false;
    last_position = mouse_position();
    was_held = false;
    front_trail = 0;
    waiting_to_draw_trail = true;

    for (int i = 0; i < TRAIL_LENGTH; i++)
    {
        trail[i].x=0;
        trail[i].y=0;
    }
    
}

bool knife::check_slash(dynamic_array<fruit_data> &fruit, dynamic_array<slice_data> &slice, spawner &fruit_spawner, game_data &data, combo &current_combo, loader &assets, point_2d last_position, point_2d current_position)
{
    point_2d fruit_location;
    
    for (int i = 0; i < length(fruit); i++)
    {
        if(!fruit[i].active)
        {
            continue;
        }

        fruit_location = point_at(sprite_x(fruit[i].fruit_object), sprite_y(fruit[i].fruit_object));

        if(!line_circle_intersect(last_position, current_position, fruit_location, fruit[i].radius))
        {
            continue;
        }

        if(fruit[i].type==BOMB)
        {
            bomb_hit = true;
            data.bomb_game_over(bomb_hit, assets);
            return false;
        }

         if (fruit[i].type == POMEGRANTE)
            {
                fruit[i].health -= 1;
                if (fruit[i].health == 0)
                {
                    data.add_score(2, current_combo.multiplier);
                    fruit[i].active = false;
                    fruit_spawner.add_fruit_slice(slice, fruit_spawner.spawn_fruit_slice(fruit[i]));
                    fruit[i].active = false;
                    remove_at(fruit, i);
                }
                current_combo.register_hit();
                fruit_hit = true;
                return true;
            }

            data.add_score(1, current_combo.multiplier);
            fruit_spawner.add_fruit_slice(slice, fruit_spawner.spawn_fruit_slice(fruit[i]));
            fruit[i].active = false;
            free_sprite(fruit[i].fruit_object);
            remove_at(fruit, i);
            current_combo.register_hit();
            fruit_hit = true;
            play_sound_effect("knife_slash.MP3");
            return true;
    }

    return false;
}

bool knife::line_circle_intersect(point_2d last_position, point_2d current_position, point_2d fruit_location, double radius)
{
    //line segment from last_position to current_position
    //fruit centered at fruit_location with radius
    //line segment can be written as P(t) = P0 + t(P1-P0), where P0 is the last_position and P1 is the current position and 0<=t<=1
    
    double dx = current_position.x- last_position.x; //direction vector
    double dy = current_position.y - last_position.y; //direction vector
    double fx = last_position.x-fruit_location.x;
    double fy= last_position.y-fruit_location.y;

    //x=fx+tdx
    //y=fy+tdy

    //for a point to lie on the circle: x^2+y^2=r^2, when we substitute the line equations, it gives:
    // (fx+tdx)^2 + (fy+tdy)^2 = r^2, after expansion it gives - (dx2+dy2)t^2+2(fxdx+fydy)t+(fx2+fy2−r2)=0
    //which is equivalent with at^2+bt+c=0

    double a = dx*dx + dy*dy;
    double b = 2.0*(fx*dx+fy*dy);
    double c = fx*fx+fy*fy-radius*radius;

    double discriminant = b*b-4.0*a*c;
    if(discriminant<0)
    {
        return false;
    }

    double sq = sqrt(float(discriminant));
    double t1 = (-b-sq)/(2.0*a);
    double t2 = (-b+sq)/(2.0*a);

    return (t1>=0.0 && t1<=1.0) || (t2>=0.0 && t2 <=1.0); //checks how far along the movement path the knife went
}





