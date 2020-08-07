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
    // Конструктор
    GameObject();

    void setGraphicObject(const GraphicObject&);

    // Обработка позиции объекта
    void setPosition(int, int);
    void setPosition(glm::ivec2);
    glm::ivec2 getPosition();

    // Двигаться по направлению
    void move(MoveDirection dir, float speed);

    // Объект движется ?
    bool isMoving();


    void simulate(float sec);

    // Получить графическое представление объекта
    glm::vec3 getGraphicPosition();

    // Отобразить объект на экране
    void draw();

    // Объекта прозрачный ?
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