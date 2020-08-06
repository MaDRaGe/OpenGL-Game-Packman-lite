#pragma once
#include "glm.hpp"
#include "../Material.h"
class PhongMaterial :
    public Material
{
public:
    // Конструктор
    PhongMaterial();

    // Применить параметры
    void apply() override;
};

