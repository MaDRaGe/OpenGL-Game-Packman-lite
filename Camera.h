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
    // ������������
	Camera();
	Camera(vec3 position);
	Camera(float x, float y, float z);

    // ��������� ���������
    void calcPosition();
	void setPosition(vec3 position);
	vec3 getPosition();

    // ��������� ���� �� �����������
    void setAngleA(float degree);
    void calcAngleA();
    float getAngleA();

    // ��������� ���� �� ���������
    void setAngleB(float degree);
    void calcAngleB();
    float getAngleB();

    // ��������� ���������� �� ������ ���������
    void calcDistance();
    void setDistance(float);
    float getDistance();

    // ��������� ������ �� �����������
	void rotateLeftRight(float degree);

    // ��������� ������ �� ���������
	void rotateUpDown(float degree);

    // �������� ������ �� ������ �����
	void zoomInOut(float distance);

    // ���������� �������� ������
	void apply();

private:
    // ��������� ������
	vec3 position;

    // ���� �������� �� �����������
	float angleA;

    // ���� �������� �� ���������
    float angleB;

    // ���������� �� ������ �����
	float distance;
};