#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>

#include "GameObject.h"
#include "Sprite.h"

#include <gl\GL.h>
#include <gl\GLU.h>
#include "freeglut.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"

using namespace glm;

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
    ivec2 getPosition();

    // Бомба установлена ?
    bool isInGame();

    // Бомба взорвалась ?
    bool isExploded();

    // Установить игровой объект для бомбы
    void setGameObject(shared_ptr<GameObject>);

    // Установить интерфейс бомбы
    void setHUD(shared_ptr<Sprite>, shared_ptr<Sprite>);

    // Отобразить на экране
    void draw();

    // Отобразить интерфейс на экране
    void displayHUD();

private:
    bool inGame; // The bomb has been planted
    bool exploded; // Exploded
    float progress;
    ivec2 position;
    shared_ptr<GameObject> gameObject;
    shared_ptr<Sprite> icon;
    shared_ptr<Sprite> tick;
    int tickNumber;
    float timeToExplode;
};