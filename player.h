#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "gameobject.hpp"

class PlayerContactListener;

class Player : public GameObject
{
private:
    int _numFootContacts = 0;
    PlayerContactListener* _playerContactListener = NULL;
    
public:

    Player(b2World* world, SDL_Renderer* renderer, float x, float y);
    void HandleEvent();void handleEvent(const SDL_Event& event);

    void moveLeft();
    void moveRight();
    void stop();
    void jump();
    


    void incrFootContacts();
    void decrFootContacts();
    
};

#endif // PLAYER_H
