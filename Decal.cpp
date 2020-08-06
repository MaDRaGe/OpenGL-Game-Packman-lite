#include "Decal.h"

PhongMaterialWithTexture Decal::material;
Mesh Decal::mesh;
shared_ptr<Texture> Decal::texture = make_shared<Texture>();

// �������������
void Decal::init()
{
    // ��������� ������ �� �����
    mesh.load("../MESHES/Decal.obj");
    texture->load("../TEXTURES/decal.png");
    material.load("../MATERIALS/decal_material.txt");
    material.setTexture(texture);
}

// �����������
Decal::Decal()
{
    this->position = glm::ivec2(0, 0);
    graphicObject.setMaterial(&material);
    graphicObject.setMesh(&mesh);
    graphicObject.setPosition(glm::vec3(-10, 0, -10));
}

// ���������� �������
Decal::Decal(glm::ivec2 position)
/*
    ���������:
        position - �������
*/
{
    this->position = position;
    graphicObject.setMaterial(&material);
    graphicObject.setMesh(&mesh);
    graphicObject.setPosition(glm::vec3(position.x - 10, 0.001, position.y - 10));
}

// ���������� ����������
void Decal::setPosition(glm::ivec2 position)
/*
    ���������:
        position - ����������
*/
{
    this->position = position;
}

// ��������� ���������
glm::ivec2 Decal::getPosition() const
/*
    ������������ ��������:
        ���������� ������
*/
{
    return this->position;
}

// ���������� �� ������
void Decal::draw()
{
    glEnable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_BLEND);
    glPolygonOffset(-1, -3);
    graphicObject.draw();
    glDisable(GL_BLEND);
    glDisable(GL_POLYGON_OFFSET_FILL);
}