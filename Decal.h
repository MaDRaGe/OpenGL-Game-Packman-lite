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
    // �������������
    static void init();
    
    // ������������
    Decal();
    Decal(glm::ivec2 position);

    // ���������� �������
    void setPosition(glm::ivec2 position);

    // �������� �������
    glm::ivec2 getPosition() const;

    // ������� �� �����
    void draw();

private:
    GraphicObject graphicObject; // ����������� ������
    glm::ivec2 position; // �������

    static PhongMaterialWithTexture material;
    static Mesh mesh;
    static shared_ptr<Texture> texture;
};