#include "scene.h"
#include "window.h"
#include <iostream>

Scene::Scene(Window& window)
    : _window(&window)
{
    _window->setScene(this);
}

Scene::~Scene(){}

void Scene::setWindow(Window* window)
{
    _window = window;
        if (_window->getScene() != this)
            _window->setScene(this);
}

Window* Scene::getWindow() const
{
    return _window;
}
