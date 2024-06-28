#pragma once

#define _USE_MATH_DEFINES

#include <Fractal.h>
#include <vector>
#include <Line.h>
#include <math.h>
#   include <Vector2.h>

#define RADIAN M_PI / 180

namespace figure
{
    class PythagorasTree : public Fractal
    {
        private:
            std::vector<Line> _lines;
            float _angle;

            void createTree(engine::Vector2 vector, float dir, float length, int iteration);
            void createLine(engine::Vector2 point1, engine::Vector2 point2);
            void clear();

        public:
           PythagorasTree(int iterations, float angle);
            void render() override; 
    };
}