//
//  GameObject.cpp
//  ar-blackboard
//
//  Created by Alexis Santini on 24/10/2016.
//  Copyright © 2016 ar-blackbord. All rights reserved.
//

#include "gameobject.hpp"

GameObject::GameObject(b2World* world, float x, float y, b2BodyType type, const b2Shape* shape)
    : _world(world)
{
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;

    // Creation of the body
    bodyDef.position = b2Vec2(x / BOX2D_SCALE, y / BOX2D_SCALE);
    bodyDef.type = type;
    _body = _world->CreateBody(&bodyDef);
    
    // Definition of the body
    fixtureDef.shape = shape;
    _fixture = _body->CreateFixture(&fixtureDef);
    _shape = _fixture->GetShape();
    switch (_shape->GetType()) {
        case b2Shape::Type::e_chain :
            
            break;
        case b2Shape::Type::e_edge :
            
            break;
        case b2Shape::Type::e_circle :
            
            break;
        case b2Shape::Type::e_polygon :
            
            break;
        default:
            break;
    }
}

GameObject::~GameObject()
{
    _world->DestroyBody(_body);
}

void    GameObject::draw() const
{
    
}

void    GameObject::drawChain() const
{
    
}

void    GameObject::drawEdge() const
{
    
}

void    GameObject::drawCircle() const
{
    
}

void    GameObject::drawPolygon() const
{
    
}

void    GameObject::setFriction(float friction)
{
    _fixture->SetFriction(friction);
}

void    GameObject::setDensity(float density)
{
    _fixture->SetDensity(density);
}

void    GameObject::setRestitution(float restitution)
{
    _fixture->SetRestitution(restitution);
}

float    GameObject::getFriction() const
{
    return _fixture->GetFriction();
}

float    GameObject::getDensity() const
{
    return _fixture->GetDensity();
}
float    GameObject::getRestitution() const
{
    return _fixture->GetRestitution();
}

