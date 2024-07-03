#include "vector.h"

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