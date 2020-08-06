#include "Texture.h"
int Texture::textFilterMode = 0;

Texture::Texture()
{
}

// Загрузка текстуры из файла
void Texture::load(string filename)
/*
    Параметры:
        filename - путь к файлу
*/
{
    // Создать текстуру
    glGenTextures(1, &texIndex);
    glBindTexture(GL_TEXTURE_2D, texIndex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Загрузить изображение из файла
    ILuint imageId = ilGenImage();
    ilBindImage(imageId);
    wchar_t Unicode_string[256];
    wsprintf(Unicode_string, L"%S", filename.c_str());
    bool result = ilLoadImage(Unicode_string);
    printf("[LOAD TEXTURE STATUS = %d] %s\n", result, filename.c_str());
    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);
    int format = ilGetInteger(IL_IMAGE_FORMAT);
    int type = ilGetInteger(IL_IMAGE_TYPE);
    ILinfo ImageInfo;
    iluGetImageInfo(&ImageInfo);
    if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
    {
        iluFlipImage();
    }

    // Привязать изображение к созданной текстуре
    GLubyte* _texture = new GLubyte[width * height * 4];
    ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, GL_UNSIGNED_BYTE, _texture);
    ilDeleteImage(imageId);
    ilBindImage(0);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _texture);
    delete[] _texture;
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Включение текстурирования
void Texture::apply(GLenum texUnit)
/*
    Параметры:
        texUnit - идентификатор текстуры
*/
{
    glActiveTexture(texUnit);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texIndex);
    Texture::setFilterMode();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// Отключение текстурирования
void Texture::disableAll()
{
    glDisable(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

// Установка режима фильтрации
void Texture::setFilterMode()
{
    const GLenum filters[] = { GL_TEXTURE_MIN_FILTER,    GL_TEXTURE_MAG_FILTER, GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT };
    const GLuint filterMode[9][3] = {
    { GL_NEAREST,			    GL_NEAREST,	1 },  // 1)точечная;
    { GL_LINEAR,			    GL_LINEAR,  1 },  // 2)билинейная;
    { GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR,	1 },  // 3)
    { GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,	1 },  // 4)x1;
    { GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,	2 },  // 5)x2;
    { GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,	4 },  // 6)x4;
    { GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,	8 },  // 7)x8;
    { GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,	16 }, // 8)x16;
    { GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,	32 }, // 9)x32;
    };
    for (int i = 0; i < 3; i++)
    {
        glTexParameteri(GL_TEXTURE_2D, filters[i], filterMode[textFilterMode][i]);
    }
}

