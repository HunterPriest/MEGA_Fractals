#pragma once

#include <GLFW/glfw3.h>
#include <string.h>
#include <nlohmann/json.hpp>

namespace Core {

    int initalize();
    void beginFrame();
    void endFrame();
    void cleanUp();
    
    GLFWwindow* getWindow();
    void toggleFullscreen();
    bool WindowIsOpen();
    int getWindowedWidth();
    int getWindowedHeight();
    unsigned int getShader();
    float getDeltaTime();
    void setWindowSize(int width, int heigth);

    nlohmann::json getWindowConfig();
    void setWindowTitle(std::string title);

    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void errorCallback(int error_code, const char *description);
}