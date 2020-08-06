#pragma once
#include "GraphicObject.h"
#include "Project1/PhongMaterialWithTexture.h"
#include "Texture.h"
#include "Mesh.h"
#include "freeglut.h"
#include "glm.hpp"

class Decal
{
public:
    // Инициализация
    static void init();
    
    // Конструкторы
    Decal();
    Decal(glm::ivec2 position);

    // Установить позицию
    void setPosition(glm::ivec2 position);

    // Получить позицию
    glm::ivec2 getPosition() const;

    // Вывести на экран
    void draw();

private:
    GraphicObject graphicObject; // Графический объект
    glm::ivec2 position; // Позиция

    static PhongMaterialWithTexture material;
    static Mesh mesh;
    static std::shared_ptr<Texture> texture;
};