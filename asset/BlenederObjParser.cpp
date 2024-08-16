#include "BlenederObjParser.h"
#include "utility.h"

assets::BlenederObjParser::BlenederObjParser(const char* filePath):file_path(filePath)
{
}

assets::BlenederObjParser::~BlenederObjParser()
{
}

void assets::BlenederObjParser::parse_object()
{
    std::ifstream file(file_path);

    std::string str;
    while (std::getline(file, str))
    {
        std::vector<std::string> lineItems = assets::split(str, ' ');
        if(std::find(lineItems.begin(), lineItems.end(), "v") != lineItems.end())
        {
            vec3_t tmp;
            tmp.x = std::stof(lineItems[1]);
            tmp.y = std::stof(lineItems[2]);
            tmp.z = std::stof(lineItems[3]);

            vertices.push_back(tmp);
        }
        if(std::find(lineItems.begin(), lineItems.end(), "f") != lineItems.end())
        {
            face_t tmp;
            tmp.color = 0xFFFFFFFF;
            for (size_t i = 1; i < lineItems.size(); i++)
            {
                std::vector<std::string> faceParams = assets::split(lineItems[i], '/');
                if(i == 1)
                    tmp.a = std::stof(faceParams[0]);
                else if(i == 2)
                    tmp.b = std::stof(faceParams[0]);
                else if(i == 3)
                    tmp.c = std::stof(faceParams[0]);    
            }
            faces.push_back(tmp);
        }
    }
}

void assets::BlenederObjParser::print_faces()
{
    for(auto i : faces)
    {
        std::cout<< i.a << ',' << i.b << ',' << i.c << '\n';
    }
}

void assets::BlenederObjParser::print_vertices()
{
    for(auto i : vertices)
    {
        std::cout<< i.x << ',' << i.y << ',' << i.z << '\n';
    }
}
