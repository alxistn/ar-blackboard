#ifndef MISSILEOBJECT_H
#define MISSILEOBJECT_H

#include "gameobject.h"

class Missile : public GameObject
{
public:
    Missile(GameScene* gameScene, b2World* world, SDL_Renderer* renderer, float x, float y, float a);
    ~Missile();

    void beginContactEvent(GameObject* contactObject);
};

#endif // MISSILEOBJECT_H
