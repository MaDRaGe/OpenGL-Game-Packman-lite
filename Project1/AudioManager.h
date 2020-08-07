#pragma once
#include "freeglut.h"
#include "glm.hpp"
#include "al.h"
#include "alc.h"

enum SoundType 
{
    AMBIENT,
    DEATH,
    EXPLOSION,
    PORTAL,
    SHIFT,
    MAX_SOUND_COUNT
};

// Заголовок wav-файла
#pragma pack (push, 1)
struct wave_chunc_header 
{
    unsigned __int8 id[4]; // идентификатор чанка
    unsigned __int32 size; // Размер оставшейся части чанка
};
#pragma pack (pop)

// Формат аудиоданных
#pragma pack (push, 1)
struct wave_format
{
    unsigned __int16 audioFormat;
    unsigned __int16 numChannels;
    unsigned __int32 sampleRate;
    unsigned __int32 byteRate;
    unsigned __int16 blockAllign;
    unsigned __int16 bitsPerSample;
};
#pragma pack (pop)

// Обработчик звуков
class AudioManager {
public:
    // Инициализация
    void init();

    // Установить позицию слушателя
    void setListenerPosition(glm::vec3 position);

    // Начать проигрывание
    void play(SoundType sound, glm::vec3 position = glm::vec3());

    // Остановить проигрывание
    void stop(SoundType sound);

private:
    // Загрузка звука из файла
    ALuint load(const char* filename);

private:
    ALuint source[MAX_SOUND_COUNT]; // Источники звука
    ALuint buffer[MAX_SOUND_COUNT]; // Буферы для хранения звуков
};