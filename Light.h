#pragma once
#include "freeglut.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"

class Light
{
public:

    // Конструкторы
    Light();
    Light(glm::vec4 position);
	Light(glm::vec3 pos);
    Light(float x, float y, float z);

    // Установка параметров
    void setPosition(glm::vec4 position);
	void setPosition(glm::vec3 pos);
    void setAmbient(glm::vec4 color);
    void setDiffuse(glm::vec4 color);
    void setSpecular(glm::vec4 color);

    // Применение параметров
    void apply(GLenum LightNumber = GL_LIGHT0);
private:

    // Параметры
    glm::vec4 position;
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 ambient;
};