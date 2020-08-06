#include "data.h"

// Карта проходимости
int passabilityMap[21][21] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 8, 0, 0, 0, 0, 0, 2, 0, 0, 5, 3,
    3, 0, 2, 1, 2, 0, 2, 0, 2, 2, 2, 1, 2, 0, 2, 0, 2, 0, 2, 2, 3,
    3, 0, 2, 6, 2, 0, 0, 0, 2, 0, 2, 6, 0, 0, 2, 0, 1, 0, 0, 0, 3,
    3, 0, 1, 0, 2, 2, 1, 2, 2, 0, 2, 0, 2, 2, 2, 1, 2, 0, 2, 0, 3,
    3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2, 0, 3,
    3, 0, 2, 2, 1, 1, 2, 0, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 0, 3,
    3, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 8, 0, 6, 2, 0, 0, 0, 0, 0, 3,
    3, 0, 2, 0, 2, 2, 2, 0, 2, 0, 2, 2, 1, 2, 2, 2, 1, 2, 2, 0, 3,
    3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 8, 3,
    3, 1, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 3,
    3, 0, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3,
    3, 0, 2, 0, 2, 2, 2, 0, 2, 1, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 3,
    3, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 3,
    3, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 1, 0, 2, 2, 2, 0, 3,
    3, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 1, 0, 0, 0, 2, 0, 3,
    3, 0, 2, 0, 2, 1, 2, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 3,
    3, 0, 1, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3,
    3, 0, 2, 1, 2, 0, 2, 2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 3,
    3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 5, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};
string msaa[] = { " [MSAA is on] ", " [MSAA is off] " };
string filterMode[] = {
    " [Точечная] ",
    " [Билинейная] ",
    " [Билинейная mipmap] ",
    " [Трилинейная] ",
    " [Анизотропная x2] ",
    " [Анизотропная x4] ",
    " [Анизотропная x8] ",
    " [Анизотропная x16] ",
    " [Анизотропная x32] " };
int fps;
double simulationTime;
bool gameOver = false;

LARGE_INTEGER oldValue, newValue, counter;

// Игровые объекты
GameObjectFactory gameObjectFactory;
shared_ptr<GameObject> gameObjects[21][21];
shared_ptr<GameObject> hero;
shared_ptr<GameObject> plane;

// Камера и источник света
Camera camera;
Light light;
Light lightHero;

// Порталы
Portal portal_1;
Portal portal_2;

// Спрайты
shared_ptr<Sprite> bombIcon = make_shared<Sprite>();
shared_ptr<Sprite> tick = make_shared<Sprite>();

// Bombs
shared_ptr<Bomb> bomb = make_shared<Bomb>();

vector<shared_ptr<Monster>> monsters;

// Декали 
std::vector<Decal> decals;

// Обработчик звуков
AudioManager audioManager;

// Глобальные настройки
bool onMSAA;

// Инициализация глобальных данных
void dataInit()
{
    // Свет
    light.setAmbient(vec4(0.3, 0.3, 0.3, 0.5));
    light.setPosition(vec4(0, 30, 0, 1));
    light.setSpecular(vec4(1, 1, 1, 1));
    light.setDiffuse(vec4(0.7, 0.7, 0.7, 0.5));

    // Игровые объекты
    gameObjectFactory.init("../scene.xml");
    plane = gameObjectFactory.create(PLANE_OBJECT, 10, 10);
    plane->high = 0;
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			switch (passabilityMap[i][j])
			{
            case 8:
                gameObjects[i][j] = gameObjectFactory.create(MONSTER_OBJECT, i, j);
                monsters.push_back(make_shared<Monster>(gameObjects[i][j]));
                break;

            case 6:
                portal_2.add(ivec2(i, j));
                gameObjects[i][j] = gameObjectFactory.create(PORTAL_2_OBJECT, i, j);
                break;

            case 5:
                portal_1.add(ivec2(i, j));
                gameObjects[i][j] = gameObjectFactory.create(PORTAL_1_OBJECT, i, j);
                break;

			case 3:
                gameObjects[i][j] = gameObjectFactory.create(EDGE_OBJECT, i, j);
				break;

			case 2:
                gameObjects[i][j] = gameObjectFactory.create(HEAVY_OBJECT, i, j);
				break;

			case 1:
                gameObjects[i][j] = gameObjectFactory.create(LIGHT_OBJECT, i, j);
				break;

            default:
                gameObjects[i][j] = nullptr;
                break;
			}
		}
	}

    // Игрок
    hero = gameObjectFactory.create(MAIN_HERO_OBJECT, 1, 1);
    lightHero.setAmbient(vec4(0, 0, 0, 1));
    lightHero.setSpecular(vec4(0.5, 0.5, 0.5, 1));
    lightHero.setDiffuse(vec4(1, 1, 1, 1));
    vec3 pos = hero->getGraphicPosition();
    lightHero.setPosition(pos);

    // Бомба
    bombIcon->load("../SPRITES/Bomb.ico");
    tick->load("../SPRITES/BombTick.tga");
    bomb->setHUD(bombIcon, tick);
    bomb->setGameObject(gameObjectFactory.create(BOMB_OBJECT, 0, 0));
    Decal::init();
    audioManager.init();
}

