
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Mesh.h"
#include "Project1/PhongMaterial.h"
#include "Project1/PhongMaterialWithTexture.h"
#include "GameObjectFactory.h"
#include "Light.h"
#include "Camera.h"
#include "GraphicObject.h"
#include "GameObject.h"
#include "Portal.h"
#include "Sprite.h"
#include "Bomb.h"
#include "Texture.h"
#include "Decal.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "freeglut.h"
#include "glm.hpp"
#include "gtx\string_cast.hpp"
#include <vector>
#include "Project1/AudioManager.h"
#include "Monster.h"

#define SPEED 5 // �������� ������������ ��������

#define FPS 120 // ������������ ���������� FPS

extern string msaa[];
extern string filterMode[];

extern int fps;
extern double simulationTime;
extern bool gameOver;

extern LARGE_INTEGER oldValue, newValue, counter;

// ����� ������������
extern int passabilityMap[21][21];

// ������� �������
extern GameObjectFactory gameObjectFactory;
extern shared_ptr<GameObject> gameObjects[21][21];
extern shared_ptr<GameObject> hero;
extern shared_ptr<GameObject> plane;

// ������
extern Camera camera;

// �������� �����
extern Light light;
extern Light lightHero;

// �������
extern Portal portal_1;
extern Portal portal_2;

// ���������� ���������
extern bool onMSAA;

// �������
extern shared_ptr<Sprite> bombIcon;
extern shared_ptr<Sprite> tick;

// Bombs
extern shared_ptr<Bomb> bomb;

// ������
extern std::vector<Decal> decals;

// ���������� ������
extern AudioManager audioManager;

// �������
extern vector<shared_ptr<Monster>> monsters;

// ������������� ���������� ������
void dataInit();