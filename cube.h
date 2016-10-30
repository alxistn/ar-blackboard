#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include "gameobject.h"

class Cube : public GameObject
{
public:
    Cube(GameScene* gameScene, b2World* world, SDL_Renderer* renderer, float x, float y, float width, float height, bool dynamic = true);
};

#endif // CUBEOBJECT_H
