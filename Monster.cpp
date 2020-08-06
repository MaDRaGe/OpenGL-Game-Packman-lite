#include "Monster.h"

Monster::Monster(shared_ptr<GameObject> monster)
{
    this->returnDirection = MoveDirection::stop;
    this->monster = monster;
    this->firstMove = true;
    this->position = monster->getPosition();
}
