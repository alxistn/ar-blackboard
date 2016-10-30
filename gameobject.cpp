//
//  GameObject.cpp
//  ar-blackboard
//
//  Created by Alexis Santini on 24/10/2016.
//  Copyright © 2016 ar-blackbord. All rights reserved.
//

#include <cmath>
#include <iostream>
#include "gamescene.h"
#include "gameobject.h"

GameObject::GameObject(GameScene* gameScene, b2World* world, SDL_Renderer* renderer, Type type)
    : type(type), _gameScene(gameScene), _world(world), _renderer(renderer)
{
}

GameObject::~GameObject()
{
    if (_body != NULL)
        _world->DestroyBody(_body);
}

SDL_Point GameObject::getPosition()
{
    b2Vec2 b2Position= _body->GetPosition();
    SDL_Point position;

    position.x = b2Position.x * BOX2D_SCALE;
    position.y = b2Position.y * BOX2D_SCALE;
    return position;
}

b2Vec2 GameObject::getB2Position() {
    return _body->GetPosition();
}

bool GameObject::toDelete()
{
    return _toDelete;
}

void GameObject::update()
{
    //Not Implemented
}

void    GameObject::draw() const
{
    if (_body == NULL)
        return;
    for (const b2Fixture* fixture = _body->GetFixtureList(); fixture != NULL; fixture = fixture->GetNext())
    {
        const b2Shape* shape = fixture->GetShape();
        switch (shape->GetType()) {
            case b2Shape::Type::e_chain :
                    drawChain(static_cast<const b2ChainShape*>(shape));
                break;
            case b2Shape::Type::e_edge :
                    drawEdge(static_cast<const b2EdgeShape*>(shape));
                break;
            case b2Shape::Type::e_circle :
                    drawCircle(static_cast<const b2CircleShape*>(shape));
                break;
            case b2Shape::Type::e_polygon :
                    drawPolygon(static_cast<const b2PolygonShape*>(shape));
                break;
            default:
                    throw std::logic_error("Shape type not supported");
                break;
        }
    }
}

void    GameObject::drawChain(const b2ChainShape* chainShape) const
{
    SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
    int vertexCount = chainShape->m_count;
    b2Vec2 position = _body->GetPosition();

    float angle = _body->GetAngle();
    float s = sinf(angle);
    float c = cosf(angle);

    b2Vec2 prevVec = chainShape->m_vertices[0];
    prevVec.Set(prevVec.x * c - prevVec.y * s,
                prevVec.x * s + prevVec.y * c);
    prevVec += position;
    b2Vec2 nextVec;
    for (int i = 0; i < (vertexCount - 1); ++i) {
        nextVec = chainShape->m_vertices[i + 1];
        nextVec.Set(nextVec.x * c - nextVec.y * s,
                    nextVec.x * s + nextVec.y * c);
        nextVec += position;
        SDL_RenderDrawLine(_renderer, prevVec.x * BOX2D_SCALE , prevVec.y * BOX2D_SCALE, nextVec.x * BOX2D_SCALE, nextVec.y * BOX2D_SCALE);
        prevVec = nextVec;
    }
}

void    GameObject::drawEdge(const b2EdgeShape* edgeShape) const
{
    (void)edgeShape;
}

void    GameObject::drawCircle(const b2CircleShape* circleShape) const
{
    SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
    int sides = 32;
    b2Vec2 center = _body->GetPosition();
    float radius = circleShape->m_radius;

    float d_a = (2*M_PI)/sides;
    float angle = d_a;
    b2Vec2 start, end;
    end.x = radius + center.x;
    end.y = 0.0f + center.y;
    for (int i = 0; i != sides; i++)
    {
        start = end;
        end.x = cos(angle) * radius + center.x;
        end.y = sin(angle) * radius + center.y;
        angle += d_a;
        SDL_RenderDrawLine(_renderer, start.x * BOX2D_SCALE , start.y * BOX2D_SCALE, end.x * BOX2D_SCALE, end.y * BOX2D_SCALE);
    }
}

void    GameObject::drawPolygon(const b2PolygonShape* polygonShape) const
{
    SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
    int vertexCount = polygonShape->m_count;
    b2Vec2 position = _body->GetPosition();

    float angle = _body->GetAngle();
    float s = sinf(angle);
    float c = cosf(angle);

    b2Vec2 prevVec = polygonShape->m_vertices[vertexCount - 1];
    prevVec.Set(prevVec.x * c - prevVec.y * s,
                prevVec.x * s + prevVec.y * c);
    prevVec += position;
    b2Vec2 nextVec;
    for (int i = 0; i < vertexCount; ++i) {
        nextVec = polygonShape->m_vertices[i];
        nextVec.Set(nextVec.x * c - nextVec.y * s,
                    nextVec.x * s + nextVec.y * c);
        nextVec += position;
        SDL_RenderDrawLine(_renderer, prevVec.x * BOX2D_SCALE , prevVec.y * BOX2D_SCALE, nextVec.x * BOX2D_SCALE, nextVec.y * BOX2D_SCALE);
        prevVec = nextVec;
    }
}

void    GameObject::handleEvent(const SDL_Event& event)
{
    //Not implemented
    (void)event;
}

void    GameObject::beginContactEvent(GameObject* contactObject)
{
    //Not implemented
    (void)contactObject;
}

void    GameObject::endContactEvent(GameObject* contactObject)
{
    //Not implemented
    (void)contactObject;
}

GameObject::Type GameObject::getType() const
{
    return type;
}
