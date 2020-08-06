#include "simulation.h"
#include <random>
#include "GameObject.h"

using namespace std;
default_random_engine generator;

void simulation()
{
    // Время вывода одного кадра
    simulationTime = getSimulationTime();

    if (!gameOver) // Игра не окончена
    {
        // Движение объектов
        objectSimulation(simulationTime);

        // Функционирование бомбы
        bombSimulation(simulationTime);
    }

    // Функционирование монстров
    monstersSimulation(simulationTime);

    // Функционирование порталов
    portalSimulation();

    // Функционирование камеры
    cameraSimulation();

    /*vec3 pos = hero->getGraphicPosition();
    lightHero.setPosition(pos);*/

    // Перерисовать окно
    glutPostRedisplay();
}

// Время вывода одного кадра
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

// Перемещение камеры по нажатию клавиши
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

// Движение объектов
void objectSimulation(float simulationTime)
{
    // Движение героя по нажатию клавиши
    int x = hero->getPosition().x;
    int y = hero->getPosition().y;
    if (    GetAsyncKeyState('W') // Вверх
         && !hero->isMoving()
       )
    {
        if (passabilityMap[x][y - 1] == 0 // Клетка пустая или с порталом
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
    if (    GetAsyncKeyState('S') // Вниз
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
    if (    GetAsyncKeyState('A') // Вправо
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
    if (    GetAsyncKeyState('D') // Влево
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

    // Движение блоков
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

// Обработка нажатия клавиш
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

// Функционирование порталов
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

// Функционирование бомбы
void bombSimulation(float simulationTime)
{
    if (    !hero->isMoving() // Установить бомбу
         && GetAsyncKeyState(VK_SPACE)
         && !bomb->isInGame()
       )
    {
        int x = hero->getPosition().x;
        int y = hero->getPosition().y;
        passabilityMap[x][y] = 9;
        bomb->start(x, y, 2);
    }
    if (bomb->isInGame()) // Отследить состояние бомбы
    {
        bomb->simulate(simulationTime);
        if (bomb->isExploded()) // Бомба взорвалась
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
                    // Уничтожить объекты вокруг бомбы
                    if (passabilityMap[x + i][y + j] == 1)  // Легкий ящик
                    {
                        passabilityMap[x + i][y + j] = 0;
                        gameObjects[x + i][y + j] = nullptr;
                    }
                    if (passabilityMap[x + i][y + j] == 8)  // Монстр
                    {
                        for (int k = 0; k < monsters.size(); k++) // Все монстры
                        {
                            if (   monsters[k]->monster != nullptr               // Убить монстра
                                 & monsters[k]->position == ivec2(x + i, y + j)
                               )
                            {
                                 monsters[k]->monster = nullptr;
                                 passabilityMap[x + i][y + j] = 0;
                                 gameObjects[x + i][y + j] = nullptr;
                            }
                        }
                    }
                    if (ivec2(x + i, y + j) == hero->getPosition()) // Игрок
                    {
                        killHero();
                    }
                }
            }
        }
    }
}

// Монстры
void monstersSimulation(float simulationTime)
{
    for (int i = 0; i < monsters.size(); i++) // Все монстры
    {
        if (monsters[i]->monster != nullptr) // Монстр существует
        {
            if (!monsters[i]->monster->isMoving()) // Монстр не двигается
            {
                // Выбрать направление движения монстра
                MoveDirection selectedDir = selectMoveDirection(monsters[i]);

                // Монстр начал движение в указанном направлении
                monsterMove(monsters[i], selectedDir);
            }
            else // Монстр уже двигается
            {
                monsters[i]->monster->simulate(simulationTime);
            }
        }
    }
}

// Выбрать направление движения мостра
MoveDirection selectMoveDirection(shared_ptr<Monster> monster)
{
    // Определить свободное нарпавление вперед
    vector<MoveDirection> freeDir;
    int x = monster->monster->getPosition().x;
    int y = monster->monster->getPosition().y;
    if (passabilityMap[x][y - 1] == 0 // Верх
        && monster->returnDirection != MoveDirection::up
        )
    {
        freeDir.push_back(MoveDirection::up);
    }
    if (passabilityMap[x + 1][y] == 0 // Право
        && monster->returnDirection != MoveDirection::right
        )
    {
        freeDir.push_back(MoveDirection::right);
    }
    if (passabilityMap[x][y + 1] == 0 // Низ
        && monster->returnDirection != MoveDirection::down
        )
    {
        freeDir.push_back(MoveDirection::down);
    }
    if (passabilityMap[x - 1][y] == 0 // Лево
        && monster->returnDirection != MoveDirection::left
        )
    {
        freeDir.push_back(MoveDirection::left);
    }
    MoveDirection selectedDir;
    if (!freeDir.empty()) // Есть свободное направление вперед
    {
        // Выбрать направление вперед
        uniform_int_distribution<int> distribution(0, freeDir.size() - 1);
        selectedDir = freeDir[distribution(generator)];
    }
    else // Можно пойти только назад
    {
        selectedDir = monster->returnDirection;
    }
    return selectedDir;
}

// Монстр начал движение в указанном направлении
void monsterMove(shared_ptr<Monster> monster, MoveDirection selectedDir)
{
    int x = monster->monster->getPosition().x;
    int y = monster->monster->getPosition().y;
    monster->monster->move(selectedDir, SPEED / 5);
    passabilityMap[x][y] = 0;
    switch (selectedDir) // Выбранное направление
    {
    case MoveDirection::up: // Верх
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

    case MoveDirection::right: // Право
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

    case MoveDirection::down: // Низ
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

    case MoveDirection::left: // Лево
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

// Героя убили
void killHero()
{
    audioManager.play(DEATH);
    audioManager.stop(AMBIENT);
    gameOver = true;
}