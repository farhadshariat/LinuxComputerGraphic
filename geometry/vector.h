#pragma once

#include <math.h>

struct vec2_t
{
    float x;
    float y;
};

struct vec3_t
{
    float x;
    float y;
    float z;

    void rotate_x(float angle);
    void rotate_y(float angle);
    void rotate_z(float angle);
};

vec3_t rotate_xx(vec3_t v, float angle);

vec3_t rotate_yy(vec3_t v, float angle);

vec3_t rotate_zz(vec3_t v, float angle);