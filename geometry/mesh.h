#pragma once

#include <vector>
#include "vector.h"
#include "triangle.h"
 
extern std::vector<vec3_t> cube_vertices;
extern std::vector<face_t> cube_faces;

class Mesh
{
private:
    
public:
    Mesh() = default;

    void load_cube_mesh_data();

    std::vector<vec3_t> vertices;
    std::vector<face_t> faces;
    vec3_t rotataion {0, 0, 0};
    vec3_t scale {1.0, 1.0, 1.0};
    vec3_t translation {0, 0, 0};
};