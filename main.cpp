#include <iostream>

#include "window.h"
#include "gamescene.h"
#include "fpstimer.h"

#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   768
#define WINDOW_TITLE    "Box2D Scene"

int main ()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::logic_error(SDL_GetError());

    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    GameScene gameScene(mainWindow.getViewPort());
    mainWindow.setScene(&gameScene);

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
                mainWindow.handleEvent(event);
            }
        }

        //Logic
        mainWindow.update(fpsTimer.getFrameTime());


        //Rendering
        mainWindow.draw();


        //Logic & Rendering
        //mainWindow.update(fpsTimer.getFrameTime());


        //Update FPSTimer (& Cap FPS)
        fpsTimer.update();
    }

    std::cout << "Closing Application." << std::endl;
    SDL_Quit();
}
