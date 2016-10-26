#include "player.h"
#include <iostream>

Player::Player(b2World* world, float x, float y, const b2Shape* shape)
    : GameObject(world, x, y, b2_dynamicBody, shape, 10.0f, 0, 0)
{
    _body->SetFixedRotation(true);

    //add foot sensor fixture
    /*b2PolygonShape polygonShape;
    polygonShape.SetAsBox(0.3, 0.3, b2Vec2(0,-2), 0);
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    myFixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = m_body->CreateFixture(&myFixtureDef);
    footSensorFixture->SetUserData((void*)3);*/
}

void Player::moveLeft()
{
    //Apply Force
    //_body->ApplyForceToCenter(b2Vec2(-10.0f, 0.0f), true);
    _body->SetLinearVelocity(b2Vec2(-2.0f, 0.0f));
}

void Player::moveRight()
{
    //Apply Froce
    _body->SetLinearVelocity(b2Vec2(2.0f, 0.0f));
    //_body->ApplyForceToCenter(b2Vec2(10.0f, 0.0f), true);
}

void Player::jump()
{
   // _body->ApplyForceToCenter(b2Vec2(0.0f, -1000.0f), true);
   //float impulse = _body->GetMass() * 10;
   //_body->ApplyLinearImpulse(b2Vec2(0, impulse), _body->GetWorldCenter(), true);
   _body->ApplyLinearImpulse(b2Vec2(0, -100.0f), _body->GetWorldCenter(), true);
}
