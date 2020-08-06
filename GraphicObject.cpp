#include "GraphicObject.h"
using namespace std;

// ������������
GraphicObject::GraphicObject()
{
    this->Position = vec3(0, 0, 0);
    this->Angle = 0;
    this->Color = vec3(0, 0, 0);
    this->material = nullptr;
    this->mesh = nullptr;
    ModelMatrix[0] = 1;
    ModelMatrix[5] = 1;
    ModelMatrix[10] = 1;
    ModelMatrix[15] = 1;
}
GraphicObject::GraphicObject(
    vec3 pos, 
    float angle
)
/*
    Params: 
        pos - object position
        angle - object horizontal rotate angle
*/
{
	Position = pos;
    Angle = angle;
    ModelMatrix[0] = 1;
    ModelMatrix[5] = 1;
    ModelMatrix[10] = 1;
    ModelMatrix[15] = 1;
    recalculateModelMatrix();
}

// Handle object position
void GraphicObject::setPosition(vec3 &pos)
/*
    Params:
        pos - object position
*/
{
	Position = pos;
	recalculateModelMatrix();
}
vec3 GraphicObject::getPosition()
{
	return Position;
}

// Handle object angle
void GraphicObject::setAngle(float angle)
/*
    params:
        angle - object horizontal rotate angle
*/
{
	Angle = angle;
	GraphicObject::recalculateModelMatrix();
}
float GraphicObject::getAngle()
{
	return Angle;
}

// ���������� �������� �������
void GraphicObject::setMaterial(Material* material)
{
    this->material = material;
}

void GraphicObject::setMesh(Mesh* mesh)
{
    this->mesh = mesh;
}

// ������ ������� ������
void GraphicObject::recalculateModelMatrix()
{
    GraphicObject::ModelMatrix[0] = cos(Angle * 3.14 / 180);
    GraphicObject::ModelMatrix[2] = sin(Angle * 3.14 / 180);

    GraphicObject::ModelMatrix[8] = -sin(Angle * 3.14 / 180);
    GraphicObject::ModelMatrix[10] = cos(Angle * 3.14 / 180);

    GraphicObject::ModelMatrix[12] = GraphicObject::Position.x;
    GraphicObject::ModelMatrix[13] = GraphicObject::Position.y;
    GraphicObject::ModelMatrix[14] = GraphicObject::Position.z;
}

// ������� ������ �� �����
void GraphicObject::draw()
{
	// ��������� ������� ������� ���������� ������ � �����
    glPushMatrix();

	// �������� ������� ������ �� ������� ������� ���������� ������
	glMultMatrixf(ModelMatrix);

    if (material != nullptr) // �������� ����������
    {
        // ��������� ��������
        material->apply();
    }

	// ������� ������ �� �����
    if (mesh != nullptr) // mesh has been set
    {
        mesh->draw();
    }

	// ������������ ������� ���������� ������
	glPopMatrix();
}

bool GraphicObject::isTransparent() {
	return material->isTransparent();
}