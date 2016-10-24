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
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                //Get mouse position
                int x, y;
                SDL_GetMouseState(&x, &y);
                std::cout << "Mouse buttom pressed at " << x << " " << y << std::endl;
                scene1.CreateBox(x, y);
            }
            //User presses a key
            else if(event.type == SDL_KEYDOWN)
            {
                //Handle some key events
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        std::cout << "Key up pressed" << std::endl;
                    break;

                    case SDLK_DOWN:
                        std::cout << "Key down pressed" << std::endl;
                    break;

                    case SDLK_LEFT:
                        std::cout << "Key left pressed" << std::endl;
                    break;

                    case SDLK_RIGHT:
                        std::cout << "Key right pressed" << std::endl;
                    break;

                    default:
                        std::cout << "Non handled key pressed" << std::endl;
                    break;
                }
            }
        }

        //Logic
        scene1.update(fpsTimer.getFrameTime());

        //Rendering
        window1.draw();


        //Logic & Rendering
        //window1.update(fpsTimer.getFrameTime());


        //Update FPSTimer (& Cap FPS)
        fpsTimer.update();
    }

    std::cout << "Closing Application." << std::endl;
    SDL_Quit();
}
