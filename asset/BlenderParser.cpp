#include "BlenderParser.h"

assets::BlenderParser::BlenderParser()
{
}

assets::BlenderParser::~BlenderParser()
{
}

void assets::BlenderParser::ParseObj(const char* filePath)
{
    std::string buffer;
    std::ifstream in(filePath, std::ios_base::binary | std::ios_base::ate);
    in.exceptions(std::ios_base::badbit | std::ios_base::failbit | std::ios_base::eofbit);
    buffer.resize(in.tellg());
    in.seekg(0, std::ios_base::beg);
    in.read(&buffer[0], buffer.size());
    std::cout << buffer;
}
