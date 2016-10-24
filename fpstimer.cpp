#include "cmath"
#include "fpstimer.h"
#include <iostream>

FPSTimer::FPSTimer(float maxFPS)
    : _maxFPS(maxFPS), _minFrameTime((1.0f / maxFPS) * 1000.0f)
{
}

FPSTimer::FPSTimer()
    : _maxFPS(0), _minFrameTime(0.0f)
{
}

void FPSTimer::start()
{
    _currentTime = SDL_GetTicks();
}

void FPSTimer::update()
{
    _oldTime = _currentTime;
    _currentTime = SDL_GetTicks();
    _frameTime = (_currentTime - _oldTime);
    if (_minFrameTime > 0.0f) {
        std::cout << "Sleep" << std::endl;
        Uint32 sleep_time = roundf(_minFrameTime - _frameTime);
        if (sleep_time > 0) {
            SDL_Delay(sleep_time);
            _currentTime = SDL_GetTicks();
            _frameTime = (_currentTime - _oldTime);
        }
    }
}


float FPSTimer::getFPS() const
{
    if (_frameTime == 0.0f)
        return 1000.0f;
    return 1000.0f / _frameTime;
}

float FPSTimer::getFrameTime() const
{
    if (_frameTime == 0.0f)
        return 0.0f;
    return _frameTime / 1000.0f;
}
