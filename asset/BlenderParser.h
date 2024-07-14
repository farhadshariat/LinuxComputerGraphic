#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "../geometry/vector.h"
#include "../geometry/triangle.h"

namespace assets
{
    class BlenderParser
    {
    private:
        std::vector<vec3_t> parsedVertices;
        std::vector<face_t> parsedFaces;
    public:
        BlenderParser();
        ~BlenderParser();

        void ParseObj(const char* filePath);
    };



}