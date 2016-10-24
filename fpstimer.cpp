#include "fpstimer.h"

FPSTimer::FPSTimer(float maxFPS)
    : _maxFPS(maxFPS), _min_frame_time((1.0f / maxFPS) * 1000.0f)
{
}

void FPSTimer::start()
{
    _current_time = SDL_GetTicks();
}

void FPSTimer::sleep()
{
    float sleep_time;

    _old_time = _current_time;
    _current_time = SDL_GetTicks();
    _frame_time = (_current_time - _old_time);
    if (_frame_time < _min_frame_time) {
        sleep_time = _min_frame_time - _frame_time;
        //SDL_Delay(sleep_time);
        _frame_time += sleep_time;
        _current_time += sleep_time;
    }
}


float FPSTimer::getFPS() const
{
    if (_frame_time == 0.0f)
        return 0.0f;
    return 1000.0f / _frame_time;
}

float FPSTimer::getFrameTime() const
{
    if (_frame_time == 0.0f)
        return 0.0f;
    return _frame_time / 1000.0f;
}
