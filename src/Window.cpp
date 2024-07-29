#include <Window.h>
#include <nlohmann/json.hpp>
#include <glad/glad.h>
#include <iostream>
#include <fstream>

void engine::Window::errorCallback(int error_code, const char *description)
{
    std::cout << "GLFW Error: " << description << " Error code: " << error_code << std::endl;
}

int engine::Window::createWindow()
{
    std::ifstream f("Configs/Window.json");
    winConf = nlohmann::json::parse(f);

    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
    {
        std::cerr << "glfw isnt init" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 1);

    title = winConf["name"];
    _window = glfwCreateWindow((int)winConf["width"], (int)winConf["height"], title.c_str(), NULL, NULL);

    if (!_window)
    {
        glfwTerminate();
        std::cerr << "window is null" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(_window);

    return 1;
}

GLFWwindow* engine::Window::getWindow()
{
    return _window;
}

nlohmann::json engine::Window::getConfig()
{
    return winConf;
}