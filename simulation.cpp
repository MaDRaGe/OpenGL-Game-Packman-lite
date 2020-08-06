#include "simulation.h"
#include <random>
#include "GameObject.h"

using namespace std;
default_random_engine generator;

void simulation()
{
    // ����� ������ ������ �����
    simulationTime = getSimulationTime();

    if (!gameOver) // ���� �� ��������
    {
        // �������� ��������
        objectSimulation(simulationTime);

        // ���������������� �����
        bombSimulation(simulationTime);
    }

    // ���������������� ��������
    monstersSimulation(simulationTime);

    // ���������������� ��������
    portalSimulation();

    // ���������������� ������
    cameraSimulation();

    /*vec3 pos = hero->getGraphicPosition();
    lightHero.setPosition(pos);*/

    // ������������ ����
    glutPostRedisplay();
}

// ����� ������ ������ �����
double getSimulationTime()
{
    QueryPerformanceCounter(&newValue);
    double time = (double)(newValue.QuadPart - oldValue.QuadPart) / (double)counter.QuadPart;
    while (time * 1000000 < 1000000 / FPS)
    {
        QueryPerformanceCounter(&newValue);
        time = (double)(newValue.QuadPart - oldValue.QuadPart) / (double)counter.QuadPart;
    }
    oldValue = newValue;
    return time;
}

// ����������� ������ �� ������� �������
void cameraSimulation()
{
    if (GetAsyncKeyState(VK_RIGHT))
    {
        camera.rotateLeftRight(-1);
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        camera.rotateLeftRight(1);
    }
    if (GetAsyncKeyState(VK_UP))
    {
        camera.rotateUpDown(3);
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        camera.rotateUpDown(-3);
    }
    audioManager.setListenerPosition(camera.getPosition());
}

// �������� ��������
void objectSimulation(float simulationTime)
{
    // �������� ����� �� ������� �������
    int x = hero->getPosition().x;
    int y = hero->getPosition().y;
    if (    GetAsyncKeyState('W') // �����
         && !hero->isMoving()
       )
    {
        if (passabilityMap[x][y - 1] == 0 // ������ ������ ��� � ��������
            || passabilityMap[x][y - 1] == 5
            || passabilityMap[x][y - 1] == 6
            )
        {
            hero->move(MoveDirection::up, SPEED);
        }
        else
        {
            if (    passabilityMap[x][y - 1] == 1 
                 && passabilityMap[x][y - 2] == 0
               )
            {
                audioManager.play(SHIFT, vec3(x, y + 2, 0));
                hero->move(MoveDirection::up, SPEED);
                gameObjects[x][y - 1]->move(MoveDirection::up, SPEED);
                passabilityMap[x][y] = 0;
                passabilityMap[x][y - 1] = 0;
                passabilityMap[x][y - 2] = 1;
                gameObjects[x][y - 2] = gameObjects[x][y - 1];
                gameObjects[x][y - 1] = nullptr;
            }
        }
    }
    if (    GetAsyncKeyState('S') // ����
         && !hero->isMoving()
       )
    {
        if (passabilityMap[x][y + 1] == 0
            || passabilityMap[x][y + 1] == 5
            || passabilityMap[x][y + 1] == 6
            )
        {
            hero->move(MoveDirection::down, SPEED);
        }
        else
        {
            if (passabilityMap[x][y + 1] == 1 && passabilityMap[x][y + 2] == 0)
            {
                audioManager.play(SHIFT, vec3(x, y + 2, 0));
                hero->move(MoveDirection::down, SPEED);
                gameObjects[x][y + 1]->move(MoveDirection::down, SPEED);
                passabilityMap[x][y] = 0;
                passabilityMap[x][y + 1] = 0;
                passabilityMap[x][y + 2] = 1;
                gameObjects[x][y + 2] = gameObjects[x][y + 1];
                gameObjects[x][y + 1] = nullptr;
            }
        }
    }
    if (    GetAsyncKeyState('A') // ������
         && !hero->isMoving()
       )
    {
        if (passabilityMap[x - 1][y] == 0
            || passabilityMap[x - 1][y] == 5
            || passabilityMap[x - 1][y] == 6
            )
        {
            hero->move(MoveDirection::left, SPEED);
        }
        else
        {
            if (passabilityMap[x - 1][y] == 1 && passabilityMap[x - 2][y] == 0)
            {
                audioManager.play(SHIFT, vec3(x - 2, y, 0));
                hero->move(MoveDirection::left, SPEED);
                gameObjects[x - 1][y]->move(MoveDirection::left, SPEED);
                passabilityMap[x][y] = 0;
                passabilityMap[x - 1][y] = 0;
                passabilityMap[x - 2][y] = 1;
                gameObjects[x - 2][y] = gameObjects[x - 1][y];
                gameObjects[x - 1][y] = nullptr;
            }
        }
    }
    if (    GetAsyncKeyState('D') // �����
         && !hero->isMoving()
       )
    {
        if (    passabilityMap[x + 1][y] == 0
             || passabilityMap[x + 1][y] == 5
             || passabilityMap[x + 1][y] == 6
           )
        {
            hero->move(MoveDirection::right, SPEED);
        }
        else
        {
            if (passabilityMap[x + 1][y] == 1 && passabilityMap[x + 2][y] == 0)
            {
                audioManager.play(SHIFT, vec3(x + 2, y, 0));
                hero->move(MoveDirection::right, SPEED);
                gameObjects[x + 1][y]->move(MoveDirection::right, SPEED);
                passabilityMap[x][y] = 0;
                passabilityMap[x + 1][y] = 0;
                passabilityMap[x + 2][y] = 1;
                gameObjects[x + 2][y] = gameObjects[x + 1][y];
                gameObjects[x + 1][y] = nullptr;
            }
        }
    }
    hero->simulate(simulationTime);

    // �������� ������
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (    gameObjects[i][j] != nullptr
                 && passabilityMap[i][j] != 8
               )
            {
                gameObjects[i][j]->simulate(simulationTime);
            }
        }
    }
}

// ��������� ������� ������
void keyPress(unsigned char key, int x, int y)
{
    if (key == 49)
    {
        if (onMSAA) {
            onMSAA = !onMSAA;
            glDisable(GL_MULTISAMPLE);
        }
        else
        {
            onMSAA = !onMSAA;
            glEnable(GL_MULTISAMPLE);
        }
    }
    if (key == 50)
    {
        Texture::textFilterMode += 1;
        if (Texture::textFilterMode > 8)
        {
            Texture::textFilterMode = 0;
        }
    }
}

// ���������������� ��������
void portalSimulation()
{
    if (!hero->isMoving())
    {
        int x = hero->getPosition().x;
        int y = hero->getPosition().y;
        portal_1.simulate(ivec2(x, y));
        portal_2.simulate(ivec2(x, y));
        if (    portal_1.isInPortal()
             && portal_1.isLeave()
           )
        {
            hero->setPosition(portal_1.move(ivec2(x, y)));
        }
        if (    portal_2.isInPortal()
             && portal_2.isLeave()
           )
        {
            audioManager.play(PORTAL);
            hero->setPosition(portal_2.move(ivec2(x, y)));
        }
    }
}

// ���������������� �����
void bombSimulation(float simulationTime)
{
    if (    !hero->isMoving() // ���������� �����
         && GetAsyncKeyState(VK_SPACE)
         && !bomb->isInGame()
       )
    {
        int x = hero->getPosition().x;
        int y = hero->getPosition().y;
        passabilityMap[x][y] = 9;
        bomb->start(x, y, 2);
    }
    if (bomb->isInGame()) // ��������� ��������� �����
    {
        bomb->simulate(simulationTime);
        if (bomb->isExploded()) // ����� ����������
        {
            audioManager.play(EXPLOSION);
            int x = bomb->getPosition().x;
            int y = bomb->getPosition().y;
            Decal decal(glm::ivec2(x, y));
            decals.push_back(decal);
            passabilityMap[x][y] = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    // ���������� ������� ������ �����
                    if (passabilityMap[x + i][y + j] == 1)  // ������ ����
                    {
                        passabilityMap[x + i][y + j] = 0;
                        gameObjects[x + i][y + j] = nullptr;
                    }
                    if (passabilityMap[x + i][y + j] == 8)  // ������
                    {
                        for (int k = 0; k < monsters.size(); k++) // ��� �������
                        {
                            if (   monsters[k]->monster != nullptr               // ����� �������
                                 & monsters[k]->position == ivec2(x + i, y + j)
                               )
                            {
                                 monsters[k]->monster = nullptr;
                                 passabilityMap[x + i][y + j] = 0;
                                 gameObjects[x + i][y + j] = nullptr;
                            }
                        }
                    }
                    if (ivec2(x + i, y + j) == hero->getPosition()) // �����
                    {
                        killHero();
                    }
                }
            }
        }
    }
}

// �������
void monstersSimulation(float simulationTime)
{
    for (int i = 0; i < monsters.size(); i++) // ��� �������
    {
        if (monsters[i]->monster != nullptr) // ������ ����������
        {
            if (!monsters[i]->monster->isMoving()) // ������ �� ���������
            {
                // ������� ����������� �������� �������
                MoveDirection selectedDir = selectMoveDirection(monsters[i]);

                // ������ ����� �������� � ��������� �����������
                monsterMove(monsters[i], selectedDir);
            }
            else // ������ ��� ���������
            {
                monsters[i]->monster->simulate(simulationTime);
            }
        }
    }
}

// ������� ����������� �������� ������
MoveDirection selectMoveDirection(shared_ptr<Monster> monster)
{
    // ���������� ��������� ����������� ������
    vector<MoveDirection> freeDir;
    int x = monster->monster->getPosition().x;
    int y = monster->monster->getPosition().y;
    if (passabilityMap[x][y - 1] == 0 // ����
        && monster->returnDirection != MoveDirection::up
        )
    {
        freeDir.push_back(MoveDirection::up);
    }
    if (passabilityMap[x + 1][y] == 0 // �����
        && monster->returnDirection != MoveDirection::right
        )
    {
        freeDir.push_back(MoveDirection::right);
    }
    if (passabilityMap[x][y + 1] == 0 // ���
        && monster->returnDirection != MoveDirection::down
        )
    {
        freeDir.push_back(MoveDirection::down);
    }
    if (passabilityMap[x - 1][y] == 0 // ����
        && monster->returnDirection != MoveDirection::left
        )
    {
        freeDir.push_back(MoveDirection::left);
    }
    MoveDirection selectedDir;
    if (!freeDir.empty()) // ���� ��������� ����������� ������
    {
        // ������� ����������� ������
        uniform_int_distribution<int> distribution(0, freeDir.size() - 1);
        selectedDir = freeDir[distribution(generator)];
    }
    else // ����� ����� ������ �����
    {
        selectedDir = monster->returnDirection;
    }
    return selectedDir;
}

// ������ ����� �������� � ��������� �����������
void monsterMove(shared_ptr<Monster> monster, MoveDirection selectedDir)
{
    int x = monster->monster->getPosition().x;
    int y = monster->monster->getPosition().y;
    monster->monster->move(selectedDir, SPEED / 5);
    passabilityMap[x][y] = 0;
    switch (selectedDir) // ��������� �����������
    {
    case MoveDirection::up: // ����
        monster->returnDirection = MoveDirection::down;
        if (hero->getPosition() == ivec2(x, y - 1))
        {
            killHero();
        }
        monster->position += ivec2(0, -1);
        passabilityMap[x][y - 1] = 8;
        gameObjects[x][y - 1] = gameObjects[x][y];
        gameObjects[x][y] = nullptr;
        break;

    case MoveDirection::right: // �����
        monster->returnDirection = MoveDirection::left;
        if (hero->getPosition() == ivec2(x + 1, y))
        {
            killHero();
        }
        monster->position += ivec2(1, 0);
        passabilityMap[x + 1][y] = 8;
        gameObjects[x + 1][y] = gameObjects[x][y];
        gameObjects[x][y] = nullptr;
        break;

    case MoveDirection::down: // ���
        monster->returnDirection = MoveDirection::up;
        if (hero->getPosition() == ivec2(x, y + 1))
        {
            killHero();
        }
        monster->position += ivec2(0, 1);
        passabilityMap[x][y + 1] = 8;
        gameObjects[x][y + 1] = gameObjects[x][y];
        gameObjects[x][y] = nullptr;
        break;

    case MoveDirection::left: // ����
        monster->returnDirection = MoveDirection::right;
        if (hero->getPosition() == ivec2(x - 1, y))
        {
            killHero();
        }
        monster->position += ivec2(-1, 0);
        passabilityMap[x - 1][y] = 8;
        gameObjects[x - 1][y] = gameObjects[x][y];
        gameObjects[x][y] = nullptr;
        break;
    }
}

// ����� �����
void killHero()
{
    audioManager.play(DEATH);
    audioManager.stop(AMBIENT);
    gameOver = true;
}