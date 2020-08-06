#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include "glm.hpp"

class Material
{
public:
    // �����������
    Material();

    // ���������� �������� ���������
    void setAmbient(glm::vec4 color);
    void setDiffuse(glm::vec4 color);
    void setSpecular(glm::vec4 color);
    void setEmission(glm::vec4 color);
    void setShininess(float p);
    void setAmbient(std::string color);
    void setDiffuse(std::string color);
    void setSpecular(std::string color);
    void setEmission(std::string color);
    void setShininess(std::string p);

    // ��������� �������� �� �����
    void load(const char* filename);

    // ��������� � OpenGL
    virtual void apply() = 0;

    // ��������������?
    bool isTransparent();
protected:

    // ���������
    glm::vec4 diffuse; 
    glm::vec4 specular;
    glm::vec4 ambient;
    glm::vec4 emission;
    float shininess;

};