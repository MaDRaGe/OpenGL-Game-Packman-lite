#include "Bomb.h"

Bomb::Bomb()
{
    inGame = false;
    exploded = false;
}

void Bomb::simulate(float sec)
{
    progress -= sec;
    tickNumber = (int)(progress / timeToExplode * 10) + 1;
    if (progress <= 0)
    {
        exploded = true;
        inGame = false;
    }
}

// Установка бомбы
void Bomb::start(
    int x, 
    int y, 
    float timeToExplode
)
/*
    params:
        x, y - coords
        timeToExplode - time after bomd is exploding
*/
{
    inGame = true;
    exploded = false;
    progress = timeToExplode;
    this->timeToExplode = timeToExplode;
    gameObject->setPosition(glm::ivec2(x, y));
}

ivec2 Bomb::getPosition()
{
    return gameObject->getPosition();
}

// Бомба установлена
bool Bomb::isInGame()
{
    return inGame;
}

// Бомба взорвана
bool Bomb::isExploded()
{
    return exploded;
}

void Bomb::setGameObject(std::shared_ptr<GameObject> gameObject)
{
    this->gameObject = gameObject;
}

// Установить интерфейс на экране
void Bomb::setHUD(
    std::shared_ptr<Sprite> icon,
    std::shared_ptr<Sprite> tick
)
{
    this->icon = icon;
    this->tick = tick;
}

// Отобразить на экране
void Bomb::draw()
{
    gameObject->draw();
    displayHUD();
}

// Отобразить интерфейс на экране
void Bomb::displayHUD()
{
    icon->drawFromLeftUp(70, 100);
    int offset = 30;
    for (int i = 0; i < tickNumber; i++)
    {
        tick->drawFromLeftUp(120 + offset, 100);
        offset += 30;
    }
}

