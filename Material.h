#pragma once
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <gl/GL.h>
#include <gl/GLU.h>
#include "freeglut.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"

using namespace glm;
using namespace std;

class Material
{
public:
    // �����������
    Material();

    // ���������� �������� ���������
    void setAmbient(vec4 color);
    void setDiffuse(vec4 color);
    void setSpecular(vec4 color);
    void setEmission(vec4 color);
    void setShininess(float p);
    void setAmbient(string color);
    void setDiffuse(string color);
    void setSpecular(string color);
    void setEmission(string color);
    void setShininess(string p);

    // ��������� �������� �� �����
    void load(const char* filename);

    // ��������� � OpenGL
    virtual void apply() = 0;

    // ��������������?
    bool isTransparent();
protected:

    // ���������
    vec4 diffuse; 
    vec4 specular;
    vec4 ambient;
    vec4 emission;
    float shininess;

};