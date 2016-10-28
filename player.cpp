#include <iostream>
#include "player.h"

Player::Player(b2World* world, SDL_Renderer* renderer, float x, float y)
    : GameObject(world, renderer)
{
    // Player Position
    x /= BOX2D_SCALE;
    y /= BOX2D_SCALE;
    // Player Size
    float width = 16.0f / (2.0f * BOX2D_SCALE);
    float height = 48.0f / (2.0f * BOX2D_SCALE);
    // Foot position (relative to player)
    b2Vec2 footOffest = b2Vec2(0, height);
    // Foot size
    float footWidth = 8.0f / (2.0f * BOX2D_SCALE);
    float footHeight = 8.0f / (2.0f * BOX2D_SCALE);

    // Creation of the body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x, y);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    _body = _world->CreateBody(&bodyDef);

    // Definition of the shape
    b2PolygonShape shape;
    shape.SetAsBox(width, height);

    // Create body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = (width * height);
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;
    _body->CreateFixture(&fixtureDef);
    
    //add foot sensor fixture
    shape.SetAsBox(footWidth, footHeight, footOffest, 0);
    fixtureDef.isSensor = true;
    fixtureDef.userData = this;
    _body->CreateFixture(&fixtureDef);
}

void Player::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_UP:
                jump();
            break;

            case SDLK_LEFT:
                moveLeft();
            break;

            case SDLK_RIGHT:
                moveRight();
            break;

            default:
            break;
        }
    }
    if (event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_RIGHT:
                stop();
            break;

            case SDLK_LEFT:
                stop();
            break;

            default:
            break;
        }
    }
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

void Player::beginContactEvent(GameObject* contactObject) {
    (void)contactObject;
    _numFootContacts++;
}

void Player::endContactEvent(GameObject* contactObject) {
    (void)contactObject;
    _numFootContacts--;
}
