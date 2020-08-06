#include "PhongMaterialWithTexture.h"

PhongMaterialWithTexture::PhongMaterialWithTexture()
{
}

/*PhongMaterialWithTexture::PhongMaterialWithTexture(Texture* texture)
{
    this->texture = texture;
}*/

PhongMaterialWithTexture::PhongMaterialWithTexture(std::shared_ptr<Texture> texture)
{
    this->texture = texture;
}

void PhongMaterialWithTexture::setTexture(std::shared_ptr<Texture> texture)
{
    this->texture = texture;
}


void PhongMaterialWithTexture::apply()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, value_ptr(ambient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, value_ptr(diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, value_ptr(specular));
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, value_ptr(emission));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    texture->apply();
}
