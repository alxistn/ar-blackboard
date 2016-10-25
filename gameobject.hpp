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
#include <SDL.h>

#define BOX2D_SCALE     30.0f

class GameObject {
    
protected:
    b2World*    _world;
    b2Body*     _body;
    b2Fixture*  _fixture;
    b2Shape*    _shape;
    void (GameObject::* _drawShape)(SDL_Renderer*) const;
    
public:
    GameObject(b2World* world, float x, float y, b2BodyType type, const b2Shape* shape,
               float density, float friction, float restitution);
    ~GameObject();

    void    setFriction(float friction);
    void    setDensity(float density);
    void    setRestitution(float restitution);
    float   getFriction() const;
    float   getDensity() const;
    float   getRestitution() const;

    virtual void    draw(SDL_Renderer* renderer) const;
    void    drawChain(SDL_Renderer* renderer) const;
    void    drawEdge(SDL_Renderer* renderer) const;
    void    drawCircle(SDL_Renderer* renderer) const;
    void    drawPolygon(SDL_Renderer* renderer) const;
    
};

#endif /* GameObject_hpp */
