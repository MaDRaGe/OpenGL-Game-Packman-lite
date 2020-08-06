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
    // ������������
    GraphicObject();
	GraphicObject(vec3, float);

    // ��������� ������� 
	void setPosition(vec3 &position);
	vec3 getPosition();

    // ��������� ���� �������� �� �����������
	void setAngle(float grad);
	float getAngle();

    // ���������� ��������
    void setMaterial(Material* material);

    // ���������� ���
    void setMesh(Mesh* mesh);

    // ������� ������ �� �����
	void draw();

    // ? ����������
    bool isTransparent();

private:
    // �������
	vec3 Position;

    // ���� �������� �� �����������
	float Angle;

    // ����
	vec3 Color;

    // ������� ������
    GLfloat ModelMatrix[16];

    // ��������
    Material* material;

    // ���
    Mesh* mesh;

    // ��������� ������� ������
	void recalculateModelMatrix();
};