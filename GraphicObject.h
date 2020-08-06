#pragma once
#include "Mesh.h"
#include "Material.h"
#include "freeglut.h"
#include "glm.hpp"

class GraphicObject
{
public:
    // Конструкторы
    GraphicObject();
	GraphicObject(glm::vec3, float);

    // Обработка позиции 
	void setPosition(glm::vec3 &position);
    glm::vec3 getPosition();

    // Обработка угла поворота по горизонтали
	void setAngle(float grad);
	float getAngle();

    // Установить материал
    void setMaterial(Material* material);

    // Установить меш
    void setMesh(Mesh* mesh);

    // Вывести объект на экран
	void draw();

    // ? Прозрачный
    bool isTransparent();

private:
    // Позиция
    glm::vec3 Position;

    // Угол поворота по горизонтали
	float Angle;

    // Цвет
    glm::vec3 Color;

    // Матрица модели
    GLfloat ModelMatrix[16];

    // Материал
    Material* material;

    // Меш
    Mesh* mesh;

    // Расчитать матрицу модели
	void recalculateModelMatrix();
};