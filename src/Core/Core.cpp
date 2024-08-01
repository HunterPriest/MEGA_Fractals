#include <Core.h>

#include <Json.h>
#include <nlohmann/json.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <Shader.h>
#include <time.h>
#include <string>
#include <Gui.h>

namespace Core 
{
    GLFWwindow* window;
    nlohmann::json windowConfig;
    int frameCount;
    float deltaTime;
    double previousTime;
    clock_t start, end;


    int initalize()
    {
        windowConfig = tools::loadJson("Configs/Window.json");  

        if (!glfwInit())
        {
            std::cerr << "glfw isnt init" << std::endl;
            return -1;
        }

        glfwSetErrorCallback(errorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        std::string title = windowConfig["name"];
        window = glfwCreateWindow((int)windowConfig["width"], (int)windowConfig["height"], title.c_str(), NULL, NULL);

        if (!window)
        {
            glfwTerminate();
            std::cerr << "window is null" << std::endl;
            return -1;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "error" << std::endl;
            return -1;
        }
        glEnable(GL_MULTISAMPLE);

        if(engine::loadShader() == -1)
        {
            return -1;
        }
        
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        gui::initialize(window);

        return 1;
    }

    void beginFrame()
    {
        start = clock();
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        gui::beginFrame();
    }

    void endFrame()
    {
        gui::endFrame();

        glfwSwapBuffers(window);
        end = clock();

        double currentTime = glfwGetTime();

        frameCount++;
        if ( currentTime - previousTime >= 1.0 )
        {
            std::string fps = (std::string)windowConfig["name"] + " fps: " + std::to_string(frameCount);
            setWindowTitle(fps);

            frameCount = 0;
            previousTime = currentTime;
        }
        deltaTime = ((float) end - start) / CLOCKS_PER_SEC;
    }

    void cleanUp()
    {
        glDeleteProgram(engine::getShader());  

        glfwTerminate();

        gui::cleanUp();
    }

    unsigned int getShader()
    {
        return engine::getShader();
    }
    
    GLFWwindow* getWindow()
    {
        return window;
    }
    
    bool WindowIsOpen()
    {
        return glfwWindowShouldClose(window);
    }

    nlohmann::json getWindowConfig()
    {
        return windowConfig;
    }

    float getDeltaTime()
    {
        return deltaTime;
    }

    void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void errorCallback(int error_code, const char *description)
    {
        std::cout << description << "error code: " << error_code << std::endl;
    }

    void setWindowTitle(std::string title)
    {
        glfwSetWindowTitle(window, title.c_str());
    }
    
    void setWindowSize(int width, int heigth)
    {
        glfwSetWindowSize(window, width, heigth);
    }

    int getWindowedWidth()
    {
        int width;
        glfwGetWindowSize(window, &width, nullptr);
        return width;
    }

    int getWindowedHeight()
    {
        int height;
        glfwGetWindowSize(window, nullptr, &height);
        return height;
    }
}