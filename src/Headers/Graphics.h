#pragma once

#include "../include/GLFW/glfw3.h"
#include "../include/glad/glad.h"
#include <iostream>
#include <filesystem>

namespace engine
{
    class Graphics
    {
        private:
        GLFWwindow* _window;
        unsigned int _shader;


        std::string readFileShader(std::filesystem::path pathShader);
        unsigned int compileShader(unsigned int shaderType, std::string& src);
        unsigned int createShader(std::string& vertex, std::string& fragment);

        public:
        int Init(GLFWwindow* window);
        unsigned int GetShader();
    };
}