#include "gamescene.h"
#include "window.h"
#include <iostream>

GameScene::GameScene(Window& window)
    : Scene(window), _gravity(0.f, 9.8f), _world(_gravity)
{
    createGround(_window->getWidth() / 2, _window->getHeight() / 2, _window->getWidth() / 2, 16.0f);
}

void GameScene::draw() const
{
    for (GameObject* gameObject : _gameObjects)
    {
        gameObject->draw(_window->getRenderer());
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
        createBox(x, y, 16.0f, 16.0f);
    }
}

void GameScene::createGround(float x, float y, float w, float h)
{
    b2PolygonShape shape;
    shape.SetAsBox((w / 2.0f) / BOX2D_SCALE, (h / 2.0f) / BOX2D_SCALE);
    GameObject* gameObject = new GameObject(&_world, x, y, b2_staticBody, &shape, 0.0f, 1.0f, 0.0f);
    _gameObjects.push_back(gameObject);
}

void GameScene::createBox(int x, int y, float w, float h)
{
    b2PolygonShape shape;
    shape.SetAsBox((w / 2.0f) / BOX2D_SCALE, (h / 2.0f) / BOX2D_SCALE);
    GameObject* gameObject = new GameObject(&_world, x, y, b2_dynamicBody, &shape, 1.0f, 0.75f, 0.25f);
    _gameObjects.push_back(gameObject);

}

void GameScene::createPlayer(int x, int y)
{
    return;
}
