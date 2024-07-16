#include "vector.h"

float vec2_t::length()
{
    return sqrt(x*x + y*y);
}

void vec2_t::normalize()
{
    float x = this->x / length();
    float y = this->y / length();
    this->x = x;
    this->y = y;
}

vec2_t vec2_t::add(vec2_t b)
{
    vec2_t retVal;
    retVal.x = this->x + b.x;
    retVal.y = this->y + b.y;
    return retVal;
}

vec2_t vec2_t::sub(vec2_t b)
{
    vec2_t retVal;
    retVal.x = this->x - b.x;
    retVal.y = this->y - b.y;
    return retVal;
}

void vec2_t::mul(int factor)
{
    x = x * factor;
    y = y * factor;
}

void vec2_t::div(int factor)
{   
    if(factor != 0)
    {
        x = x / factor;
        y = y / factor;
    }
}

vec2_t vec2_t::operator+(const vec2_t& b)
{
    vec2_t retVal;
    retVal.x = x + b.x;
    retVal.y = y + b.y;
    return retVal;
}

vec2_t vec2_t::operator-(const vec2_t& b)
{
    vec2_t retVal;
    retVal.x = x - b.x;
    retVal.y = y - b.y;
    return retVal;
}

float vec2_t::operator*(const vec2_t& b)
{
    return x * b.x + y * b.y;
}

float vec3_t::length()
{
    return sqrt(x*x + y*y + z*z);
}

void vec3_t::normalize()
{
    float x = this->x / length();
    float y = this->y / length();
    float z = this->z / length();
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3_t vec3_t::add(vec3_t b)
{
    vec3_t retVal;
    retVal.x = this->x - b.x;
    retVal.y = this->y - b.y;
    retVal.z = this->z - b.z;
    return retVal;
}

vec3_t vec3_t::sub(vec3_t b)
{
    vec3_t retVal;
    retVal.x = this->x + b.x;
    retVal.y = this->y + b.y;
    retVal.z = this->z + b.z;
    return retVal;
}

void vec3_t::mul(int factor)
{
    x = x * factor;
    y = y * factor;
    z = z * factor;
}

void vec3_t::div(int factor)
{
    if(factor != 0)
    {
        x = x / factor;
        y = y / factor;
        z = z / factor;
    }
}

vec3_t vec3_t::cross(const vec3_t& b)
{
    vec3_t retVal;
    retVal.x = this->y * b.z - this->z * b.y;
    retVal.y = this->z * b.x - this->x * b.z;
    retVal.z = this->x * b.y - this->y * b.x;
    return retVal;
}

vec3_t vec3_t::operator+(const vec3_t& b)
{
    vec3_t retVal;
    retVal.x = x + b.x;
    retVal.y = y + b.y;
    retVal.z = z + b.z;
    return retVal;
}

vec3_t vec3_t::operator-(const vec3_t& b)
{
    vec3_t retVal;
    retVal.x = x - b.x;
    retVal.y = y - b.y;
    retVal.z = z - b.z;
    return retVal;
}

float vec3_t::operator*(const vec3_t& b)
{
    return x * b.x + y * b.y + z * b.z;
}

void vec3_t::rotate_x(float angle)
{
    float y = this->y * cos(angle) - this->z * sin(angle);
    float z = this->y * sin(angle) + this->z * cos(angle);

    this->y  = y;
    this->z  = z;
}

void vec3_t::rotate_y(float angle)
{
    float x = this->x * cos(angle) - this->z * sin(angle);
    float z = this->x * sin(angle) + this->z * cos(angle);

    this->x  = x;
    this->z  = z;
}

void vec3_t::rotate_z(float angle)
{
    float x = this->x * cos(angle) - this->y * sin(angle);
    float y = this->x * sin(angle) + this->y * cos(angle);

    this->x  = x;
    this->y  = y;
}