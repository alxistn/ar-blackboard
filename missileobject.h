#ifndef MISSILEOBJECT_H
#define MISSILEOBJECT_H

#include "gameobject.hpp"

class MissileObject : public GameObject
{
public:
    MissileObject(b2World* world, SDL_Renderer* renderer, float x, float y, float a);
    ~MissileObject();

    void beginContactEvent(GameObject* contactObject);
};

#endif // MISSILEOBJECT_H
