#include "gamescene.h"
#include <iostream>

GameScene::GameScene(const SDL_Rect& viewPort)
    : Scene(viewPort), _gravity(0.f, 9.8f), _world(_gravity)
{
    createGround(_width / 2, _height / 2, _width / 2, 16.0f);
}

void GameScene::draw(SDL_Renderer* renderer) const
{
    for (GameObject* gameObject : _gameObjects)
    {
        gameObject->draw(renderer);
    }
}

void GameScene::update(float deltaTime)
{
    //Handle all events here

    //Game engine and physics here
    _world.Step(deltaTime, 8, 3);
}

void GameScene::handleEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        createBox(x, y);
    }
}

void GameScene::createGround(float x, float y, float w, float h)
{
    b2PolygonShape shape;
    shape.SetAsBox((w / 2.0f) / BOX2D_SCALE, (h / 2.0f) / BOX2D_SCALE);
    GameObject* gameObject = new GameObject(&_world, x, y, b2_staticBody, &shape, 0.0f, 1.0f, 0.0f);
    _gameObjects.push_back(gameObject);
}

void GameScene::createBox(int x, int y)
{
    b2PolygonShape shape;
    shape.SetAsBox((16.0f / 2.0f) / BOX2D_SCALE, (16.0f / 2.0f) / BOX2D_SCALE);
    GameObject* gameObject = new GameObject(&_world, x, y, b2_dynamicBody, &shape, 1.0f, 0.75f, 0.25f);
    _gameObjects.push_back(gameObject);

}
