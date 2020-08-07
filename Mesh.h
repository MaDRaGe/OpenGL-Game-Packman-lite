#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"

struct Vertex
{
    GLfloat coord[3];    // Текстурные координаты
    GLfloat normal[3];   // Векторы нормали
    GLfloat texCoord[2]; // Текстурные координаты нулевого текстурного блока
};

class Mesh
{
public:
    Mesh(); // Конструктор
    void load(std::string filename); // Загрузить меш из файла
    void draw(); // Вывести меш

private:
    void addNewVertex // Добавить новую вершину
        (
            std::string param,
            std::vector<glm::vec3>& v,
            std::vector<glm::vec3>& vn,
            std::vector<glm::vec3>& vt
        );
    Vertex createVertex // Создать вершину
        (
            std::string,
            std::vector<glm::vec3>&,
            std::vector<glm::vec3>&,
            std::vector<glm::vec3>&
        );

private:
    std::vector<Vertex> vertices; // Вершины
    std::vector<GLuint> indices; // Индексы
    std::map<std::string,int> vertexToIndex;
	GLuint buffers[2]; // Буферы
};