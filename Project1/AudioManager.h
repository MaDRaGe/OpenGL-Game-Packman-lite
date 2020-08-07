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

// ��������� wav-�����
#pragma pack (push, 1)
struct wave_chunc_header 
{
    unsigned __int8 id[4]; // ������������� �����
    unsigned __int32 size; // ������ ���������� ����� �����
};
#pragma pack (pop)

// ������ �����������
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

// ���������� ������
class AudioManager {
public:
    // �������������
    void init();

    // ���������� ������� ���������
    void setListenerPosition(glm::vec3 position);

    // ������ ������������
    void play(SoundType sound, glm::vec3 position = glm::vec3());

    // ���������� ������������
    void stop(SoundType sound);

private:
    // �������� ����� �� �����
    ALuint load(const char* filename);

private:
    ALuint source[MAX_SOUND_COUNT]; // ��������� �����
    ALuint buffer[MAX_SOUND_COUNT]; // ������ ��� �������� ������
};