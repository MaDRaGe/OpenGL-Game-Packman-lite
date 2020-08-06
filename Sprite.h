#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>

#include "glew.h"

#include <gl/GL.h>
#include <gl\GLU.h>
#include "freeglut.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"

#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

using namespace std;
using namespace glm;

class Sprite
{
public:
    static int screenWidth;
    static int screenHeight;

    // �����������
    Sprite();

    // ��������� �� �����
    void load(char* filename, bool flip = false);

    // ������� � ����� ������� ����
    void drawFromLeftUp(int x, int y);

    // ������� � ������ ������� ����
    void drawFromRightUp(int x, int y);

private:
    int width; // ������ �����������
    int height; // ������ �����������
    int format;
    int type;
    GLuint bufferID; // ����� ��������
};