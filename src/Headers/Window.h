#pragma once

#include "../include/GLFW/glfw3.h"
#include <string>
#include <nlohmann/json.hpp>

namespace engine
{
    class Window
    {
        private:
        GLFWwindow *_window;
        nlohmann::json winConf;
        static void errorCallback(int error_code, const char *description);

        public:
        std::string title;
        
        int createWindow();
        GLFWwindow* getWindow();
        nlohmann::json getConfig();
    };
}