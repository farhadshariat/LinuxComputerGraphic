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
    {.a = 1, .b = 2, .c = 3, .color = 0xFFFFFFFF},
    {.a = 1, .b = 3, .c = 4, .color = 0xFFFFFFFF},

    //right
    {.a = 4, .b = 3, .c = 5, .color = 0xFFFFFFFF},
    {.a = 4, .b = 5, .c = 6, .color = 0xFFFFFFFF},

    //back
    {.a = 6, .b = 5, .c = 7, .color = 0xFFFFFFFF},
    {.a = 6, .b = 7, .c = 8, .color = 0xFFFFFFFF},

    //left
    {.a = 8, .b = 7, .c = 2, .color = 0xFFFFFFFF},
    {.a = 8, .b = 2, .c = 1, .color = 0xFFFFFFFF},

    //top
    {.a = 2, .b = 7, .c = 5, .color = 0xFFFFFFFF},
    {.a = 2, .b = 5, .c = 3, .color = 0xFFFFFFFF},

    //botton
    {.a = 6, .b = 8, .c = 1, .color = 0xFFFFFFFF},
    {.a = 6, .b = 1, .c = 4, .color = 0xFFFFFFFF},
};

void Mesh::load_cube_mesh_data()
{
    //call copy constructor
    //this->vertices = cube_vertices;
    //this->faces = cube_faces;

    assets::BlenederObjParser parser = assets::BlenederObjParser("../BlenderObject/jet2.obj");
    parser.parse_object();

    this->vertices = std::move(parser.vertices);
    this->faces = std::move(parser.faces);

    // this->vertices = std::move(cube_vertices);
    // this->faces = std::move(cube_faces);
}