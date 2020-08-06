#pragma once
#include "../Texture.h"
#include "../Material.h"
class PhongMaterialWithTexture :
    public Material
{
public:
    // Конструктор
    PhongMaterialWithTexture();
    PhongMaterialWithTexture(Texture* texture);
    PhongMaterialWithTexture(std::shared_ptr<Texture> texture);

    // Установить текстуру
    void setTexture(std::shared_ptr<Texture> texture);
   
    // Применить параметры
    void apply() override;

private:
    std::shared_ptr<Texture> texture;
};

