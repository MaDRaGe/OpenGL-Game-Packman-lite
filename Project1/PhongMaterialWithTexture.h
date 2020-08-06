#pragma once
#include "../Texture.h"
#include "../Material.h"
class PhongMaterialWithTexture :
    public Material
{
public:
    // �����������
    PhongMaterialWithTexture();
    PhongMaterialWithTexture(Texture* texture);
    PhongMaterialWithTexture(std::shared_ptr<Texture> texture);

    // ���������� ��������
    void setTexture(std::shared_ptr<Texture> texture);
   
    // ��������� ���������
    void apply() override;

private:
    std::shared_ptr<Texture> texture;
};

