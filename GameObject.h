#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>

#include "GraphicObject.h"

#include <gl\GL.h>
#include <gl\GLU.h>
#include "freeglut.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"


using namespace std;
using namespace glm;

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
    void setPosition(ivec2);
    ivec2 getPosition();

    // ��������� �� �����������
    void move(MoveDirection dir, float speed);

    // ������ �������� ?
    bool isMoving();


    void simulate(float sec);

    // �������� ����������� ������������� �������
    vec3 getGraphicPosition();

    // ���������� ������ �� ������
    void draw();

    // ������� ���������� ?
    bool isTransparent(); 
public:
    float high;

private:
    ivec2 position;
    GraphicObject graphicObject;
    MoveDirection sost;
    float progress;
    float speed;
};