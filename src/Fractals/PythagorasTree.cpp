#include <PythagorasTree.h>
#include <Line.h>
#include <Vector2.h>
#include <math.h>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <assert.h>

#define SIZE_INT sizeof(int)

int sizeEbo = 0;

figure::PythagorasTree::PythagorasTree(int iterations, float angle, int amountBranchs, 
float speedRotation, int amountTrees, float length, float xPos, unsigned int* shaderId)
{
    _length = length;
    _amountTrees = amountTrees;
    _amountBranchs = amountBranchs;
    _iterations = iterations; 
    _speedRotation = speedRotation;
    _isRotate = true;
    _angle = angle;

    _startPoint.x = xPos;

    if (amountTrees == 1)
    {
        _dir = 0;
        _startPoint.y = -1.0f;
    }
    else
    {
        _startPoint.y = 0.0f;
        _dir = 360 / amountTrees;
    }
    _shaderId = shaderId;
    setScale(glm::vec2(1, 1));    
}

void figure::PythagorasTree::update(float deltaTime)
{   
    _angle += deltaTime * _speedRotation;

    for (int i = 1; i < _amountTrees + 1; i++)
    {
        createTree(_startPoint, _dir * i, _length, _iterations);
    }
    
    _line.setVerticles(_vbo, _sizeVbo);
    _line.render();

    free(_vbo);
    _vbo = 0;
    _sizeVbo = 0;
}

void figure::PythagorasTree::withdrawUI()
{   
    Fractal::withdrawUI();
    ImGui::DragFloat("Length", &_length, 0.05f, 0.0f, 1, "%.3f", ImGuiSliderFlags_None);
    ImGui::DragFloat("Speed rotation", &_speedRotation, 0.1f, 0.0f, 100.0f, "%.3f", ImGuiSliderFlags_None);
    ImGui::DragInt("Iteration", &_iterations, 0.1f, 0, 10, "%d", ImGuiSliderFlags_None);
    ImGui::DragInt("Amount tranchs", &_amountBranchs, 0.1f, 1, 6, "%d", ImGuiSliderFlags_None);
    if(ImGui::DragInt("Amount trees", &_amountTrees, 0.1f, 1, 6, "%d", ImGuiSliderFlags_None))
    {
        updateAmountTrees();
    }
}


void figure::PythagorasTree::createTree(engine::Vector2 vector, float dir, float length, int iterations)
{
    engine::Vector2 nextVector(vector.x + length * sin(dir * RADIAN), 
    vector.y + length * cos(dir * RADIAN));

    _sizeVbo += 4;
    _vbo = (float*)realloc(_vbo, (_sizeVbo) * sizeof(float));
    assert(_vbo);
    _vbo[_sizeVbo - 4] = vector.x;
    _vbo[_sizeVbo - 3] = vector.y;
    _vbo[_sizeVbo - 2] = nextVector.x;
    _vbo[_sizeVbo - 1] = nextVector.y;      

    std::cout << "index: " << _sizeVbo << std::endl;

    if (iterations > 0 && length > 0.0008f) 
    {       
        for (int i = 0; i < _amountBranchs; i++)
        {
            createTree(nextVector, dir + _angle * (i + 2 * M_PI / _amountTrees), length * 0.5f, iterations - 1);
        }
    }
}

void figure::PythagorasTree::setScale(glm::vec2 newScale)
{ 
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(newScale.x, newScale.y, 0));  
    unsigned int transformLoc = glGetUniformLocation(*_shaderId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void figure::PythagorasTree::updateAmountTrees()
{
    if (_amountTrees == 1)
    {
        _dir = 0;
        _startPoint.y = -1.0f;
    }
    else
    {
        _startPoint.y = 0.0f;
        _dir = 360 / _amountTrees;
    }
}