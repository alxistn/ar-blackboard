//
//  GameObject.cpp
//  ar-blackboard
//
//  Created by Alexis Santini on 24/10/2016.
//  Copyright © 2016 ar-blackbord. All rights reserved.
//

#include <cmath>
#include <iostream>
#include "gameobject.hpp"

GameObject::GameObject(b2World* world, float x, float y, b2BodyType type, const b2Shape* shape, float density, float friction, float restitution)
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
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    _fixture = _body->CreateFixture(&fixtureDef);
    _shape = _fixture->GetShape();

    // Definition of the draw type
    switch (_shape->GetType()) {
        case b2Shape::Type::e_chain :
                _drawShape = &GameObject::drawChain;
            break;
        case b2Shape::Type::e_edge :
                _drawShape = &GameObject::drawEdge;
            break;
        case b2Shape::Type::e_circle :
                _drawShape = &GameObject::drawCircle;
            break;
        case b2Shape::Type::e_polygon :
                _drawShape = &GameObject::drawPolygon;
            break;
        default:
                throw std::logic_error("Shape type not supported");
            break;
    }
}

GameObject::~GameObject()
{
    _world->DestroyBody(_body);
}

void    GameObject::draw(SDL_Renderer* renderer) const
{
    (this->*_drawShape)(renderer);
}

void    GameObject::drawChain(SDL_Renderer* renderer) const
{
    (void)renderer;
}

void    GameObject::drawEdge(SDL_Renderer* renderer) const
{
    (void)renderer;
}

void    GameObject::drawCircle(SDL_Renderer* renderer) const
{
    (void)renderer;
}

void    GameObject::drawPolygon(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    b2PolygonShape* polygonShape = static_cast<b2PolygonShape*>(_shape);
    int vertexCount = polygonShape->GetVertexCount();
    b2Vec2 position = _body->GetPosition();

    float angle = _body->GetAngle();
    float s = sinf(angle);
    float c = cosf(angle);

    b2Vec2 prevVec = polygonShape->GetVertex(vertexCount - 1);
    prevVec.Set(prevVec.x * c - prevVec.y * s,
                prevVec.x * s + prevVec.y * c);
    prevVec += position;
    b2Vec2 nextVec;
    for (int i = 0; i < vertexCount; ++i) {
        nextVec = polygonShape->GetVertex(i);
        nextVec.Set(nextVec.x * c - nextVec.y * s,
                    nextVec.x * s + nextVec.y * c);
        nextVec += position;
        SDL_RenderDrawLine(renderer, prevVec.x * BOX2D_SCALE , prevVec.y * BOX2D_SCALE, nextVec.x * BOX2D_SCALE, nextVec.y * BOX2D_SCALE);
        prevVec = nextVec;
    }
}

void    GameObject::setFriction(float friction)
{
    _fixture->SetFriction(friction);
}

void    GameObject::setDensity(float density)
{
    _fixture->SetDensity(density);
    _body->ResetMassData();
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

