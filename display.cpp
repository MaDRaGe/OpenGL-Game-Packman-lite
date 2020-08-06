#include "display.h"

void display()
{
    // ���� �������
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // �������� ������ ����� � ������ �������
    glClearColor(0, 0.02, 0.1, 0.7);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_LIGHTING);

    // �������� ����� �������� ���������
    // !!! ��������� ������������������ !!!
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    // ��������� ������
    camera.apply();

    // ��������� ��������� �����
    light.apply();

    displayNonTransparentObjects();

    displayTransparentObjects();
    
    // �������� ��������� ����
    changeWindowTitle();

    // ����� ��������� � ������� ������
    glutSwapBuffers();
}

// �������� ��������� ����
void changeWindowTitle()
{
    fps = (int)(1 / simulationTime);
    stringstream str;
    str << fps;
    string title = "FPS: " + str.str();
    string MSAAmsg = msaa[onMSAA];
    title += MSAAmsg;
    string filter = filterMode[Texture::textFilterMode];
    title += filter;
    glutSetWindowTitle((char*)title.c_str());
}

// ����� ������������ ��������
void displayNonTransparentObjects()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDisable(GL_BLEND);
    Texture::disableAll();
    plane->draw();
    for (auto IT = decals.begin(); IT != decals.end(); IT++)
    {
        IT->draw();
    }
    for (int i = 0; i < 21; i++) // �� ����������� �����
    {
        for (int j = 0; j < 21; j++) // �� ��������� �����
        {
            if (    gameObjects[i][j] != nullptr
                 && !gameObjects[i][j]->isTransparent()
               )
            {
                gameObjects[i][j]->draw();
            }
        }
    }
    Texture::disableAll();
    if (!gameOver) // ���� ��������
    {
        hero->draw();
    }
    if (bomb->isInGame()) // ����� �����������
    {
        bomb->draw();
    }
}

// ����� �������������� ��������
void displayTransparentObjects()
{
    // ������� ��������� �����
    glDepthMask(GL_FALSE);
    glCullFace(GL_FRONT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (   gameObjects[i][j] != nullptr
                 && gameObjects[i][j]->isTransparent()
               )
            {
                gameObjects[i][j]->draw();
            }
        }
    }

    // ������� ������� �����
    glCullFace(GL_BACK);
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (    gameObjects[i][j] != nullptr
                 && gameObjects[i][j]->isTransparent()
               )
            {
                gameObjects[i][j]->draw();
            }
        }
    }
    glDisable(GL_BLEND);
}