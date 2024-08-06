#pragma once

#define _USE_MATH_DEFINES

#include <Fractal.h>
#include <Vector2.h>
#include <Line.h>

#define RADIAN M_PI / 180

namespace figure
{
    class DragonsCurve : public Fractal
    {
        private:
            float _length;
            figure::Line _line;

            void drawCurve(engine::Vector2 startPoint, float length, float angle, int iterations);
            void calculateAmountElements(int interations) override;

        public:
            DragonsCurve(int iterations, float length, float xPos, unsigned int* shaderId);
            void update(float deltaTime) override; 
            void withdrawUI() override;
    };
}