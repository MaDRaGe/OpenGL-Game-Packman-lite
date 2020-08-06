#pragma once
#include <memory>
#include <vector>
#include "GameObject.h"

class Portal
{
public:
    // Конструтор
    Portal();

    // Добавить координаты новой точки входа
    void add(glm::ivec2);

    // Портал пуст ?
    bool isLeave();

    // Игрок в портале
    bool playerInPortal(glm::ivec2);

	bool isInPortal();

    // Переместить игрока
    glm::ivec2 move(glm::ivec2);

    void simulate(glm::ivec2 playerPos);

private:
    bool leave;
	bool inPortal;
    // Точки входа в портал
    std::vector<glm::ivec2> points;
};