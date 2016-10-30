#ifndef BALL_H
#define BALL_H

#include "gameobject.h"

class Ball: public GameObject
{
public:
    Ball(GameScene* gameScene, b2World* world, SDL_Renderer* renderer, float x, float y);
    ~Ball();
};

#endif // BALL_H
