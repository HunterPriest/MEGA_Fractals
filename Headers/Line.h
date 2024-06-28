#pragma once

#include "Vector2.h"
#include "../include/glad/glad.h"

namespace figure
{
    class Line
    {
        private:
        GLint _VAO;

        public:
            void create(engine::Vector2 *point1, engine::Vector2 *point2, float thickness);
            void render();
    };
}