#pragma once

#include <math.h>

class vec2_t
{
public:
    float x;
    float y;

    float length();
    void normalize();
    vec2_t add(vec2_t b);
    vec2_t sub(vec2_t b);
    void mul(int factor);
    void div(int factor = 1);
    vec2_t cross(vec2_t a, vec2_t b);

    vec2_t operator+(const vec2_t& b);
    vec2_t operator-(const vec2_t& b);
    float  operator*(const vec2_t& b);
};

class vec3_t
{
public:
    float x;
    float y;
    float z;

    float length();
    void normalize();
    vec3_t add(vec3_t b);
    vec3_t sub(vec3_t b);
    void mul(int factor);
    void div(int factor = 1);
    vec3_t cross(const vec3_t& b);

    vec3_t operator+(const vec3_t& b);
    vec3_t operator-(const vec3_t& b);
    float  operator*(const vec3_t& b);

    void rotate_x(float angle);
    void rotate_y(float angle);
    void rotate_z(float angle);
};