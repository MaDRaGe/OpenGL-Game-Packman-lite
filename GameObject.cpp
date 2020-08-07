#include "GameObject.h"

GameObject::GameObject() 
{ 
    high = 0.5; 
    sost = MoveDirection::stop;
}

void GameObject::setGraphicObject(const GraphicObject& graphicObject) 
{ 
    this->graphicObject = graphicObject; 
}

// ��������� ������� �������
void GameObject::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}
void GameObject::setPosition(glm::ivec2 position) 
{ 
    this->position = position; 
}
glm::ivec2 GameObject::getPosition() 
{ 
    return position; 
}

// ���������� ������ �� ������
void GameObject::draw()
{
	switch (sost) {
	case MoveDirection::stop:
		graphicObject.setPosition(glm::vec3(position.x - 10, high, position.y - 10));
		break;
	case MoveDirection::up:
		graphicObject.setPosition(glm::vec3(position.x - 10, high, position.y - 10 - progress));
		break;
	case MoveDirection::down:
		graphicObject.setPosition(glm::vec3(position.x - 10, high, position.y - 10 + progress));
		break;
	case MoveDirection::left:
		graphicObject.setPosition(glm::vec3(position.x - 10 - progress, high, position.y - 10));
		break;
	case MoveDirection::right:
		graphicObject.setPosition(glm::vec3(position.x - 10 + progress, high, position.y - 10));
		break;
	}
    graphicObject.draw();
}


void GameObject::move(
    MoveDirection dir, 
    float speed
)
/*
    params:
        dir - move direction
        speed - move speed
*/
{
    sost = dir;
    this->speed = speed;
    progress = 0;
}

// ������ ��������?
bool GameObject::isMoving()
{
    if (this->sost == MoveDirection::stop)
    {
        return false;
    }
    return true;
}
void GameObject::simulate(float sec)
{
    if (isMoving()) // ������ ��������
    {
		float path = sec * speed;

        // �������� �������� ����������� ����������
        progress += path;
        if (progress >= 1) // ������ ������ ����
        {
			switch (sost)
			{
			case MoveDirection::up:
				position.y -= 1;
				break;
			case MoveDirection::down:
				position.y += 1;
				break;
			case MoveDirection::left:
				position.x -= 1;
				break;
			case MoveDirection::right:
				position.x += 1;
				break;
			}
			progress = 0;
            sost = MoveDirection::stop;
        }
    }
}

// �������� ����������� ������������� �������
glm::vec3 GameObject::getGraphicPosition()
{
    return graphicObject.getPosition();
}

// ������ ���������� ?
bool GameObject::isTransparent()
{
    return graphicObject.isTransparent();
}
