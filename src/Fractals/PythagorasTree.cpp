#include <PythagorasTree.h>
#include <Line.h>
#include <Vector2.h>
#include <math.h>
#include <iostream>
#include <imgui.h>

#define SIZE_INT sizeof(int)

int sizeEbo = 0;

figure::PythagorasTree::PythagorasTree(int iterations, float angle, int amountBranchs, 
float speedRotation, int amountTrees, float length, float xPos, unsigned int* shaderId)
{
    _length = length;
    _amountTrees = amountTrees;
    _amountBranchs = amountBranchs;
    this->iterations = iterations; 
    _speedRotation = speedRotation;
    _isRotate = true;
    _angle = angle;

    startPoint.x = xPos;

    if (amountTrees == 1)
    {
        _dir = 0;
        startPoint.y = -1.0f;
    }
    else
    {
        startPoint.y = 0.0f;
        _dir = 360 / amountTrees;
    }
    this->shaderId = shaderId;
    setScale(glm::vec2(1, 1));   
    resize(_amountTrees);
}

void figure::PythagorasTree::update(float deltaTime)
{   
    if(_isRotate)
    _angle += deltaTime * _speedRotation;


    for (int i = 1; i < _amountTrees + 1; i++)
    {
        createTree(startPoint, _dir * i, _length, iterations);
    }
    
    _line.setVerticles(VBO, sizeVBO);
    _line.render();

    sizeVBO = 0;
}

void figure::PythagorasTree::withdrawUI()
{   
    Fractal::withdrawUI();
    ImGui::DragFloat("Length", &_length, 0.05f, 0.0f, 1, "%.3f", ImGuiSliderFlags_None);
    ImGui::DragFloat("Speed rotation", &_speedRotation, 0.1f, 0.0f, 100.0f, "%.3f", ImGuiSliderFlags_None);
    if (ImGui::DragInt("Iteration", &iterations, 0.05f, 0, 10, "%d", ImGuiSliderFlags_None))
    {
        resize(_amountTrees);
    }
    if(ImGui::DragInt("Amount tranchs", &_amountBranchs, 0.1f, 1, 6, "%d", ImGuiSliderFlags_None))
    {
        resize(_amountTrees);
    }
    if(ImGui::DragInt("Amount trees", &_amountTrees, 0.1f, 1, 6, "%d", ImGuiSliderFlags_None))
    {
        updateAmountTrees();
        resize(_amountTrees);
    }
    if(ImGui::Button("Rotate"))
    {
        _isRotate = !_isRotate;
    }
}


void figure::PythagorasTree::createTree(engine::Vector2 vector, float dir, float length, int iterations)
{
    engine::Vector2 nextVector(vector.x + length * sin(dir * RADIAN), 
    vector.y + length * cos(dir * RADIAN));

    sizeVBO += 4;
    VBO[sizeVBO - 4] = vector.x;
    VBO[sizeVBO - 3] = vector.y;
    VBO[sizeVBO - 2] = nextVector.x;
    VBO[sizeVBO - 1] = nextVector.y;   

    if (iterations > 0 && length > 0.0008f) 
    {       
        for (int i = 0; i < _amountBranchs; i++)
        {
            createTree(nextVector, dir + _angle * (i + 2 * M_PI / _amountTrees), length * 0.5f, iterations - 1);
        }
    }
}

void figure::PythagorasTree::addIteration(int iterations)
{
    amountElements += 4;

    if (iterations > 0) 
    {   
        for (int i = 0; i < _amountBranchs; i++)
        {
            addIteration(iterations - 1);
        }
    }
}

void figure::PythagorasTree::updateAmountTrees()
{
    if (_amountTrees == 1)  
    {
        _dir = 0;
        startPoint.y = -1.0f;
    }
    else
    {
        startPoint.y = 0.0f;
        _dir = 360 / _amountTrees;
    }
}