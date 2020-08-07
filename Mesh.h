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
    GLfloat coord[3];    // ���������� ����������
    GLfloat normal[3];   // ������� �������
    GLfloat texCoord[2]; // ���������� ���������� �������� ����������� �����
};

class Mesh
{
public:
    Mesh(); // �����������
    void load(std::string filename); // ��������� ��� �� �����
    void draw(); // ������� ���

private:
    void addNewVertex // �������� ����� �������
        (
            std::string param,
            std::vector<glm::vec3>& v,
            std::vector<glm::vec3>& vn,
            std::vector<glm::vec3>& vt
        );
    Vertex createVertex // ������� �������
        (
            std::string,
            std::vector<glm::vec3>&,
            std::vector<glm::vec3>&,
            std::vector<glm::vec3>&
        );

private:
    std::vector<Vertex> vertices; // �������
    std::vector<GLuint> indices; // �������
    std::map<std::string,int> vertexToIndex;
	GLuint buffers[2]; // ������
};