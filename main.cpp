#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

#include "glew.h"

#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#include <gl/GL.h>
#include "freeglut.h"
#include "glm.hpp"
#include "gtx/string_cast.hpp"

#include "data.h"
#include "simulation.h"
#include "display.h"
#include "Sprite.h"

#include "al.h"
#include "alc.h"

using namespace glm;
using namespace std;

// Изменение размера окна
void Reshape(int w, int h){

	// установка новой области просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);

    Sprite::screenHeight = (int)h;
    Sprite::screenWidth = (int)w;
}

void main(void){

	// инициализации библиотеки
	glutInit(&__argc, __argv);

	// Определить контекст рендеринга
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitContextVersion(4, 0);
    glEnable(GL_MULTISAMPLE);
    onMSAA = true;

	// Создать окно
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1600, 1000);
	glutCreateWindow("OpenGL Intr");
	glewInit();

	// Регистрация функций обратного вызова
	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	QueryPerformanceCounter(&oldValue);
	QueryPerformanceFrequency(&counter);
    glutKeyboardFunc(keyPress);
	glutIdleFunc(simulation);

    ilInit();
    iluInit();
    ilutInit();

    ALCdevice* device = nullptr;
    device = alcOpenDevice(nullptr);
    ALCcontext* context = nullptr;
    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);

	dataInit();
	glutMainLoop();
}
