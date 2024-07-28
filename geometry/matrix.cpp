#include "matrix.h"

void matrix4_t::identity()
{
    data = {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1
            };
}

void matrix4_t::make_scale(float sx, float sy, float sz)
{
    this->identity();
    this->data[0] = sx;
    this->data[5] = sy;
    this->data[10] = sz;
}

vec4_t matrix4_t::mul_vec4(vec4_t v)
{
    float x = this->data[0] * v.x + this->data[1] * v.y + this->data[2] * v.z + this->data[3] * v.w;
    float y = this->data[4] * v.x + this->data[5] * v.y + this->data[6] * v.z + this->data[7] * v.w;
    float z = this->data[8] * v.x + this->data[9] * v.y + this->data[10] * v.z + this->data[11] * v.w;
    float w = this->data[12] * v.x + this->data[13] * v.y + this->data[14] * v.z + this->data[15] * v.w;

    vec4_t tmp = {.x=x, .y=y, .z=z, .w=w};
    return tmp;
}