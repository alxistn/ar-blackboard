#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "Box2D/Box2D.h"

class Scene
{
protected:

    int _width;
    int _height;
    SDL_Rect _viewPort;

public:
    Scene(const SDL_Rect& viewPort);

    virtual void draw(SDL_Renderer* renderer) const = 0;
    virtual void update(float deltaTime) = 0;
    virtual void handleEvent(const SDL_Event& event) = 0;
};

#endif // SCENE_H
