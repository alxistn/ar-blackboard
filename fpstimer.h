#ifndef FPSTIMER_H
#define FPSTIMER_H

#include <SDL2/SDL.h>

class FPSTimer
{
private:

    float _maxFPS;
    float _minFrameTime;

    Uint32 _oldTime = 0;
    Uint32 _currentTime = 0;
    float _frameTime = 0;


public:
    FPSTimer();
    FPSTimer(float maxFPS);

    void start();
    void update();

    float getFPS() const;
    float getFrameTime() const;

};

#endif // FPSTIMER_H
