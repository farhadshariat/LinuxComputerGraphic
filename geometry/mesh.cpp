#include "mesh.h"
#include "triangle.h"
#include "../asset/BlenederObjParser.h"

std::vector<vec3_t> cube_vertices = {
    {.x = -1, .y = -1, .z = -1},
    {.x = -1, .y =  1, .z = -1},
    {.x =  1, .y =  1, .z = -1},
    {.x =  1, .y = -1, .z = -1},
    {.x =  1, .y =  1, .z =  1},
    {.x =  1, .y = -1, .z =  1},
    {.x = -1, .y =  1, .z =  1},
    {.x = -1, .y = -1, .z =  1},
};

std::vector<face_t> cube_faces=
{
    //front
    {.a = 1, .b = 2, .c = 3},
    {.a = 1, .b = 3, .c = 4},

    //right
    {.a = 4, .b = 3, .c = 5},
    {.a = 4, .b = 5, .c = 6},

    //back
    {.a = 6, .b = 5, .c = 7},
    {.a = 6, .b = 7, .c = 8},

    //left
    {.a = 8, .b = 7, .c = 2},
    {.a = 8, .b = 2, .c = 1},

    //top
    {.a = 2, .b = 7, .c = 5},
    {.a = 2, .b = 5, .c = 3},

    //botton
    {.a = 6, .b = 8, .c = 1},
    {.a = 6, .b = 1, .c = 4},
};

void Mesh::load_cube_mesh_data()
{
    //call copy constructor
    // this->vertices = cube_vertices;
    // this->faces = cube_faces;

    assets::BlenederObjParser parser = assets::BlenederObjParser("../BlenderObject/cube.txt");
    parser.parse_object();

    this->vertices = std::move(parser.vertices);
    this->faces = std::move(parser.faces);
}