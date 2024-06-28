#include "../Headers/Graphics.h"
#include "../include/GLFW/glfw3.h"
#include "../include/glad/glad.h"
#include <fstream>
#include <iostream>
#include "../include/nlohmann/json.hpp"

int engine::Graphics::Init(GLFWwindow* window)
{
    _window = window;
    nlohmann::json graphicsConf; 
    std::fstream f("Configs/Graphics.json");
    graphicsConf = nlohmann::json::parse(f);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "error" << std::endl;
        return -1;
    }

    glEnable(GL_MULTISAMPLE);

    std::string vertex = readFileShader(graphicsConf["vertexPath"]);
    std::string fragment = readFileShader(graphicsConf["fragmentPath"]);

    _shader = createShader(vertex, fragment);
    glUseProgram(_shader);
    

    return 0;
}

std::string engine::Graphics::readFileShader(std::filesystem::path pathShader)
{
    std::ifstream in(pathShader, std::ios::in);
    const auto sz = std::filesystem::file_size(pathShader);
    std::string result(sz, '\0');
    in.read(result.data(), sz);

    return result;
}

unsigned int engine::Graphics::compileShader(unsigned int shaderType, std::string& src)
{
    unsigned id = glCreateShader(shaderType);
    const char* raw = src.c_str();

    glShaderSource(id, 1, &raw, nullptr);
    glCompileShader(id);

    int  success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        

    if(!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog<< std::endl;
    }
    
    return id;
}

unsigned int engine::Graphics::createShader(std::string& vertex, std::string& fragment)
{
    unsigned vs = compileShader(GL_VERTEX_SHADER, vertex);
    unsigned fs = compileShader(GL_FRAGMENT_SHADER, fragment);

    unsigned program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);


    
    int  success;
    char infoLog[512];
    

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout<<infoLog<<std::endl;
    }


    glDeleteShader(vs);
    glDeleteShader(fs);

    

    return program;
}

unsigned int engine::Graphics::GetShader()
{
    return _shader;
}
