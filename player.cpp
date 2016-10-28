#include <iostream>
#include "player.h"
#include "gamescene.h"

Player::Player(GameScene* gameScene, b2World* world, SDL_Renderer* renderer, float x, float y)
    : GameObject(gameScene, world, renderer, Type::PLAYER)
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
    // barrel position (relative to player)
    b2Vec2 barrelOffest = b2Vec2(0, -height);
    // Foot size
    float barrelWidth = 8.0f / (2.0f * BOX2D_SCALE);
    float barrelHeight = 48.0f / (2.0f * BOX2D_SCALE);

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

    //add barrel
    shape.SetAsBox(barrelWidth, barrelHeight, barrelOffest, 0);
    fixtureDef.isSensor = true;
    fixtureDef.userData = this;
    _barrelFixture = _body->CreateFixture(&fixtureDef);

    //add foot sensor fixture
    shape.SetAsBox(footWidth, footHeight, footOffest, 0);
    fixtureDef.isSensor = true;
    fixtureDef.userData = this;
    _body->CreateFixture(&fixtureDef);
}

Player::~Player() {
    std::cout << "Player removed." << std::endl;
}

void Player::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_RIGHT:
                setSpeed(0.0f);
            break;

            case SDLK_LEFT:
                setSpeed(0.0f);
            break;

            case SDLK_w:
                shoot();
            break;

            default:
            break;
        }
    }
    if (event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_SPACE:
                jump(6.0f);
            break;
            case SDLK_UP:
                jump(6.0f);
            break;

            case SDLK_LEFT:
                setSpeed(-3.0f);
            break;

            case SDLK_RIGHT:
                setSpeed(3.0f);
            break;

            case SDLK_a:
                rotateBarrel(-0.1f);
            break;

            case SDLK_d:
                rotateBarrel(0.1f);
            break;

            default:
            break;
        }
    }
}


void Player::setSpeed(float speed)
{
    b2Vec2 movement = _body->GetLinearVelocity();
    movement.x = speed;
    _body->SetLinearVelocity(movement);
}

void Player::rotateBarrel(float deltaAngle)
{
    //Update barrel angle
    _barrelDirection += deltaAngle;
    float s = sinf(deltaAngle);
    float c = cosf(deltaAngle);

    //Update barrel shape
    b2PolygonShape* shape = static_cast<b2PolygonShape*>(_barrelFixture->GetShape());
    b2Vec2* points = new b2Vec2[shape->GetVertexCount()];

    for (int i = 0; i < shape->GetVertexCount(); ++i)
    {
        points[i] = shape->GetVertex(i);
        points[i].Set(points[i].x * c - points[i].y * s,
                      points[i].x * s + points[i].y * c);
    }

    shape->Set(points, shape->GetVertexCount());

    delete points;
}

void Player::shoot()
{
    std::cout << "shoot" << std::endl;
    b2Vec2 position = _body->GetPosition();
    _gameScene->createMissile(position.x * BOX2D_SCALE, position.y * BOX2D_SCALE, _barrelDirection);
}

void Player::jump(float height)
{
    if (_numFootContacts < 1)
        return;

    Uint32 currTime = SDL_GetTicks();
    if ((_lastJumpTime + _minJumpTimeInterval) > currTime)
        return;

    _lastJumpTime = currTime;
   _body->ApplyLinearImpulse(b2Vec2(0, -_body->GetMass() * height), _body->GetWorldCenter(), true);
}

void Player::beginContactEvent(GameObject* contactObject) {
    (void)contactObject;
    _numFootContacts++;
}

void Player::endContactEvent(GameObject* contactObject) {
    (void)contactObject;
    _numFootContacts--;
}
