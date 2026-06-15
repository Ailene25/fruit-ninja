#ifndef FRUIT_DATA_H
#define FRUIT_DATA_H
#include "splashkit.h"
#include <fstream>
#include <string>
#include "enums.h"

struct fruit_data
{
    fruit_type type;
    int health; // pomegrantes requires longer hits to destroy
    sprite fruit_object;
    bool active;
    bool shot;
    double radius;
    double y_velocity;
    double spawn_position;

    point_2d p0, p1, p2;
    double t;
    double t_speed;
};

struct slice_data
{
    fruit_slices slice_type;
    double y_velocity;
    double x_velocity_left;
    double x_velocity_right;
    double rotation_speed;
    sprite left_slice;
    sprite right_slice;
    bool active;
};

#endif