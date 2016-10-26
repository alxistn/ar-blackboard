#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.hpp"

class Player : public GameObject
{
public:
    Player(b2World* world, SDL_Renderer* renderer, float x, float y);

    void moveLeft();
    void moveRight();
    void stop();
    void jump();
};

#endif // PLAYER_H
