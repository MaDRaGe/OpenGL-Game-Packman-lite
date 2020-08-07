#pragma once
#include "GameObject.h"
#include "glm.hpp"

class Monster
{
public:
    Monster(std::shared_ptr<GameObject> monster);
public:
    // Представление монстра
    std::shared_ptr<GameObject> monster;

    // Направление откуда монстр пришел
    MoveDirection returnDirection;

    // Монстр делает первый шаг?
    bool firstMove;

    // Позиция монстра
    glm::ivec2 position;
};
