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
            
            unsigned int *_shaderId;
            glm::vec2 scale;
            float _dir, _speedRotation, _angle, _length, *_vbo = 0;
            int _iterations, _amountTrees, _amountBranchs, _sizeVbo = 0, _amountElements;
            bool _isRotate;
            engine::Vector2 _startPoint;
            figure::Line _line;

            void createTree(engine::Vector2 vector, float dir, float length, int iterations);
            void resize();
            void addIteration(int iterations, float length);

        public:
            PythagorasTree(int iterations, float angle, int amountBranchs, float speedRotation, int amountTrees, float length, float xPos, unsigned int* shaderId);
            ~PythagorasTree();
            void update(float deltaTime) override; 
            void withdrawUI() override;
            void setScale(glm::vec2 newScale) override;
            void updateAmountTrees();
    };
}