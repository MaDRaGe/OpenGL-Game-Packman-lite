#pragma once
#include <memory>
#include <map>
#include <string>
#include "Mesh.h"
#include "GameObject.h"
#include "Material.h"
#include "Project1/PhongMaterial.h"
#include "Project1/PhongMaterialWithTexture.h"
#include "Texture.h"
#include "GraphicObject.h"
#include "pugixml.hpp"
#include "Bomb.h"

using namespace std;
using namespace pugi;

enum GameObjectType
{
    PLANE_OBJECT,
    LIGHT_OBJECT,
    HEAVY_OBJECT,
    EDGE_OBJECT,
    MAIN_HERO_OBJECT,
    MONSTER_OBJECT,
    PORTAL_1_OBJECT,
    PORTAL_2_OBJECT,
    BOMB_OBJECT,
    MAX_OBJECT_COUNT
};

class GameObjectFactory
{
public:
    void init(string xmlFileName);

    // Создать игровой объект с заданными параметрами
    shared_ptr<GameObject> create
    (
        GameObjectType type,
        int x,
        int y
    );
    /*
        Параметры:
            type - тип игрового объекта
            x - координата по оси Х
            y - координата по оси Y
        Возвр:
            указатель на созданный игровой объект
    */
    
private:
    // Загрузить объект из узла
    bool initObject(GameObjectType type, xml_node node);

private:
    // Меши для каждого типа объекта
	map<string, Mesh> meshesUniq;
	map<GameObjectType, string> meshes;

    // Меши для каждого типа объекта
    Material* materials[MAX_OBJECT_COUNT];

};