#include "display.h"

void display()
{
    // Тест глубины
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Очищение буфера цвета и буфера глубины
    glClearColor(0, 0.02, 0.1, 0.7);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_LIGHTING);

    // Включить режим рассчета освещения
    // !!! Уменьшает производительность !!!
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    // Установка камеры
    camera.apply();

    // Установка источника света
    light.apply();

    displayNonTransparentObjects();

    displayTransparentObjects();
    
    // Изменить заголовок окна
    changeWindowTitle();

    // смена переднего и заднего буфера
    glutSwapBuffers();
}

// Изменить заголовок окна
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

// Вывод непрозрачных объектов
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
    for (int i = 0; i < 21; i++) // По горизонтали карты
    {
        for (int j = 0; j < 21; j++) // По вертикали карты
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
    if (!gameOver) // Игра окончена
    {
        hero->draw();
    }
    if (bomb->isInGame()) // Бомба установлена
    {
        bomb->draw();
    }
}

// Вывод полупрозрачных объектов
void displayTransparentObjects()
{
    // Вывести нелицевые грани
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

    // Вывести лицевые грани
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