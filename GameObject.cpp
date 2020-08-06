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

// Обработка позиции объекта
void GameObject::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}
void GameObject::setPosition(ivec2 position) 
{ 
    this->position = position; 
}
ivec2 GameObject::getPosition() 
{ 
    return position; 
}

// Отобразить объект на экране
void GameObject::draw()
{
	switch (sost) {
	case MoveDirection::stop:
		graphicObject.setPosition(vec3(position.x - 10, high, position.y - 10));
		break;
	case MoveDirection::up:
		graphicObject.setPosition(vec3(position.x - 10, high, position.y - 10 - progress));
		break;
	case MoveDirection::down:
		graphicObject.setPosition(vec3(position.x - 10, high, position.y - 10 + progress));
		break;
	case MoveDirection::left:
		graphicObject.setPosition(vec3(position.x - 10 - progress, high, position.y - 10));
		break;
	case MoveDirection::right:
		graphicObject.setPosition(vec3(position.x - 10 + progress, high, position.y - 10));
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

// Объект движется?
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
    if (isMoving()) // Объект движется
    {
		float path = sec * speed;

        // Изменить значение пройденного расстояния
        progress += path;
        if (progress >= 1) // Объект достиг цели
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

// Получить графическое представление объекта
vec3 GameObject::getGraphicPosition()
{
    return graphicObject.getPosition();
}

// Объект прозрачный ?
bool GameObject::isTransparent()
{
    return graphicObject.isTransparent();
}
