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
    
public:

    Player(b2World* world, SDL_Renderer* renderer, float x, float y);
    void HandleEvent();void handleEvent(const SDL_Event& event);

    void moveLeft();
    void moveRight();
    void stop();
    void jump();
    
    void beginContactEvent(GameObject* contactObject);
    void endContactEvent(GameObject* contactObject);
    
};

#endif // PLAYER_H
