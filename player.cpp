#include <iostream>
#include "PlayerContactListener.hpp"
#include "player.h"

Player::Player(b2World* world, SDL_Renderer* renderer, float x, float y)
    : GameObject(world, renderer)
{
    _numFootContacts = 0;
    float width = 8.0f;
    float height = 24.0f;

    // Creation of the body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / BOX2D_SCALE, y / BOX2D_SCALE);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    _body = _world->CreateBody(&bodyDef);

    // Definition of the shape
    b2PolygonShape shape;
    shape.SetAsBox(width / BOX2D_SCALE, height / BOX2D_SCALE);

    // Create body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = (width * height) / BOX2D_SCALE;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;
    _body->CreateFixture(&fixtureDef);
    
    //add foot sensor fixture
    shape.SetAsBox(width / BOX2D_SCALE, 5 / BOX2D_SCALE, b2Vec2(0,0.75), 0);
    fixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = _body->CreateFixture(&fixtureDef);
    footSensorFixture->SetUserData( (void*)3 );

    //at global scope
    _playerContactListener = new PlayerContactListener(this);
    
    //in FooTest constructor
    _world->SetContactListener(_playerContactListener);

}

void Player::moveLeft()
{
    //Apply Force
    //_body->ApplyForceToCenter(b2Vec2(-10.0f, 0.0f), true);
    b2Vec2 movement = _body->GetLinearVelocity();
    movement.x = -3.0f;
    _body->SetLinearVelocity(movement);
}

void Player::moveRight()
{
    //Apply Froce
    //_body->ApplyForceToCenter(b2Vec2(10.0f, 0.0f), true);
    b2Vec2 movement = _body->GetLinearVelocity();
    movement.x = 3.0f;
    _body->SetLinearVelocity(movement);
}

void Player::stop()
{
    b2Vec2 movement = _body->GetLinearVelocity();
    movement.x = 0.0f;
    _body->SetLinearVelocity(movement);
}

void Player::jump()
{
   // _body->ApplyForceToCenter(b2Vec2(0.0f, -1000.0f), true);
   //float impulse = _body->GetMass() * 10;
   //_body->ApplyLinearImpulse(b2Vec2(0, impulse), _body->GetWorldCenter(), true);
    if (_numFootContacts < 1)
    {
        return;
    }
   _body->ApplyLinearImpulse(b2Vec2(0, -_body->GetMass() * 6.0f), _body->GetWorldCenter(), true);
}

void Player::incrFootContacts()
{
    _numFootContacts++;
}

void Player::decrFootContacts()
{
    _numFootContacts--;
}
