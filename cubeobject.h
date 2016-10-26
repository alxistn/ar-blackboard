#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include "gameobject.hpp"

class CubeObject : public GameObject
{
public:
    CubeObject(b2World* world, SDL_Renderer* renderer, float x, float y, float width, float height, bool dynamic = true);
};

#endif // CUBEOBJECT_H
