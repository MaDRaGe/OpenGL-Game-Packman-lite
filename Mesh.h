#pragma once
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "glew.h"

#include <gl/GL.h>
#include "freeglut.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"

using namespace std;
using namespace glm;

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
    void load(string filename); // Загрузить меш из файла
    void draw(); // Вывести меш

private:
    void addNewVertex // Добавить новую вершину
        (
            string param, 
            vector<vec3>& v, 
            vector<vec3>& vn,
            vector<vec3>& vt
        );
    Vertex createVertex // Создать вершину
        (
            string, 
            vector<vec3>&, 
            vector<vec3>&, 
            vector<vec3>&
        );

private:
    vector<Vertex> vertices; // Вершины
    vector<GLuint> indices; // Индексы
    map<string,int> vertexToIndex;
	GLuint buffers[2]; // Буферы
};