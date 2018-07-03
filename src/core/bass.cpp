#include "bass.hpp"

Bass::Bass()
{
    _instances++;
    if (_instances > 1)
        return;

    if (init())
        if (HIWORD(BASS_GetVersion()) != BASSVERSION)
            log("Bass: Different BASS versions %1 and %2", {static_cast<int>(BASS_GetVersion()), BASSVERSION});
}

Bass::~Bass()
{
    _instances--;
    if (_instances == 0)
        free();
}

BassStream * Bass::stream()
{
    return &m_stream;
}

bool Bass::start()
{
    return call(&BASS_Start);
}

bool Bass::pause()
{
    return call(&BASS_Pause);
}

bool Bass::stop()
{
    return call(&BASS_Stop);
}

bool Bass::setVolume(float volume)
{
    bool success = BASS_SetVolume(volume);
    if (!success)
        error();

    return success;
}

float Bass::volume()
{
    if (BASS_GetVolume() == -1)
        error();

    return BASS_GetVolume();
}

bool Bass::setDevice(DWORD device)
{
    bool success = BASS_SetDevice(device);
    if (!success)
        error();

    return success;
}

DWORD Bass::device()
{
    if (BASS_GetDevice() == -1)
        error();

    return BASS_GetDevice();
}

BASS_DEVICEINFO Bass::deviceInfo()
{
    BASS_DEVICEINFO info;
    if (!BASS_GetDeviceInfo(device(), &info))
        error();

    return info;
}

bool Bass::init()
{
    bool success = BASS_Init(-1, 44100, 0, 0, NULL);
    if (!success)
        error();

    return success;
}

bool Bass::free()
{
    return call(&BASS_Free);
}

bool Bass::call(BOOL(*func)())
{
    bool success = func();
    if (!success)
        error();

    return success;
}

int Bass::_instances = 0;
