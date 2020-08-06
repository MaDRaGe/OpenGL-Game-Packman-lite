#pragma once
#include <stdio.h>
#include "GraphicObject.h"
#include "Project1/PhongMaterialWithTexture.h"
#include "Texture.h"
#include "Mesh.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "freeglut.h"
#include "glm.hpp"

using namespace std;

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
    static shared_ptr<Texture> texture;
};