#include "Mesh.h"

// Конструктор
Mesh::Mesh()
{
}

// Отобразить на экране
void Mesh::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, coord));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Загрузить меш из файла
void Mesh::load(std::string filename)
/*
    Параметры:
        filename - путь к файлу
*/
{
    std::ifstream file(filename.c_str());
    std::string param, tmp;
    std::vector<glm::vec3> v;  // Геометрические координаты
    std::vector<glm::vec3> vn; // Координаты нормалей
    std::vector<glm::vec3> vt; // Текстурные коорднаты
    if (file.is_open()) // Файл открыт
    {
		// Загрузить параметры вершины меша
        while (!file.eof()) // До конца файла
        {
            // Геометрические координаты
			file >> param;
            if (param == "v")
            {
                glm::vec3 newV;
                file >> newV.x;
                file >> newV.y;
                file >> newV.z;
                v.push_back(newV);
            }

            // Координаты нормалей
            if (param == "vn")
            {
                glm::vec3 newV;
                file >> newV.x;
                file >> newV.y;
                file >> newV.z;
                vn.push_back(newV);
            }

            // Текстурные координаты
            if (param == "vt")
            {
                glm::vec3 newV;
                file >> newV.x;
                file >> newV.y;
                file >> newV.z;
                vt.push_back(newV);
            }

            // Индексы параметров трех вершин
            if (param == "f")
            {
                file >> param;
                addNewVertex(param, v, vn, vt);
                file >> param;
                addNewVertex(param, v, vn, vt);
                file >> param;
                addNewVertex(param, v, vn, vt);
            }
            getline(file, tmp);
        }
    }
    file.close();

	// Создать буферы
	glGenBuffers(2, buffers);

	// Загрузить полученный меш в буферы
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0].coord, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Добавить индекс вершины
void Mesh::addNewVertex
    (
        std::string param,
        std::vector<glm::vec3>& v,
        std::vector<glm::vec3>& vn,
        std::vector<glm::vec3>& vt
    )
{
    auto it = vertexToIndex.find(param);
    if (it != vertexToIndex.end()) // Вершина уже встречалась
    {
        indices.push_back(vertexToIndex[param]);
    }
    else
    {
        vertices.push_back(createVertex(param, v, vn, vt));
        vertexToIndex.insert(std::make_pair(param, vertexToIndex.size()));
        indices.push_back(vertexToIndex.size() - 1);
    }
}

// Создать вершину
Vertex Mesh::createVertex
    (
        std::string param,
        std::vector<glm::vec3>& v,
        std::vector<glm::vec3>& vn,
        std::vector<glm::vec3>& vt
    )
{
    std::string index;    // Индекс в строковом формате
    int f;           // Индекс
    int i = 0;       // Позиция курсора в строке
    Vertex newVertex;// Новая вершина
    param.push_back('/');

    // Геометрические координаты вершины
    index = "";
    while (param[i] != '/')
    {
        index += param[i];
        i++;
    }
    i++;
    f = stoi(index);
    newVertex.coord[0] = v[f - 1].x;
    newVertex.coord[1] = v[f - 1].y;
    newVertex.coord[2] = v[f - 1].z;

    // Текстурные координаты
    index = "";
    while (param[i] != '/')
    {
        index += param[i];
        i++;
    }
    i++;
    f = stoi(index);
    newVertex.texCoord[0] = vt[f - 1].x;
    newVertex.texCoord[1] = vt[f - 1].y;
    //newVertex.texCoord[2] = vt[f - 1].z;

    // Координаты нормалей
    index = "";
    while (param[i] != '/')
    {
        index += param[i];
        i++;
    }
    f = stoi(index);
    newVertex.normal[0] = vn[f - 1].x;
    newVertex.normal[1] = vn[f - 1].y;
    newVertex.normal[2] = vn[f - 1].z;
    return newVertex;
}