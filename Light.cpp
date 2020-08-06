#include "Light.h"

// Конструкторы
Light::Light() 
{ 
    position = glm::vec4(5, 15, 5, 1);  
}
Light::Light(glm::vec4 position) 
{ 
    this->position = position;  
}
Light::Light(glm::vec3 pos) 
{ 
    this->position = glm::vec4(pos.x, pos.y, pos.z, 1); 
}
Light::Light(float x, float y, float z) 
{ 
    position = glm::vec4(x, y, z, 1);
}

// Установка параметров освещения
void Light::setPosition(glm::vec4 position)
{ 
    this->position = position; 
}
void Light::setPosition(glm::vec3 pos) 
{ 
    this->position = glm::vec4(pos.x, pos.y, pos.z, 1);
}
void Light::setAmbient(glm::vec4 color)
{ 
    this->ambient = color; 
}
void Light::setDiffuse(glm::vec4 color) 
{ 
    this->diffuse = color; 
}
void Light::setSpecular(glm::vec4 color) 
{ 
    this->specular = color; 
}

// Применение параметров освещения
void Light::apply(GLenum LightNumber)
{
    glEnable(LightNumber);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(diffuse));
    glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(specular));
    glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(ambient));
    glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));
}