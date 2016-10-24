#include <iostream>

#include "window.h"
#include "gamescene.h"
#include "fpstimer.h"

int main ()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::logic_error(SDL_GetError());

    Window window1(640, 480, "Box2D Scene");
    GameScene scene1(window1.getViewPort());
    window1.setScene(&scene1);

    Window window2(640, 480, "Box2D Scene");
    window2.setScene(new GameScene(window2.getViewPort()));

    FPSTimer fpsTimer;
    fpsTimer.start();
    bool quit = false;
    SDL_Event event;
    while (quit == false) {

        //Events
        //Handle events on queue
        while(SDL_PollEvent(&event) != 0)
        {
            //User requests quit
            if (event.type == SDL_QUIT)
                quit = true;
            else {
                window1.handleEvent(event);
                window2.handleEvent(event);
            }
        }
        if (window1.hidden() && window2.hidden())
            quit = true;

        //Logic
        window1.update(fpsTimer.getFrameTime());
        window2.update(fpsTimer.getFrameTime());


        //Rendering
        window1.draw();
        window2.draw();


        //Logic & Rendering
        //window1.update(fpsTimer.getFrameTime());


        //Update FPSTimer (& Cap FPS)
        fpsTimer.update();
    }

    std::cout << "Closing Application." << std::endl;
    SDL_Quit();
}
