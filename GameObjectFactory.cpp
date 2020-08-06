#include "GameObjectFactory.h"

// Инициализация объектов из xml-файла
void GameObjectFactory::init(string xmlFileName)
/*
    Параметры:
        xmlFileName - путь к xml-файлу
*/
{
    // Загрузка xml-файла
    cout << "[PROJECT FACTORY INIT]" << endl;
    xml_document doc;
    doc.load_file(xmlFileName.c_str());
    xml_node root = doc.child("AllObjectsDescription");

    // Инициализация объектов
    initObject(    PLANE_OBJECT, root.child("Plane"));
    initObject(    LIGHT_OBJECT, root.child("LightObject"));
    initObject(    HEAVY_OBJECT, root.child("HeavyObject"));
    initObject(     EDGE_OBJECT, root.child("BorderObject"));
    initObject(MAIN_HERO_OBJECT, root.child("PlayerObject"));
    initObject( PORTAL_1_OBJECT, root.child("Portal_1_Object"));
    initObject( PORTAL_2_OBJECT, root.child("Portal_2_Object"));
    initObject(  MONSTER_OBJECT, root.child("MonsterObject"));
    initObject(     BOMB_OBJECT, root.child("BombObject"));
}

// Создать объект
shared_ptr<GameObject> GameObjectFactory::create
    (
        GameObjectType type, 
        int x, 
        int y
    )
/*
    Параметры:
        type - тип объекта
        x, y - координаты объекта
        
    Возвращаемое значение:
        Указатель на созданный объект
*/
{
    shared_ptr<GameObject> newObject(new GameObject);
    newObject->setPosition(x, y);
    GraphicObject go;
    go.setMaterial(materials[type]);
    go.setMesh(&meshesUniq[meshes[type]]);
    newObject->setGraphicObject(go);
    return newObject;
}

// Загрузить объект
bool GameObjectFactory::initObject
    (
        GameObjectType type, 
        xml_node node
    )
/*
    Параметры:
        type - тип объекта
        node - узел xml с данными
        
    Возвращаемое значение:
        true - загрузка прошла успешно
*/
{
    // Загрузка меша
    xml_attribute meshFileName = node.child("Mesh").attribute("FileName");
	map<string, Mesh>::iterator IT = meshesUniq.find(string(meshFileName.value()));
	if (IT == meshesUniq.end()) // Меш отсутствует
	{
        cout << "[LOAD MESH]" << endl;
		meshes.insert(pair<GameObjectType, string>(type, string(meshFileName.value())));
		meshesUniq[string(meshFileName.value())].load("../MESHES/" + string(meshFileName.value()));
	}
	else // Меш уже был загружен
	{
		meshes[type] = string(meshFileName.value());
	}

    // Загрузка материала
    xml_node material = node.child("Material");
    if (!strcmp(material.attribute("Type").value(), "PhongMaterialWithTexture")) // Материал с текстурой
    {
        string texturePath = material.child("Texture").attribute("FileName").value();
        shared_ptr<Texture> texture = make_shared<Texture>();
        texture->load(string("../TEXTURES/" + texturePath));
        materials[type] = new PhongMaterialWithTexture(texture);
    }
    else
    {
        materials[type] = new PhongMaterial();
    }
    xml_node phongParam = material.child("PhongParameters");
    materials[type]->setDiffuse(string(phongParam.attribute("diffuse").value()));
    materials[type]->setAmbient(string(phongParam.attribute("ambient").value()));
    materials[type]->setSpecular(string(phongParam.attribute("specular").value()));
    materials[type]->setEmission(string(phongParam.attribute("emission").value()));
    materials[type]->setShininess(string(phongParam.attribute("shininess").value()));
    return true;
}