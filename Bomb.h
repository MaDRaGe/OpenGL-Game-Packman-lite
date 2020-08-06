#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "glm.hpp"

class Bomb
{
public:
    // Конструктор
    Bomb();

    // 
    void simulate(float sec);

    // Установка бомбы
    void start(int x, int y, float timeToExplode);

    // Получить позицию
    glm::ivec2 getPosition();

    // Бомба установлена ?
    bool isInGame();

    // Бомба взорвалась ?
    bool isExploded();

    // Установить игровой объект для бомбы
    void setGameObject(std::shared_ptr<GameObject>);

    // Установить интерфейс бомбы
    void setHUD(std::shared_ptr<Sprite>, std::shared_ptr<Sprite>);

    // Отобразить на экране
    void draw();

    // Отобразить интерфейс на экране
    void displayHUD();

private:
    bool inGame; // The bomb has been planted
    bool exploded; // Exploded
    float progress;
    glm::ivec2 position;
    std::shared_ptr<GameObject> gameObject;
    std::shared_ptr<Sprite> icon;
    std::shared_ptr<Sprite> tick;
    int tickNumber;
    float timeToExplode;
};