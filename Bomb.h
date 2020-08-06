#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "glm.hpp"

class Bomb
{
public:
    // �����������
    Bomb();

    // 
    void simulate(float sec);

    // ��������� �����
    void start(int x, int y, float timeToExplode);

    // �������� �������
    glm::ivec2 getPosition();

    // ����� ����������� ?
    bool isInGame();

    // ����� ���������� ?
    bool isExploded();

    // ���������� ������� ������ ��� �����
    void setGameObject(std::shared_ptr<GameObject>);

    // ���������� ��������� �����
    void setHUD(std::shared_ptr<Sprite>, std::shared_ptr<Sprite>);

    // ���������� �� ������
    void draw();

    // ���������� ��������� �� ������
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