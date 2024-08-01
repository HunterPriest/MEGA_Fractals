#pragma once

#define _USE_MATH_DEFINES

#include <Fractal.h>
#include <vector>
#include <Vector2.h>
#include <glm/vec2.hpp>
#include <Line.h>

#define RADIAN M_PI / 180

namespace figure
{
    class PythagorasTree : public Fractal
    {
        private: 
            float _dir, _speedRotation, _angle, _length;
            int _amountTrees, _amountBranchs;
            bool _isRotate;
            figure::Line _line;

            void createTree(engine::Vector2 vector, float dir, float length, int iterations);

        public:
            PythagorasTree(int iterations, float angle, int amountBranchs, float speedRotation, int amountTrees, float length, float xPos, unsigned int* shaderId);
            void update(float deltaTime) override; 
            void withdrawUI() override;
            void updateAmountTrees();
            void addIteration(int interations) override;
    };
}