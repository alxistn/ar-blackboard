#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.hpp"

class Player : public GameObject
{
public:
    Player(b2World* world, float x, float y, const b2Shape* shape);
};

#endif // PLAYER_H
