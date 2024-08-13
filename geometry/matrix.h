#pragma once

#include <iostream>
#include <vector>
#include "vector.h"

class matrix4_t
{
public:
    matrix4_t& identity();
    matrix4_t& zero();
    void make_scale(float sx, float sy, float sz);
    void make_translation(float tx, float ty, float tz);
    void make_rotation_x(float angle);
    void make_rotation_y(float angle);
    void make_rotation_z(float angle);
    void make_perspective(float fov, float aspect, float znear,  float zfar);
    vec4_t mul_vec4(vec4_t v);
    matrix4_t mul_mat4(matrix4_t);
    vec4_t mul_vec4_project(vec4_t v);

    std::vector<float> data;
};