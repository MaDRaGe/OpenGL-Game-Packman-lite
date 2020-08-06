#include "Sprite.h"
Sprite::Sprite(){

}

// Загрузить из файла
void Sprite::load(char* filename, bool flip)
{
    // Загрузить спрайт
    ILuint imageId = ilGenImage();
    ilBindImage(imageId);
    wchar_t Unicode_string[256];
    wsprintf(Unicode_string, L"%S", filename);
    bool rezult = ilLoadImage(Unicode_string);
    this->width = ilGetInteger(IL_IMAGE_WIDTH);
    height = ilGetInteger(IL_IMAGE_HEIGHT);
    format = ilGetInteger(IL_IMAGE_FORMAT);
    type = ilGetInteger(IL_IMAGE_TYPE);
    if (flip)
    {
        iluFlipImage();
    }


    // Загрузить спрайт в оперативную память
    ILubyte* _sprite = new ILubyte[width * height * 4];
    ilCopyPixels(0, 0, 0, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, _sprite);

    // Создать буфер
    glGenBuffers(1, &bufferID);

    // Загрузить спрайт в буфер
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, bufferID);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, _sprite, GL_DYNAMIC_COPY);
    ilDeleteImage(imageId);
    delete[] _sprite;
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

void Sprite::drawFromLeftUp(int x, int y)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glWindowPos2i(x, screenHeight - y);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, bufferID);
    glDrawPixels(width, height, format, type, 0);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    glDisable(GL_BLEND);
}

void Sprite::drawFromRightUp(int x, int y)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glWindowPos2i(screenWidth - x, screenHeight - y);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, bufferID);
    glDrawPixels(width, height, format, type, 0);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    glDisable(GL_BLEND);
}

int Sprite::screenHeight = 0;
int Sprite::screenWidth = 0;
