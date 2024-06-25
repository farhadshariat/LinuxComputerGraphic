#include "vector.h"

void vec3_t::rotate_x(float angle)
{
    float y = this->y * cos(angle) - this->z * sin(angle);
    float z = this->y * sin(angle) + this->z * cos(angle);
    float x  = this->x;

    this->y  = y;
    this->z  = z;
    this->x  = x;

    //TODO:Check this weird behavior doesnt return same result compare to above code!!! 
    // this->y = this->y * cos(angle) - this->z * sin(angle);
    // this->z  = this->y * sin(angle) + this->z * cos(angle);
    // this->x  = this->x;
}

void vec3_t::rotate_y(float angle)
{
    float x = this->x * cos(angle) - this->z * sin(angle);
    float z = this->x * sin(angle) + this->z * cos(angle);
    float y = this->y;

    this->x  = x;
    this->z  = z;
    this->y  = y;

    //TODO:Check this weird behavior doesnt return same result compare to above code!!! 
    // this->x = this->x * cos(angle) - this->z * sin(angle);
    // this->z = this->x * sin(angle) + this->z * cos(angle);
    // this->y = this->y;
}

void vec3_t::rotate_z(float angle)
{
    float x = this->x * cos(angle) - this->y * sin(angle);
    float y = this->x * sin(angle) + this->y * cos(angle);
    float z  = this->z;

    this->x  = x;
    this->y  = y;
    this->z  = z;

    //TODO:Check this weird behavior doesnt return same result compare to above code!!! 
    // this->x = this->x * cos(angle) - this->y * sin(angle);
    // this->y = this->x * sin(angle) + this->y * cos(angle);
    // this->z  = this->z;
}