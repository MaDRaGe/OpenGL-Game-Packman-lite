
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

#define SPEED 5 // Скорость передвижения объектов

#define FPS 120 // Максимальное количество FPS

extern string msaa[];
extern string filterMode[];

extern int fps;
extern double simulationTime;
extern bool gameOver;

extern LARGE_INTEGER oldValue, newValue, counter;

// Карта проходимости
extern int passabilityMap[21][21];

// Игровые объекты
extern GameObjectFactory gameObjectFactory;
extern shared_ptr<GameObject> gameObjects[21][21];
extern shared_ptr<GameObject> hero;
extern shared_ptr<GameObject> plane;

// Камера
extern Camera camera;

// Источник света
extern Light light;
extern Light lightHero;

// Порталы
extern Portal portal_1;
extern Portal portal_2;

// Глобальные настройки
extern bool onMSAA;

// Спрайты
extern shared_ptr<Sprite> bombIcon;
extern shared_ptr<Sprite> tick;

// Bombs
extern shared_ptr<Bomb> bomb;

// Декали
extern std::vector<Decal> decals;

// Обработчик звуков
extern AudioManager audioManager;

// Монстры
extern vector<shared_ptr<Monster>> monsters;

// Инициализация глобальных данных
void dataInit();