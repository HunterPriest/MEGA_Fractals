#include <Shader.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <Json.h>

namespace engine
{
    unsigned int id;

    int loadShader()
    {
        nlohmann::json graphicsConf = tools::loadJson("Configs/Graphics.json");

        std::string vertex = readFileShader(graphicsConf["vertexPath"]);
        std::string fragment = readFileShader(graphicsConf["fragmentPath"]);

        id = createShader(vertex, fragment);
        glUseProgram(id);
        

        return 0;
    }

    static std::string readFileShader(std::filesystem::path pathShader)
    {
        std::ifstream in(pathShader, std::ios::in);
        const auto sz = std::filesystem::file_size(pathShader);
        std::string result(sz, '\0');
        in.read(result.data(), sz);

        return result;
    }

    static unsigned int compileShader(unsigned int shaderType, std::string& src)
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

    static unsigned int createShader(std::string& vertex, std::string& fragment)
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

    unsigned int getShader()
    {
        return id;
    }
}