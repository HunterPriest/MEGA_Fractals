#include <DragonsCurve.h>
#include <Vector2.h>
#include <math.h>    
#include <Line.h>
#include <iostream>

figure::DragonsCurve::DragonsCurve(int iterations, float length, float xPos, unsigned int* shaderId)
{
    this->shaderId = shaderId;
    _length = length;
    this->iterations = iterations;

    startPoint = {xPos, 0.0f};
    setScale(glm::vec2(1, 1));
    resize(1);
}

void figure::DragonsCurve::calculateAmountElements(int iterations)
{
    amountElements += 4;

    if (iterations > 0) 
    {   
        calculateAmountElements(iterations - 1);
        calculateAmountElements(iterations - 1);
    }
}

void figure::DragonsCurve::drawCurve(engine::Vector2 startPoint, float length, float angle, int iterations)
{
    engine::Vector2 nextPoint(startPoint.x + _length * cos(angle), startPoint.y + _length * sin(angle));

    VBOindex += 4;

    VBO[VBOindex - 4] = startPoint.x;
    VBO[VBOindex - 3] = startPoint.y;
    VBO[VBOindex - 2] = nextPoint.x;
    VBO[VBOindex - 1] = nextPoint.y;

    std::cout << startPoint.x << " " << startPoint.y << " " << nextPoint.x << " " << nextPoint.y << " " << VBOindex << " " << iterations << std::endl;

    if(iterations == 0)
    {
        drawCurve(startPoint, length / sqrt(2),  angle - M_PI / 4.0f, iterations - 1);
        drawCurve(nextPoint, length / sqrt(2), M_PI + angle + M_PI / 4.0f, iterations - 1);
    }
}

void figure::DragonsCurve::update(float deltaTime)
{
    VBOindex = 0;
    drawCurve(startPoint, _length, 0.0f, iterations);
    _line.setVerticles(VBO, VBOindex);
    _line.render();
}

void figure::DragonsCurve::withdrawUI() 
{

}