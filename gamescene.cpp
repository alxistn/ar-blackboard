#include "gamescene.h"
#include <iostream>

GameScene::GameScene(const SDL_Rect& viewPort)
    : Scene(viewPort), _gravity(0.f, 9.8f), _world(_gravity)
{
    CreateGround(0, 360);
    CreateBox(52.0f, 43.0f);
    CreateBox(41.0f, 46.0f);
    CreateBox(47.0f, 58.0f);
    CreateBox(54.0f, 55.0f);
}

void GameScene::draw(SDL_Renderer* renderer) const
{
    for (const b2Body* bodyIterator = _world.GetBodyList(); bodyIterator != 0; bodyIterator = bodyIterator->GetNext())
    {
        if (bodyIterator->GetType() == b2_dynamicBody)
        {
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_Rect boxRect;
            boxRect.x = bodyIterator->GetPosition().x * 30.0f + 16.0f;
            boxRect.y = bodyIterator->GetPosition().y * 30.0f;
            boxRect.w = 16.0f;
            boxRect.h = 16.0f;
            SDL_RenderDrawRect(renderer, &boxRect);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_Rect groundRect;
            groundRect.x = bodyIterator->GetPosition().x * 30.0f;
            groundRect.y = bodyIterator->GetPosition().y * 30.0f + 8.0f;
            groundRect.w = 640.0f;
            groundRect.h = 8.0f;
            SDL_RenderFillRect(renderer, &groundRect);
        }
    }
}

void GameScene::update(float deltaTime)
{
    //Handle all events here

    //Game engine and physics here
    _world.Step(deltaTime, 8, 3);
}

void GameScene::CreateGround(float x, float y)
{
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x/30.f, y/30.f);
    bodyDef.type = b2_staticBody;
    b2Body* body = _world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(640.0f/30.f, 8.0f/30.f); // Creates a box shape. Divide your desired width and height by 2.
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.f;  // Sets the density of the body
    fixtureDef.shape = &shape; // Sets the shape
    body->CreateFixture(&fixtureDef); // Apply the fixture definition
}

void GameScene::CreateBox(int x, int y)
{
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x/30.f, y/30.f);
    bodyDef.type = b2_dynamicBody;
    b2Body* body = _world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(16.0f/30.f, 16.0f/30.f);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.7f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
}
