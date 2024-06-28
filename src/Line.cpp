#include <Line.h>
#include <glad/glad.h>
#include <iostream>

figure::Line::Line(engine::Vector2 point1, engine::Vector2 point2, float thickness)
{
    float halfThickness = thickness / 2;

    float verticles [] = {
        point1.x + halfThickness,  point1.y,
        point2.x + halfThickness, point2.y,
        point1.x - halfThickness, point1.y,
        point2.x + halfThickness, point2.y,
        point2.x - halfThickness, point2.y, 
        point1.x - halfThickness, point1.y
    };

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);  
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glEnableVertexAttribArray(0); 

    std::cout << "prekol" << std::endl;
}

figure::Line::Line(Line &&other)
{
    _VBO = other._VBO;
    _VAO = other._VAO;
}

figure::Line::~Line()
{
    glDeleteBuffers(1, &_VBO);
    glDeleteVertexArrays(1, &_VAO);

    std::cout << "I delete prekol" << std::endl;
}

void figure::Line::render()
{
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}