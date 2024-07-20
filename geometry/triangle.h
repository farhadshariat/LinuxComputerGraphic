#pragma once

#include "vector.h"
#include <iostream>
#include <array>
#include <cstdint>

class face_t
{
public:
    float a;
    float b;
    float c;
    uint32_t color;
};

class triangle_t
{
public:
    std::array<vec2_t,3> points;
    uint32_t color;
    float avg_depth;
};