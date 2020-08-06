
#include "data.h"

void simulation();
double getSimulationTime();

// ����� �����
void killHero();

// ����������� ������ �� ������� �������
void cameraSimulation();

// ����������� ����� �� ������� �������
void objectSimulation(float);

// ��������� ������� �������
void keyPress(unsigned char key, int x, int y);

// ������ ��������
void portalSimulation();

// ������ �����
void bombSimulation(float);

// �������
void monstersSimulation(float simulationTime);

// ���������� ����������� ��������
MoveDirection selectMoveDirection(shared_ptr<Monster> monster);

// ������ ����� �������� � ��������� �����������
void monsterMove(shared_ptr<Monster> monster, MoveDirection selectedDir);
