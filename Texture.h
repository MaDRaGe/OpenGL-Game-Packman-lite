#pragma once

#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>

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

class Texture
{
public:
    Texture();
    void load(string filename);
    void apply(GLenum texUnit = GL_TEXTURE0);
    static void disableAll();
    void setFilterMode();

    static int textFilterMode;

private:
    GLuint texIndex;
};
