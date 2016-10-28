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

class GameObject {
    
protected:
    b2World*    _world = NULL;
    SDL_Renderer* _renderer = NULL;
    b2Body*     _body = NULL;
    
public:
    GameObject(b2World* world, SDL_Renderer* renderer);
    virtual ~GameObject();

    void    draw() const;
    void    drawChain(const b2ChainShape* chainShape) const;
    void    drawEdge(const b2EdgeShape* edgeShape) const;
    void    drawCircle(const b2CircleShape* circleShape) const;
    void    drawPolygon(const b2PolygonShape* polygonShape) const;

    virtual void handleEvent(const SDL_Event& event);
    virtual void beginContactEvent(GameObject* contactObject);
    virtual void endContactEvent(GameObject* contactObject);
    
};

#endif /* GameObject_hpp */
