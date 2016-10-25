#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "Box2D/Box2D.h"

class Window;

class Scene
{
protected:

    int _width;
    int _height;
    SDL_Rect _viewPort;

    Window* _window = NULL;

public:
    Scene(const SDL_Rect& viewPort);

    virtual void draw() const = 0;
    virtual void update(float deltaTime) = 0;
    virtual void handleEvent(const SDL_Event& event) = 0;

    void setWindow(Window* window);
    Window* getWindow() const;
};

#endif // SCENE_H
