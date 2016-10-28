#include "cubeobject.h"
#include <iostream>
CubeObject::CubeObject(b2World* world, SDL_Renderer* renderer, float x, float y, float width, float height, bool dynamic)
    : GameObject(world, renderer)
{
    x /= BOX2D_SCALE;
    y /= BOX2D_SCALE;
    width /= 2.0f * BOX2D_SCALE;
    height /= 2.0f * BOX2D_SCALE;

    // Creation of the body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x, y);
    bodyDef.type = (dynamic == true) ? b2_dynamicBody : b2_staticBody;
    _body = _world->CreateBody(&bodyDef);

    // Definition of the shape
    b2PolygonShape shape;
    shape.SetAsBox(width, height);

    // Create body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = width * height;
    fixtureDef.friction = 0.75f;
    fixtureDef.restitution = (dynamic == true) ? 0.1f : 0.0f;
    fixtureDef.userData = this;
    _body->CreateFixture(&fixtureDef);
}

