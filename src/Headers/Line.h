#pragma once

#include <Vector2.h>
#include <glad/glad.h>
#include <vector>

namespace figure
{
    class Line
    {
        private:
        GLuint _VAO, _VBO;
        int _size;
        float _thickness; 

        public:
            Line(float thickness = 0.1f);
            void setVerticles(float verticles[], int sizeVerticles);
            ~Line();
            void render();
    };
}