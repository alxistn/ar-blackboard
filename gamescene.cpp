#include "gamescene.h"
#include "window.h"
#include <iostream>
#include "cubeobject.h"
#include "destructibleobject.h"
#include "player.h"

GameScene::GameScene(Window& window, VertexExtractor *vertexExtractor)
    : Scene(window), _vertexExtractor(vertexExtractor), _gravity(0.f, 9.8f), _world(_gravity)
{
    if (_vertexExtractor == NULL) {
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

void GameScene::draw() const
{
    for (GameObject* gameObject : _gameObjects)
    {
        gameObject->draw();
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
        //createBox(x, y, 16.0f, 16.0f);
        //createPlayer(x, y);
    }
    for (GameObject* gameObject : _gameObjects) {
        gameObject->handleEvent(event);
    }
    switch (event.type)
    {
    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
            case SDLK_r:
            reset();
            break;
        }
        break;
    }
}

void GameScene::createGround(float x, float y, float w, float h)
{
    _gameObjects.push_back(new CubeObject(&_world, _window->getRenderer(), x, y, w, h, false));
}

void GameScene::createBox(float x, float y, float w, float h)
{
    _gameObjects.push_back(new CubeObject(&_world, _window->getRenderer(), x, y, w, h));
}

void GameScene::createDestructibleObject(float x, float y, std::vector<cv::Point>& points)
{
    _gameObjects.push_back(new DestructibleObject(&_world, _window->getRenderer(), _window->getWidth() / 2, _window->getHeight() / 2 - 128.0f, points));
}

void GameScene::createPlayer(float x, float y)
{
    _player = new Player(&_world, _window->getRenderer(), x, y);
    _gameObjects.push_back(_player);
    return;
}

void GameScene::reset()
{
/*
    for (GameObject* gameObject : _gameObjects)
    {
        delete gameObject;
    }
*/
    if (_vertexExtractor){
        std::vector<std::vector<cv::Point>> shapes = _vertexExtractor->getShapes();
        for (auto& shape : shapes)
        {
            if (shape.size() > 5){
            DestructibleObject *newObject = new DestructibleObject(&_world, _window->getRenderer(), 0,0, shape);
            _gameObjects.push_back(newObject);
            }
        }
    }
}
