#include "missileobject.h"
#include "destructibleobject.h"
#include <iostream>

MissileObject::MissileObject(GameScene* gameScene, b2World* world, SDL_Renderer* renderer, float x, float y, float a)
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
    bodyDef.angle = a;
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
    fixtureDef.restitution = 0.0f;
    fixtureDef.userData = this;
    fixtureDef.isSensor = true;
    _body->CreateFixture(&fixtureDef);

    //Set initial speed
    float launchForce = _body->GetMass() * 12.0f;
    _body->ApplyLinearImpulse(b2Vec2(launchForce * sinf(a), launchForce * -cosf(a)), _body->GetWorldCenter(), true);

}

MissileObject::~MissileObject()
{
    //std::cout << "Missile Destroyed" << std::endl;
}

void MissileObject::beginContactEvent(GameObject* contactObject)
{
    if (contactObject != NULL && contactObject->type == Type::DESTRUCTIBLE)
    {
        //std::cout << "Missile touched ground" << std::endl;
        _toDelete = true;
        static_cast<DestructibleObject*>(contactObject)->pushDestroy(_body->GetPosition().x * BOX2D_SCALE, _body->GetPosition().y * BOX2D_SCALE, 1.0f);
    }
}

