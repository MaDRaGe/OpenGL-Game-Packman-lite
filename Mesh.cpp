#include "Mesh.h"

// �����������
Mesh::Mesh()
{
}

// ���������� �� ������
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

// ��������� ��� �� �����
void Mesh::load(string filename)
/*
    ���������:
        filename - ���� � �����
*/
{
    ifstream file(filename.c_str());
    string param, tmp;
    vector<vec3> v;  // �������������� ����������
    vector<vec3> vn; // ���������� ��������
    vector<vec3> vt; // ���������� ���������
    if (file.is_open()) // ���� ������
    {
		// ��������� ��������� ������� ����
        while (!file.eof()) // �� ����� �����
        {
            // �������������� ����������
			file >> param;
            if (param == "v")
            {
                vec3 newV;
                file >> newV.x;
                file >> newV.y;
                file >> newV.z;
                v.push_back(newV);
            }

            // ���������� ��������
            if (param == "vn")
            {
                vec3 newV;
                file >> newV.x;
                file >> newV.y;
                file >> newV.z;
                vn.push_back(newV);
            }

            // ���������� ����������
            if (param == "vt")
            {
                vec3 newV;
                file >> newV.x;
                file >> newV.y;
                file >> newV.z;
                vt.push_back(newV);
            }

            // ������� ���������� ���� ������
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

	// ������� ������
	glGenBuffers(2, buffers);

	// ��������� ���������� ��� � ������
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0].coord, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// �������� ������ �������
void Mesh::addNewVertex
    (
        string param, 
        vector<vec3>& v, 
        vector<vec3>& vn, 
        vector<vec3>& vt
    )
{
    auto it = vertexToIndex.find(param);
    if (it != vertexToIndex.end()) // ������� ��� �����������
    {
        indices.push_back(vertexToIndex[param]);
    }
    else
    {
        vertices.push_back(createVertex(param, v, vn, vt));
        vertexToIndex.insert(make_pair(param, vertexToIndex.size()));
        indices.push_back(vertexToIndex.size() - 1);
    }
}

// ������� �������
Vertex Mesh::createVertex
    (
        string param, 
        vector<vec3>& v, 
        vector<vec3>& vn, 
        vector<vec3>& vt
    )
{
    string index;    // ������ � ��������� �������
    int f;           // ������
    int i = 0;       // ������� ������� � ������
    Vertex newVertex;// ����� �������
    param.push_back('/');

    // �������������� ���������� �������
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

    // ���������� ����������
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
    /*cout 
        << "TEXCOORD: " 
        << newVertex.texCoord[0] << " " 
        << newVertex.texCoord[1] << " " 
        << newVertex.texCoord[2] << endl;*/

    // ���������� ��������
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
    /*cout
        << "NORMALS: "
        << newVertex.normal[0] << " "
        << newVertex.normal[1] << " "
        << newVertex.normal[2] << endl;*/
    return newVertex;
}