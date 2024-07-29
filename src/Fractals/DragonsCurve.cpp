#include <DragonsCurve.h>
#include <vector>
#include <Vector2.h>
#include <math.h>    
#include <Line.h>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

figure::DragonsCurve::DragonsCurve(int iterations, float length, float xPos, unsigned int* shaderId)
{
    _shaderId = shaderId;
    _length = length;
    _iterations = iterations;

    _startPoint = {xPos, 0.0f};
    setScale(glm::vec2(1, 1));
}

void figure::DragonsCurve::drawCurve(engine::Vector2 startPoint, float length, float angle, int iterations)
{
    engine::Vector2 nextPoint(startPoint.x + _length * cos(angle), startPoint.y + _length * sin(angle));

    if(iterations == 0)
    {
        _points.push_back(startPoint);
        _points.push_back(nextPoint);
        return;
    }

    drawCurve(startPoint, length / sqrt(2),  angle - M_PI / 4.0f, iterations - 1);
    drawCurve(nextPoint, length / sqrt(2), M_PI + angle + M_PI / 4.0f, iterations - 1);
}

void figure::DragonsCurve::update(float deltaTime)
{
    _points.clear();
    drawCurve(_startPoint, _length, 0.0f, _iterations);
    //Line line(_points, 0.1f);
    //line.render();
}

void figure::DragonsCurve::setScale(glm::vec2 newScale)
{ 
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(newScale.x, newScale.y, 0));  
    unsigned int transformLoc = glGetUniformLocation(*_shaderId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void figure::DragonsCurve::withdrawUI() {   }