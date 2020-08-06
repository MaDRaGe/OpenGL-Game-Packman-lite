#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>

#include "Mesh.h"
#include "Material.h"

#include <gl\GL.h>
#include <gl\GLU.h>
#include "freeglut.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"

using namespace glm;

class GraphicObject
{
public:
    // Конструкторы
    GraphicObject();
	GraphicObject(vec3, float);

    // Обработка позиции 
	void setPosition(vec3 &position);
	vec3 getPosition();

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
	vec3 Position;

    // Угол поворота по горизонтали
	float Angle;

    // Цвет
	vec3 Color;

    // Матрица модели
    GLfloat ModelMatrix[16];

    // Материал
    Material* material;

    // Меш
    Mesh* mesh;

    // Расчитать матрицу модели
	void recalculateModelMatrix();
};