#pragma once
#include "GraphicObject.h"
#include "glm.hpp"

enum class MoveDirection { 
    stop, 
    up, down, 
    left, 
    right 
};

class GameObject
{
public:
    // �����������
    GameObject();

    void setGraphicObject(const GraphicObject&);

    // ��������� ������� �������
    void setPosition(int, int);
    void setPosition(glm::ivec2);
    glm::ivec2 getPosition();

    // ��������� �� �����������
    void move(MoveDirection dir, float speed);

    // ������ �������� ?
    bool isMoving();


    void simulate(float sec);

    // �������� ����������� ������������� �������
    glm::vec3 getGraphicPosition();

    // ���������� ������ �� ������
    void draw();

    // ������� ���������� ?
    bool isTransparent(); 
public:
    float high;

private:
    glm::ivec2 position;
    GraphicObject graphicObject;
    MoveDirection sost;
    float progress;
    float speed;
};