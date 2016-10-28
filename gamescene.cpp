#include "gamescene.h"
#include "window.h"
#include <iostream>
#include "cubeobject.h"
#include "destructibleobject.h"
#include "player.h"

GameScene::GameScene(Window& window, bool clean)
    : Scene(window), _gravity(0.f, 9.8f), _world(_gravity)
{
    _world.SetContactListener(&_contactListener);
    if (!clean) {
        //createGround(_window->getWidth() / 2, _window->getHeight() / 2, _window->getWidth() / 2, 16.0f);
        createPlayer(_window->getWidth() / 2, 0);
        std::vector<cv::Point> pts;
        pts.push_back(cv::Point(-100,0));
        pts.push_back(cv::Point(-150,150));
        pts.push_back(cv::Point(0,100));
        pts.push_back(cv::Point(150,150));
        pts.push_back(cv::Point(100,0));
        pts.push_back(cv::Point(150,-150));
        pts.push_back(cv::Point(0,-100));
        pts.push_back(cv::Point(-150,-150));
        createDestructibleObject(_window->getWidth() / 2, _window->getHeight() / 2, pts);
    }
}

GameScene::~GameScene()
{
    for (GameObject* gameObject :_gameObjects)
        delete gameObject;
}

void GameScene::draw() const
{
    for (GameObject* gameObject : _gameObjects) {
        gameObject->draw();
    }
}

void GameScene::update(float deltaTime)
{
    //Game engine and physics here
    _world.Step(deltaTime, 8, 3);

    //Delete objects outside of view
    auto gameObjectIt = _gameObjects.begin();
    while (gameObjectIt != _gameObjects.end())
    {
        SDL_Point position = (*gameObjectIt)->getPosition();
        if (position.x < (-_worldBoundaryOffset) || position.x > (_window->getWidth() + _worldBoundaryOffset) ||
                position.y < (-_worldBoundaryOffset) || position.y > (_window->getHeight() + _worldBoundaryOffset)) {
            delete *gameObjectIt;
            gameObjectIt = _gameObjects.erase(gameObjectIt);
        }
        else
            ++gameObjectIt;
    }
}

void GameScene::handleEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        //createBox(x, y, 16.0f, 16.0f);
        createPlayer(x, y);
    }
    for (GameObject* gameObject : _gameObjects) {
        gameObject->handleEvent(event);
    }
}

void GameScene::clear()
{
    for (GameObject* gameObject :_gameObjects)
        delete gameObject;
    _gameObjects.clear();
}

void GameScene::createGround(float x, float y, float w, float h)
{
    _gameObjects.push_back(new CubeObject(&_world, _window->getRenderer(), x, y, w, h, false));
}

void GameScene::createBox(float x, float y, float w, float h)
{
    _gameObjects.push_back(new CubeObject(&_world, _window->getRenderer(), x, y, w, h));
}

void GameScene::createDestructibleObject(float x, float y, const std::vector<cv::Point>& points)
{
    _gameObjects.push_back(new DestructibleObject(&_world, _window->getRenderer(), _window->getWidth() / 2, _window->getHeight() / 2 - 128.0f, points));
}

void GameScene::createPlayer(float x, float y)
{
    Player* newPlayer = new Player(&_world, _window->getRenderer(), x, y);
    _gameObjects.push_back(newPlayer);
    return;
}

void GameScene::addShape(const std::vector<cv::Point>& shape)
{
    if (shape.size() >= 3){
        DestructibleObject *newObject = new DestructibleObject(&_world, _window->getRenderer(), 0,0, shape);
        _gameObjects.push_back(newObject);
    }
}

void GameScene::addShapes(const std::vector<std::vector<cv::Point>>& shapes)
{
    for (auto& shape : shapes){
        addShape(shape);
    }
}
