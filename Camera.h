#pragma once
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <cmath>

#include <gl\GL.h>
#include <gl\GLU.h>
#include "freeglut.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"

using namespace glm;

class Camera{
public:
    // Конструкторы
	Camera();
	Camera(vec3 position);
	Camera(float x, float y, float z);

    // Обработка положения
    void calcPosition();
	void setPosition(vec3 position);
	vec3 getPosition();

    // Обработка угла по горизонтали
    void setAngleA(float degree);
    void calcAngleA();
    float getAngleA();

    // Обработка угла по вертикали
    void setAngleB(float degree);
    void calcAngleB();
    float getAngleB();

    // Обработка расстояния от начала координат
    void calcDistance();
    void setDistance(float);
    float getDistance();

    // Повернуть камеру по горизонтали
	void rotateLeftRight(float degree);

    // Повернуть камеру по вертикали
	void rotateUpDown(float degree);

    // Отдалить камеру от центра сцены
	void zoomInOut(float distance);

    // Применение настроек камеры
	void apply();

private:
    // Положение камеры
	vec3 position;

    // Угол поворота по горизонтали
	float angleA;

    // Угол поворота по вертикали
    float angleB;

    // Расстояние до центра сцены
	float distance;
};