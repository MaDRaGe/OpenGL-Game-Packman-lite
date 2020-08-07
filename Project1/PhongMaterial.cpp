#include "PhongMaterial.h"

PhongMaterial::PhongMaterial()
{
}

void PhongMaterial::apply()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emission));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
