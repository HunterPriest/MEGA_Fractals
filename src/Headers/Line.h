#pragma once

#include <Vector2.h>
#include <glad/glad.h>

namespace figure
{
    class Line
    {
        private:
        GLuint _VAO, _VBO;

        public:
            Line(engine::Vector2 point1, engine::Vector2 point2, float thickness);
            Line(Line &&);
            ~Line();
            void render();
    };
}