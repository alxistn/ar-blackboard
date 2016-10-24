#ifndef FPSTIMER_H
#define FPSTIMER_H

#include <SDL2/SDL.h>

class FPSTimer
{
private:

    int _maxFPS;
    float _min_frame_time;

    Uint32 _old_time = 0;
    Uint32 _current_time = 0;
    float _frame_time = 0;


public:
    FPSTimer(float maxFPS);

    void start();
    void sleep();

    float getFPS() const;
    float getFrameTime() const;

};

#endif // FPSTIMER_H
