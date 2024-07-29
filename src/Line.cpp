#include <Line.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>

figure::Line::Line(float thickness)
{
    _thickness = thickness;

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0); 
}

void figure::Line::setVerticles(float verticles[], int sizeVerticles)
{
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeVerticles, verticles, GL_DYNAMIC_DRAW);  
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0); 
    _size = sizeVerticles;  
}

figure::Line::~Line()
{
    glDeleteBuffers(1, &_VBO);
    glDeleteVertexArrays(1, &_VAO);
}

void figure::Line::render()
{
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBindVertexArray(_VAO);
    glLineWidth(_thickness);
    glDrawArrays(GL_LINES, 0, _size);
}