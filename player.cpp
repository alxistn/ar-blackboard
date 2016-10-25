#include "player.h"

Player::Player(b2World* world, float x, float y, const b2Shape* shape)
    : GameObject(world, x, y, b2_kinematicBody, shape, 0, 0, 0)
{

}

