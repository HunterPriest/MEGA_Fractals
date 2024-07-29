#pragma once

#include <GLFW/glfw3.h>

namespace gui
{
    int initialize(GLFWwindow* window);
    void beginFrame();
    void endFrame();
    void cleanUp();
}