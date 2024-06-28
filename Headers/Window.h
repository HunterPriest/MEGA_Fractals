#pragma once

#include "../include/GLFW/glfw3.h"

namespace engine
{
    class Window
    {
        private:
        GLFWwindow *_window;
        static void errorCallback(int error_code, const char *description);

        public:
        int createWindow();
        GLFWwindow* GetWindow();
    };
}