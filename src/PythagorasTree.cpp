#include <PythagorasTree.h>
#include <Line.h>
#include <Vector2.h>
#include <math.h>
#include <iostream>

figure::PythagorasTree::PythagorasTree(int iterations, float angle)
{
    engine::Vector2 vec(0.0, -1.0);

    //engine::Vector2 nextVector(0.0f, 0.0f);


    _angle = angle / 2;
    // engine::Vector2 vec(0.0, -1.0);

    // engine::Vector2 nextVector(0.0f, 0.0f);

    // figure::Line line(vec, nextVector, 0.01f);
    // _line = line;


    createLine(engine::Vector2(0.0f, -1.0f), engine::Vector2(0.0f, -0.6f));

    // figure::Line line(vec, nextVector, 0.01f);
    // _lines.push_back(line);
    //createTree(vec, 0, 0.4f, iterations);
}

void figure::PythagorasTree::render()
{
    // clear();
    // engine::Vector2 vec(0.0, -1.0);
    // createTree(vec, M_PI / 2, 0.4f, 10, _angle);
    // _angle += 0.01f;

    for (auto& line : _lines)
    {
        line.render();
    }

}


void figure::PythagorasTree::createTree(engine::Vector2 vector, float dir, float length, int iteration)
{
    engine::Vector2 nextVector(vector.x + length * sin(dir * RADIAN), 
    vector.y + length * cos(dir * RADIAN));

    std::cout << vector.x << " " << vector.y << std::endl;
    std::cout << nextVector.x << " " << nextVector.y << std::endl;

    createLine(vector, nextVector);

    if (iteration > 0 && length > 0.0008f) {
        createTree(nextVector, dir + _angle, length * 0.72, iteration - 1);
        createTree(nextVector, dir - _angle, length * 0.72, iteration - 1);
    }
}

void figure::PythagorasTree::createLine(engine::Vector2 point1, engine::Vector2 point2)
{
    _lines.emplace_back(figure::Line(point1, point2, 0.02f));
}

void figure::PythagorasTree::clear()
{
    _lines.clear();
}