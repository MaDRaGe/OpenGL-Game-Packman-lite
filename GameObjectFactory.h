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

    // ������� ������� ������ � ��������� �����������
    shared_ptr<GameObject> create
    (
        GameObjectType type,
        int x,
        int y
    );
    /*
        ���������:
            type - ��� �������� �������
            x - ���������� �� ��� �
            y - ���������� �� ��� Y
        �����:
            ��������� �� ��������� ������� ������
    */
    
private:
    // ��������� ������ �� ����
    bool initObject(GameObjectType type, xml_node node);

private:
    // ���� ��� ������� ���� �������
	map<string, Mesh> meshesUniq;
	map<GameObjectType, string> meshes;

    // ���� ��� ������� ���� �������
    Material* materials[MAX_OBJECT_COUNT];

};