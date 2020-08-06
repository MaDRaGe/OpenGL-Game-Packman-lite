#pragma once
#include "freeglut.h"
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"

class Camera{
public:
    // ������������
	Camera();
	Camera(glm::vec3 position);
	Camera(float x, float y, float z);

    // ��������� ���������
    void calcPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();

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
    glm::vec3 position;

    // ���� �������� �� �����������
	float angleA;

    // ���� �������� �� ���������
    float angleB;

    // ���������� �� ������ �����
	float distance;
};