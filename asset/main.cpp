#include <fstream> 
#include <iostream> 
#include <string> 
#include <filesystem> 
#include <vector> 
#include <algorithm>
#include "triangle.h" 
  
class BlenederParserObj
{
private:
    
public:
    BlenederParserObj();
    ~BlenederParserObj();

    void PrintFaces()
    {
        for(auto i : faces)
        {
            std::cout<< i.a << ',' << i.b << ',' << i.c << '\n';
        }
    }

    void PrintVertices()
    {
        for(auto i : vertices)
        {
            std::cout<< i.x << ',' << i.y << ',' << i.z << '\n';
        }
    }

    std::vector<face_t> faces;
    std::vector<vec3_t> vertices;
};

BlenederParserObj::BlenederParserObj(/* args */)
{
}

BlenederParserObj::~BlenederParserObj()
{
}


std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}


int main() 
{ 
    std::cout << std::filesystem::current_path().string() << std::endl;

    std::ifstream file("../cube.txt");

    if(file)
    {
        std::cout<< "opened" <<'\n';
    }
    std::string str;
    BlenederParserObj parser = BlenederParserObj();
    while (std::getline(file, str))
    {
        std::vector<std::string> lineItems = split(str, ' ');
        if(std::find(lineItems.begin(), lineItems.end(), "v") != lineItems.end())
        {
            vec3_t tmp = {std::stof(lineItems[1]) , std::stof(lineItems[2]), std::stof(lineItems[3])};

            parser.vertices.push_back(tmp);
        }
        if(std::find(lineItems.begin(), lineItems.end(), "f") != lineItems.end())
        {
            face_t tmp;
            for (size_t i = 1; i < lineItems.size(); i++)
            {
                std::vector<std::string> faceParams = split(lineItems[i], '/');
                if(i == 1)
                    tmp.a = std::stof(faceParams[0]);
                if(i == 2)
                    tmp.a = std::stof(faceParams[0]);
                if(i == 3)
                    tmp.a = std::stof(faceParams[0]);    
            }
            parser.faces.push_back(tmp);
        }
    }

    parser.PrintFaces();
}