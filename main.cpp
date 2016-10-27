#include <iostream>

#include "window.h"
#include "scene.h"
#include "opencvscene.h"
#include "gamescene.h"
#include "fpstimer.h"
#include <cstddef>
#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   768
#define WINDOW_TITLE    "Box2D Scene"

int main ()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::logic_error(SDL_GetError());
    //detect numbers of monitors
    SDL_DisplayMode monitorA;
    SDL_DisplayMode monitorB;
    uint32 flags;

    int vdn = SDL_GetNumVideoDisplays();
    SDL_Rect screens[2];
    if (vdn < 1)
        return 0;
    if (vdn == 1){
       SDL_GetCurrentDisplayMode(0, &monitorA);
       screens[0].x = 0;
       screens[0].y = 0;
       screens[0].h = monitorA.h;
       screens[0].w = monitorA.w / 2;
       screens[1].x = monitorA.h;
       screens[1].y = 0;
       screens[1].h = monitorA.h;
       screens[1].w = monitorA.w / 2;
       flags = SDL_WINDOW_BORDERLESS;
    }
    if (vdn >= 2){
       SDL_GetCurrentDisplayMode(0, &monitorA);
       SDL_GetCurrentDisplayMode(1, &monitorB);
       screens[0].x = 0;
       screens[0].y = 0;
       screens[0].h = monitorB.h;
       screens[0].w = monitorB.w;
       screens[1].x = 1920;
       screens[1].y = 0;
       screens[1].h = monitorA.h;
       screens[1].w = monitorA.w;
       flags = SDL_WINDOW_FULLSCREEN;
    }


    Window mainWindow(screens[1].x, screens[1].y,screens[1].w,screens[1].h, flags, WINDOW_TITLE);
    Window openCVWindow(screens[0].x, screens[0].y,screens[0].w,screens[0].h, flags, "opencv parameter");
SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    OpenCVScene openCVScene(openCVWindow);
    GameScene gameScene(mainWindow);

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
                openCVWindow.handleEvent(event);
            }
        }

        //Logic
        float time = fpsTimer.getFrameTime();
        mainWindow.update(time);
        openCVWindow.update(time);


        //Rendering
        mainWindow.draw();
        openCVWindow.draw();

        //Logic & Rendering
        //mainWindow.update(fpsTimer.getFrameTime());


        //Update FPSTimer (& Cap FPS)
        fpsTimer.update();
    }
    //*/
    std::cout << "Closing Application." << std::endl;
    SDL_Quit();
}
