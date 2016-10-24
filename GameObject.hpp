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
#include <Box2D/Box2D.h>
#include "IMesh.hpp"

#define BOX2D_SCALE     30.0f

class GameObject {
    
private:
    b2World*    _world;
    b2Fixture*  _fixture;
    b2Shape*    _shape;
    b2Body*     _body;
    
public:
    GameObject(b2World* world, float x, float y, b2BodyType type, const b2Shape* mesh);
    ~GameObject();
    void    setFriction(float friction);
    void    setDensity(float density);
    void    setRestitution(float restitution);
    float    getFriction() const;
    float    getDensity() const;
    float    getRestitution() const;
    void    draw() const;
    void    drawChain() const;
    void    drawEdge() const;
    void    drawCircle() const;
    void    drawPolygon() const;
    
};

#endif /* GameObject_hpp */
