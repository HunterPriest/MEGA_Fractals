#pragma once

#include <glm/vec2.hpp>

namespace figure
{
    class Fractal
    {
        public:
            virtual void update(float deltaTime) = 0;
            virtual void withdrawUI() = 0;
            virtual void setScale(glm::vec2 newScale) = 0;
    };
}