#include "matrix.h"
#include <chrono>

/// [0  1  2  3 ]
/// [4  5  6  7 ]
/// [8  9  10 11]
/// [12 13 14 15]

matrix4_t& matrix4_t::zero()
{
    data = {
            0,0,0,0,
            0,0,0,0,
            0,0,0,0,
            0,0,0,0
            };
    return *this;
}

matrix4_t& matrix4_t::identity()
{
    data = {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1
            };
    return *this;
}

void matrix4_t::make_scale(float sx, float sy, float sz)
{
    this->identity();
    this->data[0] = sx;
    this->data[5] = sy;
    this->data[10] = sz;
}

void matrix4_t::make_translation(float tx, float ty, float tz)
{
    this->identity();
    this->data[3] = tx;
    this->data[7] = ty;
    this->data[11] = tz;
}

void matrix4_t::make_rotation_x(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    this->identity();
    this->data[5] = c;
    this->data[9] = -s;
    this->data[6] = s;
    this->data[10] = c;

}
void matrix4_t::make_rotation_y(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    this->identity();
    this->data[0] = c;
    this->data[2] = s;
    this->data[8] = -s;
    this->data[10] = c;

}
void matrix4_t::make_rotation_z(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    this->identity();
    this->data[0] = c;
    this->data[1] = -s;
    this->data[4] = s;
    this->data[5] = c;
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

matrix4_t matrix4_t::mul_mat4(matrix4_t b)
{   
    //NOTE: most of the time has better performance!!!
    // matrix4_t temp;
    // temp = temp.zero();

    // for (size_t i = 0; i < 4; i++)
    // {
    //     for (size_t k = 0; k < 4; k++)
    //     {
    //         for (size_t j = 0; j < 4; j++)
    //         {
    //             temp.data[i * 4 + j] += this->data[i * 4 + k] * b.data[k * 4 + j];
    //         }
    //     }
    // }

    // return temp;

    matrix4_t temp;
    temp = temp.zero();
    
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            temp.data[i * 4 + j] = 
                  this->data[i * 4 + 0] * b.data[0 * i + j] 
                + this->data[i * 4 + 1]  * b.data[1 * 4 + j] 
                + this->data[i * 4 + 2] * b.data[2 * 4 + j] + this->data[i * 4 + 3] * b.data[3 * 4 + j];
        }
        
    }

    return temp;
}