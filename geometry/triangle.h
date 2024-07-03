#pragma once

#include "vector.h"
#include <iostream>
#include <array>

struct face_t
{
    float a;
    float b;
    float c;
};

struct triangle_t
{
    std::array<vec2_t,3> points;
};