#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "gameobject.hpp"

class PlayerContactListener;

class Player : public GameObject
{
private:
    static const Uint32 _minJumpTimeInterval = 100;
    int _numFootContacts = 0;
    Uint32 _lastJumpTime = 0;
    float _barrelDirection = 0.0f;
    b2Fixture* _barrelFixture = NULL;
    
public:

    Player(GameScene* gameScene, b2World* world, SDL_Renderer* renderer, float x, float y);
    ~Player();
    void HandleEvent();void handleEvent(const SDL_Event& event);

    void setSpeed(float speed);
    void setBarrelRotation(float angle);
    void rotateBarrel(float deltaAngle);
    void jump(float height);
    void shoot();
    
    void beginContactEvent(GameObject* contactObject);
    void endContactEvent(GameObject* contactObject);
    
};

#endif // PLAYER_H
