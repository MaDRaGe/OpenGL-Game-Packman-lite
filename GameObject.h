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
    // Конструктор
    GameObject();

    void setGraphicObject(const GraphicObject&);

    // Обработка позиции объекта
    void setPosition(int, int);
    void setPosition(ivec2);
    ivec2 getPosition();

    // Двигаться по направлению
    void move(MoveDirection dir, float speed);

    // Объект движется ?
    bool isMoving();


    void simulate(float sec);

    // Получить графическое представление объекта
    vec3 getGraphicPosition();

    // Отобразить объект на экране
    void draw();

    // Объекта прозрачный ?
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