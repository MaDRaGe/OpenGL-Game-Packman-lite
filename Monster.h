#pragma once
#include "GameObject.h"
#include "glm.hpp"

class Monster
{
public:
    Monster(std::shared_ptr<GameObject> monster);
public:
    // ������������� �������
    std::shared_ptr<GameObject> monster;

    // ����������� ������ ������ ������
    MoveDirection returnDirection;

    // ������ ������ ������ ���?
    bool firstMove;

    // ������� �������
    glm::ivec2 position;
};
