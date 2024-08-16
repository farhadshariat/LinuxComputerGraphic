#pragma once

#include "vector.h"
#include <stdint.h>

class light_t
{
public:
    vec3_t direction;

    uint32_t apply_intensity(uint32_t original_color, float percentage_factor);
};

extern light_t light;