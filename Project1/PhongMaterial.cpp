#include "PhongMaterial.h"

PhongMaterial::PhongMaterial()
{
}

void PhongMaterial::apply()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, value_ptr(ambient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, value_ptr(diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, value_ptr(specular));
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, value_ptr(emission));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
