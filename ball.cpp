#include <iostream>
#include "ball.h"

Ball::Ball(GameScene* gameScene, b2World* world, SDL_Renderer* renderer, float x, float y)
    : GameObject(gameScene, world, renderer, Type::MISSILE)
{
    float width = 10.0f;
    float height = 10.0f;

    x /= BOX2D_SCALE;
    y /= BOX2D_SCALE;
    width /= 2.0f * BOX2D_SCALE;
    height /= 2.0f * BOX2D_SCALE;

    // Creation of the body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x, y);
    bodyDef.type = b2_dynamicBody;
    _body = _world->CreateBody(&bodyDef);

    // Definition of the shape
    /*b2Vec2 b2Vec2Points[5] = {
        {-width, -height},
        {0, -height * 2.0f},
        {width, -height},
        {width, height},
        {-width, height}
    };
    b2PolygonShape shape;
    shape.Set(b2Vec2Points, 5);*/
    b2CircleShape shape;
    shape.m_radius = width;

    // Create body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = width * height;
    fixtureDef.friction = 0.75f;
    fixtureDef.restitution = 0.6f;
    fixtureDef.userData = this;
    //fixtureDef.isSensor = true;
    _body->CreateFixture(&fixtureDef);

}

Ball::~Ball()
{
    std::cout << "Ball removed." << std::endl;
}

