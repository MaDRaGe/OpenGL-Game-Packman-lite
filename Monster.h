#pragma once
#include "GameObject.h"
#include "glm.hpp"

using namespace std;
using namespace glm;

class Monster
{
public:
    Monster(shared_ptr<GameObject> monster);
public:
    // Представление монстра
    shared_ptr<GameObject> monster;

    // Направление откуда монстр пришел
    MoveDirection returnDirection;

    // Монстр делает первый шаг?
    bool firstMove;

    // Позиция монстра
    ivec2 position;
};
