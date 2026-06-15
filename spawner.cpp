#include "spawner.h"


spawner::spawner()
{
    current_frame = 0;
    spawn_interval = 2.0;
    difficulty = 1;
}

void spawner::reset()
{
    current_frame = 0;
    spawn_interval = 2.0;
    difficulty = 1;
    next_pomegrante = 10;
}

void spawner::update_difficulty(game_data &data)
{
    difficulty = 1+(data.score/20);

    spawn_interval = 120 - (difficulty*10);

    if(spawn_interval<30)
    {
        spawn_interval = 30;
    }
}

fruit_data spawner::spawn_fruit(loader &load_sound, levels current_level)
{
    fruit_data new_fruit;
    new_fruit.type = static_cast<fruit_type>(rnd(MAX_FRUIT));
    new_fruit.health = NORMAL_HEALTH;
    new_fruit.spawn_position = rnd(300,SCREEN_WIDTH-300);
    new_fruit.p0 = point_at(rnd(100,700),SCREEN_HEIGHT);
    new_fruit.p2 = point_at(rnd(700,SCREEN_WIDTH-300),SCREEN_HEIGHT);
    double midpoint = (new_fruit.p0.x+new_fruit.p2.x)/2.0;
    new_fruit.p1 = point_at(midpoint,rnd(200)-500);
    new_fruit.t = 0.0;
    new_fruit.t_speed = 0.005 + rnd() * 0.001;
    new_fruit.y_velocity = -8.0;
    new_fruit.fruit_object = create_sprite(bitmap_named(fruit_name(new_fruit.type)));
    if(current_level==FIRST || current_level ==SECOND)
    {
        sprite_set_x(new_fruit.fruit_object, new_fruit.spawn_position);
        sprite_set_y(new_fruit.fruit_object, SCREEN_HEIGHT);
    }
    else
    {
        sprite_set_x(new_fruit.fruit_object, new_fruit.p0.x);
        sprite_set_y(new_fruit.fruit_object, new_fruit.p0.y);
    }
    new_fruit.active = true;
    new_fruit.shot = false;

    switch (new_fruit.type)
    {
    case APPLE:
        new_fruit.radius=43.5;
        break;
    case WATERMELON:
        new_fruit.radius=80.5;
        break;
    case BANANA:
        new_fruit.radius=62;
        break;
    case KIWI:
        new_fruit.radius=39;
        break;
    case LEMON:
        new_fruit.radius=35.5;
        break;
    case PEACH:
        new_fruit.radius=41.5;
        break;
    case PINEAPPLE:
        new_fruit.radius=62;
        break;
    case BOMB:
        new_fruit.radius=75;
        break;
    default:
        new_fruit.radius=50;
        break;
    }

    if(new_fruit.type==BOMB)
    {
        play_sound_effect("bomb", -1);
    }
    else
    {
        play_sound_effect("fruit spawn");
    }

    return new_fruit;
}

fruit_data spawner::spawn_pomegrante(levels current_level, loader &load_sound)
{
    fruit_data new_fruit;
    new_fruit.type = POMEGRANTE;
    new_fruit.health = POMEGRANTE_HEALTH;
    new_fruit.spawn_position = rnd(300,SCREEN_WIDTH-300);
    new_fruit.p0 = point_at(rnd(100,700),SCREEN_HEIGHT);
    new_fruit.p2 = point_at(rnd(700,SCREEN_WIDTH-300),SCREEN_HEIGHT);
    double midpoint = (new_fruit.p0.x+new_fruit.p2.x)/2.0;
    new_fruit.p1 = point_at(midpoint,rnd(200)-500);
    new_fruit.t = 0.0;
    new_fruit.t_speed = 0.005 + rnd() * 0.001;
    new_fruit.y_velocity = -8.0;
    new_fruit.fruit_object = create_sprite(bitmap_named(fruit_name(new_fruit.type)));
    if(current_level==FIRST || current_level ==SECOND)
    {
        sprite_set_x(new_fruit.fruit_object, new_fruit.spawn_position);
        sprite_set_y(new_fruit.fruit_object, SCREEN_HEIGHT);
    }
    else
    {
        sprite_set_x(new_fruit.fruit_object, new_fruit.p0.x);
        sprite_set_y(new_fruit.fruit_object, new_fruit.p0.y);
    }
    new_fruit.active = true;
    new_fruit.shot = false;
    new_fruit.radius=44;
    play_sound_effect("fruit spawn");

    return new_fruit;
}

void spawner::update(dynamic_array<fruit_data> &fruit, game_data &data, loader &load_sound, levels current_level)
{
    update_difficulty(data);

    current_frame+=1.0;

    if(current_frame>=spawn_interval)
    {
        int fruits_on_screen = 0;
        for (int i = 0; i < length(fruit); i++)
        {
            if(fruit[i].active)
            {
                fruits_on_screen++;
            }
        }

        if(fruits_on_screen<5)
        {
            int number_of_fruits_to_spawn = 1 + rnd(difficulty);
            int available_to_spawn = 5-fruits_on_screen;

            if(number_of_fruits_to_spawn>5)
            {
            number_of_fruits_to_spawn=5;
            }

            if(number_of_fruits_to_spawn>available_to_spawn)
            {
                number_of_fruits_to_spawn=available_to_spawn;
            }

            for (int i = 0; i < number_of_fruits_to_spawn; i++)
            {
                if(data.score>=next_pomegrante)
                {
                    add_fruit(fruit, spawn_pomegrante(current_level, load_sound));
                    next_pomegrante+=10;
                }
                else
                {
                    add_fruit(fruit, spawn_fruit(load_sound, current_level));
                }
            }
        }
        current_frame = 0;
    }
}

slice_data spawner::spawn_fruit_slice(const fruit_data &fruit)
{
    slice_data new_slice;
    switch (fruit.type)
    {
    case APPLE:
        new_slice.slice_type = APPLE_SLICE;
        new_slice.left_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        new_slice.right_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        sprite_set_x(new_slice.left_slice, sprite_x(fruit.fruit_object) - 50); // offset left
        sprite_set_y(new_slice.left_slice, sprite_y(fruit.fruit_object));
        sprite_set_x(new_slice.right_slice, sprite_x(fruit.fruit_object) + 50); // offset right
        sprite_set_y(new_slice.right_slice, sprite_y(fruit.fruit_object));
        sprite_set_rotation(new_slice.left_slice, 45);
        sprite_set_rotation(new_slice.left_slice, -45);
        new_slice.x_velocity_left = -0.3;
        new_slice.x_velocity_right = 0.3;
        new_slice.y_velocity = -0.2;
        new_slice.rotation_speed = 5;
        new_slice.active = true;

        return new_slice;

        break;
    case BANANA:
        new_slice.slice_type = BANANA_SLICE;
        new_slice.left_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        new_slice.right_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        sprite_set_x(new_slice.left_slice, sprite_x(fruit.fruit_object) - 50); // offset left
        sprite_set_y(new_slice.left_slice, sprite_y(fruit.fruit_object));
        sprite_set_x(new_slice.right_slice, sprite_x(fruit.fruit_object) + 50); // offset right
        sprite_set_y(new_slice.right_slice, sprite_y(fruit.fruit_object));
        sprite_set_rotation(new_slice.left_slice, 45);
        sprite_set_rotation(new_slice.left_slice, -45);
        new_slice.x_velocity_left = -0.3;
        new_slice.x_velocity_right = 0.3;
        new_slice.y_velocity = -0.2;
        new_slice.rotation_speed = 5;
        new_slice.active = true;

        return new_slice;
        break;
    case KIWI:
        new_slice.slice_type = KIWI_SLICE;
        new_slice.left_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        new_slice.right_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        break;
    case LEMON:
        new_slice.slice_type = LEMON_SLICE;
        new_slice.left_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        new_slice.right_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        break;
    case PEACH:
        new_slice.slice_type = PEACH_SLICE;
        new_slice.left_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        new_slice.right_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        break;
    case PINEAPPLE:
        new_slice.slice_type = PINEAPPLE_SLICE;
        new_slice.left_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        new_slice.right_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        sprite_set_x(new_slice.left_slice, sprite_x(fruit.fruit_object) - 60); // offset left
        sprite_set_y(new_slice.left_slice, sprite_y(fruit.fruit_object));
        sprite_set_x(new_slice.right_slice, sprite_x(fruit.fruit_object) + 60); // offset right
        sprite_set_y(new_slice.right_slice, sprite_y(fruit.fruit_object));
        sprite_set_rotation(new_slice.left_slice, 45);
        sprite_set_rotation(new_slice.left_slice, -45);
        new_slice.x_velocity_left = -0.3;
        new_slice.x_velocity_right = 0.3;
        new_slice.y_velocity = -0.2;
        new_slice.rotation_speed = 1.5;
        new_slice.active = true;

        return new_slice;

        break;
    case POMEGRANTE:
        new_slice.slice_type = POMEGRANTE_SLICE;
        new_slice.left_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        new_slice.right_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        break;
    case WATERMELON:
        new_slice.slice_type = WATERMELON_SLICE;
        new_slice.left_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        new_slice.right_slice = create_sprite(bitmap_named(fruit_slice_name(fruit.type)));
        sprite_set_x(new_slice.left_slice, sprite_x(fruit.fruit_object) - 80); // offset left
        sprite_set_y(new_slice.left_slice, sprite_y(fruit.fruit_object));
        sprite_set_x(new_slice.right_slice, sprite_x(fruit.fruit_object) + 80); // offset right
        sprite_set_y(new_slice.right_slice, sprite_y(fruit.fruit_object));
        sprite_set_rotation(new_slice.left_slice, 45);
        sprite_set_rotation(new_slice.left_slice, -45);
        new_slice.x_velocity_left = -0.3;
        new_slice.x_velocity_right = 0.3;
        new_slice.y_velocity = -0.2;
        new_slice.rotation_speed = 1.5;
        new_slice.active = true;

        return new_slice;
        break;
    case BOMB:
        return new_slice;
    }

    sprite_set_x(new_slice.left_slice, sprite_x(fruit.fruit_object) - 40); // offset left
    sprite_set_y(new_slice.left_slice, sprite_y(fruit.fruit_object));
    sprite_set_x(new_slice.right_slice, sprite_x(fruit.fruit_object) + 40); // offset right
    sprite_set_y(new_slice.right_slice, sprite_y(fruit.fruit_object));
    sprite_set_rotation(new_slice.left_slice, 45);
    sprite_set_rotation(new_slice.left_slice, -45);
    new_slice.x_velocity_left = -0.3;
    new_slice.x_velocity_right = 0.3;
    new_slice.y_velocity = -0.2;
    new_slice.rotation_speed = 1.5;
    new_slice.active = true;

    return new_slice;
}

void spawner::add_fruit(dynamic_array<fruit_data> &fruit, fruit_data new_fruit)
{
    add(fruit, new_fruit);
}

void spawner::add_fruit_slice(dynamic_array<slice_data> &slice, slice_data new_slice)
{
    add(slice, new_slice);
}