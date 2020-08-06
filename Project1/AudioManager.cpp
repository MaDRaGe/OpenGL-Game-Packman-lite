#include "AudioManager.h"

// Инициализация
void AudioManager::init()
{
    // Загрузка звуков из файлов
    buffer[AMBIENT] = load("../MUSIC/ambient.wav");
    buffer[DEATH] = load("../MUSIC/death.wav");
    buffer[EXPLOSION] = load("../MUSIC/explosion.wav");
    buffer[SHIFT] = load("../MUSIC/shift.wav");
    buffer[PORTAL] = load("../MUSIC/portal.wav");
    for (int i = 0; i < MAX_SOUND_COUNT; i++)
    {
        alGenSources(1, &source[i]);
        alSourcei(source[i], AL_BUFFER, buffer[i]);
    }
    
    // Найстройка звуков
    alSourcef(source[SHIFT], AL_GAIN, 6.0f);
    alSourcef(source[PORTAL], AL_GAIN, 0.2f);
    alSourcef(source[DEATH], AL_GAIN, 6.0f);
    alSourcef(source[EXPLOSION], AL_GAIN, 0.3f);
    alSourcei(source[AMBIENT], AL_LOOPING, AL_TRUE);
    alSourcef(source[AMBIENT], AL_GAIN, 0.1);
    alSourcef(source[AMBIENT], AL_PITCH, 1.2f);
    play(AMBIENT);
}

// Установить позицию слушателя
void AudioManager::setListenerPosition(vec3 position)
{
    ALfloat listenerPos[3] = { position.x, position.y, position.z };
    vec3 at = normalize(vec3(0 - position.x, 0 - position.y, 0 - position.z));
    vec3 supplied = vec3(0, 1, 0);
    vec3 right = cross(supplied, at);
    vec3 up = normalize(cross(at, right));
    ALfloat listenerOrientation[6] = { at.x, at.y, at.z, up.x, up.y, up.z };
    alListenerfv(AL_POSITION, listenerPos);
    alListenerfv(AL_ORIENTATION, listenerOrientation);
    alListenerf(AL_GAIN, 2.0f);
}

// Проигрывание звука
void AudioManager::play(SoundType sound, vec3 position)
{
    if (sound == AMBIENT)
    {
        ALfloat sourcePos[] = { 0, 0, 0 };
        alSourcei(source[sound], AL_SOURCE_RELATIVE, AL_TRUE);
        alSourcefv(source[sound], AL_POSITION, sourcePos);
    }
    else
    {
        ALfloat sourcePos[] = { position.x, position.y, position.z };
        alSourcei(source[sound], AL_SOURCE_RELATIVE, AL_FALSE);
        alSourcefv(source[sound], AL_POSITION, sourcePos);
    }
    alSourcePlay(source[sound]);
}

// Остановить проигрывание
void AudioManager::stop(SoundType sound)
{
    alSourceStop(source[sound]);
}

// Загрузка звука из файла
ALuint AudioManager::load(const char* filename)
/*
    params:
        filename - path to audio file

    return:
        id of buffer of audio file
*/
{
    // Открыть файл
    FILE* f = nullptr;
    fopen_s(&f, filename, "rb");
    if (f == nullptr) 
    {
        printf_s("File is not opened %s\n", filename);
        return 0;
    }

    // Чтение чанков из файла
    wave_chunc_header header;
    wave_format wfmt;
    unsigned char* audio_data = nullptr;
    unsigned long data_length = 0;
    while (fread(&header, sizeof(header), 1, f) != 0) // До конца файла
    {
        if (    header.id[0] == 'R'
             && header.id[1] == 'I'
             && header.id[2] == 'F'
             && header.id[3] == 'F'
           )
        {
            char temp[4];
            fread(temp, sizeof(char), 4, f);
            continue;
        }

        // Формат аудиоданных
        if (    header.id[0] == 'f'
             && header.id[1] == 'm'
             && header.id[2] == 't'
             && header.id[3] == ' '
           )
        {
            fread(&wfmt, sizeof(wfmt), 1, f);
            continue;
        }

        // Аудиоданные
        if (    header.id[0] == 'd'
             && header.id[1] == 'a'
             && header.id[2] == 't'
             && header.id[3] == 'a'
           )
        {
            data_length = header.size;
            audio_data = new unsigned char[data_length];
            fread(audio_data, sizeof(char), data_length, f);
            continue;
        }
        fseek(f, header.size, SEEK_CUR);
    }

    ALuint frequency = wfmt.sampleRate;
    ALenum format = 0;
    if (wfmt.bitsPerSample == 8)
    {
        if (wfmt.numChannels == 1)
        {
            format = AL_FORMAT_MONO8;
        }
        else
        {
            format = AL_FORMAT_STEREO8;
        }
    }
    if (wfmt.bitsPerSample == 16)
    {
        if (wfmt.numChannels == 1)
        {
            format = AL_FORMAT_MONO16;
        }
        else
        {
            format = AL_FORMAT_STEREO16;
        }
    }

    // Загрузить данные в буфер OpenAL
    ALuint buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, audio_data, data_length, frequency);
    if (audio_data != nullptr)
    {
        delete[] audio_data;
    }
    return buffer;
}
