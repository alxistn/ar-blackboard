#ifndef DESTRUCTIBLEOBJECT_H
#define DESTRUCTIBLEOBJECT_H

#include "gameobject.hpp"

class DestructibleObject : public GameObject
{
public:
    DestructibleObject(b2World* world, SDL_Renderer* renderer, float x, float y);

    void destroy(float x, float y, float r);
};

#endif // DESTRUCTIBLEOBJECT_H
