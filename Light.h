#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>

#include <gl/GL.h>
#include <gl\GLU.h>
#include "freeglut.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"

using namespace glm;

class Light
{
public:

    // Конструкторы
    Light();
    Light(vec4 position);
	Light(vec3 pos);
    Light(float x, float y, float z);

    // Установка параметров
    void setPosition(vec4 position);
	void setPosition(vec3 pos);
    void setAmbient(vec4 color);
    void setDiffuse(vec4 color);
    void setSpecular(vec4 color);

    // Применение параметров
    void apply(GLenum LightNumber = GL_LIGHT0);
private:

    // Параметры
    vec4 position;
    vec4 diffuse;
    vec4 specular;
    vec4 ambient;
};