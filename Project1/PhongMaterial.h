#pragma once
#include "freeglut.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
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

