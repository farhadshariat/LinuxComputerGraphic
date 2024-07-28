#pragma once

#include <iostream>
#include <vector>
#include "vector.h"

class matrix4_t
{
public:
    void identity();
    void make_scale(float sx, float sy, float sz);
    vec4_t mul_vec4(vec4_t v);


    std::vector<float> data;
};
