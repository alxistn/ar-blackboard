//
//  GameObject.hpp
//  ar-blackboard
//
//  Created by Alexis Santini on 24/10/2016.
//  Copyright © 2016 ar-blackbord. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <stdexcept>
#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>

#define BOX2D_SCALE     30.0f

class GameScene;

class GameObject {
    
public:

    enum Type {
        CUBE,
        DESTRUCTIBLE,
        PLAYER,
        MISSILE,
        BALL,
    };
    const Type type;

protected:

    bool        _toDelete = false;

    GameScene*  _gameScene = NULL;
    b2World*    _world = NULL;
    SDL_Renderer* _renderer = NULL;
    b2Body*     _body = NULL;
    
public:
    GameObject(GameScene* gameScene, b2World* world, SDL_Renderer* renderer, Type type);
    virtual ~GameObject();

    SDL_Point getPosition();
    b2Vec2 getB2Position();

    bool toDelete();

    virtual void update();

    void    draw() const;
    void    drawChain(const b2ChainShape* chainShape) const;
    void    drawEdge(const b2EdgeShape* edgeShape) const;
    void    drawCircle(const b2CircleShape* circleShape) const;
    void    drawPolygon(const b2PolygonShape* polygonShape) const;

    virtual void handleEvent(const SDL_Event& event);
    virtual void beginContactEvent(GameObject* contactObject);
    virtual void endContactEvent(GameObject* contactObject);
    Type        getType()const;
    
};

#endif /* GameObject_hpp */
