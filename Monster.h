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
    // ������������� �������
    shared_ptr<GameObject> monster;

    // ����������� ������ ������ ������
    MoveDirection returnDirection;

    // ������ ������ ������ ���?
    bool firstMove;

    // ������� �������
    ivec2 position;
};
