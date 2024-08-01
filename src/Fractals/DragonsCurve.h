#pragma once

#define _USE_MATH_DEFINES

#include <Fractal.h>
#include <vector>
#include <math.h>
#include <Vector2.h>
#include <glm/vec2.hpp>

#define RADIAN M_PI / 180

namespace figure
{
    class DragonsCurve : public Fractal
    {
        private:
            std::vector<engine::Vector2> _points;
            unsigned int *_shaderId;
            glm::vec2 scale;
            float _length;
            int _iterations, *VBO;
            engine::Vector2 startPoint;

            void drawCurve(engine::Vector2 startPoint, float length, float angle, int iterations);

        public:
            DragonsCurve(int iterations, float length, float xPos, unsigned int* shaderId);
            void update(float deltaTime) override; 
            void withdrawUI() override;
    };
}