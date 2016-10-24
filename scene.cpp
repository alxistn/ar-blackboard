#include "scene.h"
#include <iostream>
Scene::Scene(const SDL_Rect& viewPort)
    : _width(viewPort.w - viewPort.x), _height(viewPort.y - viewPort.h), _viewPort(viewPort)
{
}
