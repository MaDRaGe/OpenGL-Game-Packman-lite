#pragma once
#include <memory>
#include <vector>
#include "GameObject.h"

class Portal
{
public:
    // ����������
    Portal();

    // �������� ���������� ����� ����� �����
    void add(glm::ivec2);

    // ������ ���� ?
    bool isLeave();

    // ����� � �������
    bool playerInPortal(glm::ivec2);

	bool isInPortal();

    // ����������� ������
    glm::ivec2 move(glm::ivec2);

    void simulate(glm::ivec2 playerPos);

private:
    bool leave;
	bool inPortal;
    // ����� ����� � ������
    std::vector<glm::ivec2> points;
};