#include "scene.h"
#include "window.h"
#include <iostream>

Scene::Scene(const SDL_Rect& viewPort)
    : _width(viewPort.w - viewPort.x), _height(viewPort.h - viewPort.y), _viewPort(viewPort)
{
}

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
