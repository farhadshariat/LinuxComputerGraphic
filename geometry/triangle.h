#pragma once

#include "vector.h"
#include <iostream>
#include <array>

class face_t
{
public:
    float a;
    float b;
    float c;
};

class triangle_t
{
public:
    std::array<vec2_t,3> points;
};