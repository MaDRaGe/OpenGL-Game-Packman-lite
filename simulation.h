
#include "data.h"

void simulation();
double getSimulationTime();

// Героя убили
void killHero();

// Перемещение камеры по нажатию клавиши
void cameraSimulation();

// Перемещение героя по нажатию клавиши
void objectSimulation(float);

// Обработка гажатия клавиши
void keyPress(unsigned char key, int x, int y);

// Логика порталов
void portalSimulation();

// Логика бомбы
void bombSimulation(float);

// Монстры
void monstersSimulation(float simulationTime);

// Определить направление движения
MoveDirection selectMoveDirection(shared_ptr<Monster> monster);

// Монстр начал движение в указанном направлении
void monsterMove(shared_ptr<Monster> monster, MoveDirection selectedDir);
