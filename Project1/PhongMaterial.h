#pragma once
#include "glm.hpp"
#include "../Material.h"
class PhongMaterial :
    public Material
{
public:
    // �����������
    PhongMaterial();

    // ��������� ���������
    void apply() override;
};

