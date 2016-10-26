#include "cubeobject.h"

CubeObject::CubeObject(b2World* world, SDL_Renderer* renderer, float x, float y, float width, float height, bool dynamic)
    : GameObject(world, renderer)
{
    width /= 2.0f;
    height /= 2.0f;

    // Creation of the body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / BOX2D_SCALE, y / BOX2D_SCALE);
    bodyDef.type = (dynamic == true) ? b2_dynamicBody : b2_staticBody;
    _body = _world->CreateBody(&bodyDef);

    // Definition of the shape
    b2PolygonShape shape;
    shape.SetAsBox(width / BOX2D_SCALE, height / BOX2D_SCALE);

    // Create body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = (width * height) / BOX2D_SCALE;
    fixtureDef.friction = 0.75f;
    fixtureDef.restitution = (dynamic == true) ? 0.1f : 0.0f;
    _body->CreateFixture(&fixtureDef);
}

