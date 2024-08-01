#include <Fractal.h>
#include <imgui.h>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

void figure::Fractal::withdrawUI()
{
    ImGui::Text("Fractal:");  
}

void figure::Fractal::setScale(glm::vec2 newScale)
{ 
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(newScale.x, newScale.y, 0));  
    unsigned int transformLoc = glGetUniformLocation(*shaderId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void figure::Fractal::resize(int amountRepeats)
{
    amountElements = 0;

    for (int i = 0; i < amountRepeats; i++)
    {
        addIteration(iterations);
    }

    VBO = (float*)realloc(VBO, amountElements * sizeof(float));
}

void figure::Fractal::addIteration(int iterations)
{
    amountElements += 4;

    if (iterations > 0) 
    {   
        addIteration(iterations - 1);
    }
}

figure::Fractal::~Fractal()
{
    free(VBO);
    VBO = 0;
}