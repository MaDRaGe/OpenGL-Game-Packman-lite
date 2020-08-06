#include "Light.h"

// Конструкторы
Light::Light() { position = vec4(5, 15, 5, 1);  }
Light::Light(vec4 position) { this->position = position;  }
Light::Light(vec3 pos) { this->position = vec4(pos.x, pos.y, pos.z, 1); }
Light::Light(float x, float y, float z) { position = vec4(x, y, z, 1); }

// Установка параметров освещения
void Light::setPosition(vec4 position){ this->position = position; }
void Light::setPosition(vec3 pos) { this->position = vec4(pos.x, pos.y, pos.z, 1); }
void Light::setAmbient(vec4 color){ this->ambient = color; }
void Light::setDiffuse(vec4 color) { this->diffuse = color; }
void Light::setSpecular(vec4 color) { this->specular = color; }

// Применение параметров освещения
void Light::apply(GLenum LightNumber)
{
    glEnable(LightNumber);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
    glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
    glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));

    glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(position));
}