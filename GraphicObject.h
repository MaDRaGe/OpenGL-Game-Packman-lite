#pragma once
#include "Mesh.h"
#include "Material.h"
#include "freeglut.h"
#include "glm.hpp"

class GraphicObject
{
public:
    // ������������
    GraphicObject();
	GraphicObject(glm::vec3, float);

    // ��������� ������� 
	void setPosition(glm::vec3 &position);
    glm::vec3 getPosition();

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
    glm::vec3 Position;

    // ���� �������� �� �����������
	float Angle;

    // ����
    glm::vec3 Color;

    // ������� ������
    GLfloat ModelMatrix[16];

    // ��������
    Material* material;

    // ���
    Mesh* mesh;

    // ��������� ������� ������
	void recalculateModelMatrix();
};