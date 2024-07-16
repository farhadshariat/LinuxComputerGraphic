#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "../geometry/vector.h"
#include "../geometry/triangle.h"

namespace assets
{
    class BlenederObjParser
    {
    private:
        
    public:
        BlenederObjParser(const char* filePath);
        ~BlenederObjParser();

        void print_faces();
        void print_vertices();

        void parse_object();

        const char* file_path;
        std::vector<face_t> faces;
        std::vector<vec3_t> vertices;
    };
}