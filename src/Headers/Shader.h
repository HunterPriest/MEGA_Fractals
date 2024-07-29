#pragma once

#include <string>
#include <filesystem>

namespace engine
{
    static std::string readFileShader(std::filesystem::path pathShader);
    static unsigned int compileShader(unsigned int shaderType, std::string& src);
    static unsigned int createShader(std::string& vertex, std::string& fragment);

    int loadShader();
    unsigned int getShader();
}