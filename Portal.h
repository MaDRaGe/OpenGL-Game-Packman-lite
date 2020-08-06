#pragma once
#include <memory>
#include <vector>
#include "GameObject.h"

using namespace std;

class Portal
{
public:
    // ����������
    Portal();

    // �������� ���������� ����� ����� �����
    void add(ivec2);

    // ������ ���� ?
    bool isLeave();

    // ����� � �������
    bool playerInPortal(ivec2);

	bool isInPortal();

    // ����������� ������
    ivec2 move(ivec2);

    void simulate(ivec2 playerPos);

private:
    bool leave;
	bool inPortal;
    // ����� ����� � ������
    vector<ivec2> points;
};