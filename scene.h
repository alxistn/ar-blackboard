#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "Box2D/Box2D.h"

class Window;

class Scene
{
protected:

    Window* _window = NULL;

public:
    Scene(Window& window);
    virtual ~Scene();
    virtual void draw() const = 0;
    virtual void update(float deltaTime) = 0;
    virtual void handleEvent(const SDL_Event& event) = 0;

    Window*     getWindow() const;
    void        setWindow(Window* window);
};

#endif // SCENE_H
