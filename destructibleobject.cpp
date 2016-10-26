#include "destructibleobject.h"

DestructibleObject::DestructibleObject(b2World* world, SDL_Renderer* renderer, float x, float y)
    : GameObject(world, renderer)
{
    // Creation of the body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / BOX2D_SCALE, y / BOX2D_SCALE);
    bodyDef.type = b2_staticBody;
    _body = _world->CreateBody(&bodyDef);

    // Definition of the shape
    b2Vec2 points[8] = {
        {2*4, 2},
        {3*4, 0},
        {2*4, -1},
        {0*4, 0},
        {-2*4, -1},
        {-3*4, 0},
        {-2*4, 2},
        {0*4, 3}
    };
    //b2PolygonShape shape;
    b2ChainShape shape;
    shape.CreateChain(points, 8);

    // Create body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.0f;
    fixtureDef.friction = 0.75f;
    fixtureDef.restitution = 0.0f;
    _body->CreateFixture(&fixtureDef);
}

void destroy(float x, float y, float r)
{

}
