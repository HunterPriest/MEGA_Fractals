#include "src/Headers/Window.h"
#include "src/Headers/Graphics.h"
#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include "src/Headers/Vector2.h"
#include <PythagorasTree.h>


int main()
{
    engine::Window window;
    if(window.createWindow() == -1)
    {
        return -1;
    }
    engine::Graphics graphics;
    if(graphics.Init(window.GetWindow()) == -1)
    {
        return -1;
    }

    figure::PythagorasTree tree(0, 90);
    // engine::Vector2 vec(0.0, -1.0);

    // engine::Vector2 nextVector(0.0f, 0.0f);

    // figure::Line line(vec, nextVector, 0.01f);

    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        tree.render();
        // line.render();

        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }
    glDeleteProgram(graphics.GetShader());  

    glfwTerminate();
    return 0;
}