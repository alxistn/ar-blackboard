#include <iostream>

#include "window.h"
#include "gamescene.h"
#include "fpstimer.h"

int main ()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::logic_error(SDL_GetError());

    bool quit = false;
    Window window1(640, 480, "Box2D Scene");
    GameScene scene1(window1.getViewPort());
    window1.setScene(&scene1);

    FPSTimer fpsTimer;
    fpsTimer.start();
    while (quit == false) {

        //Events


        //Logic
        scene1.update(fpsTimer.getFrameTime());

        //Rendering
        window1.draw();


        //Logic & Rendering
        //window1.update(fpsTimer.getFrameTime());


        //Update FPSTimer (& Cap FPS)
        fpsTimer.update();
    }

    SDL_Quit();
}
