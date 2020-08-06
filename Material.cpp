#include "Material.h"

// Конструкторы
Material::Material() { }

void Material::setAmbient(string color) {
    stringstream newColor(color);
    newColor >> ambient.r;
    newColor >> ambient.g;
    newColor >> ambient.b;
    ambient.a = 1;
}
void Material::setDiffuse(string color) {
    stringstream newColor(color);
    newColor >> diffuse.r;
    newColor >> diffuse.g;
    newColor >> diffuse.b;
    newColor >> diffuse.a;
}
void Material::setSpecular(string color) {
    stringstream newColor(color);
    newColor >> specular.r;
    newColor >> specular.g;
    newColor >> specular.b;
    specular.a = 1;
}
void Material::setEmission(string color) {
    stringstream newColor(color);
    newColor >> emission.r;
    newColor >> emission.g;
    newColor >> emission.b;
    emission.a = 1;
}
void Material::setShininess(string color) {
    stringstream newColor(color);
    newColor >> shininess;
}

//  Загрузить параметры из файла
void Material::load(const char* filename)
{
    ifstream file(filename);
    string line, tmp;
    if (file.is_open()) // Файл открыть
    {
        while (!file.eof()) // До конца файла
        {
            file >> line;
            line.pop_back();

            if (line == "ambient") // Ambient
            {
                file >> ambient.r;
                file >> ambient.g;
                file >> ambient.b;
                file >> ambient.a;
            }

            if (line == "diffuse") // Diffuse
            {
                file >> diffuse.r;
                file >> diffuse.g;
                file >> diffuse.b;
                file >> diffuse.a;
            }

            if (line == "specular") // Specular
            {
                file >> specular.r;
                file >> specular.g;
                file >> specular.b;
                file >> specular.a;
            }

            if (line == "emission") // Emission
            {
                file >> emission.r;
                file >> emission.g;
                file >> emission.b;
                file >> emission.a;
            }

            if (line == "shininess") // Shininess
            {
                file >> shininess;
            }
            getline(file, tmp);
        }
    }

    file.close();
}

// Прозрачный?
bool Material::isTransparent()
{
    if (diffuse.a < 1)
    {
        return true;
    }
    return false;
}