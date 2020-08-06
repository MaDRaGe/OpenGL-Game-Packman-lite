#pragma once
#include <memory>
#include <vector>
#include "GameObject.h"

using namespace std;

class Portal
{
public:
    // Конструтор
    Portal();

    // Добавить координаты новой точки входа
    void add(ivec2);

    // Портал пуст ?
    bool isLeave();

    // Игрок в портале
    bool playerInPortal(ivec2);

	bool isInPortal();

    // Переместить игрока
    ivec2 move(ivec2);

    void simulate(ivec2 playerPos);

private:
    bool leave;
	bool inPortal;
    // Точки входа в портал
    vector<ivec2> points;
};