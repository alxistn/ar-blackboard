#include "window.h"

#include <stdexcept>
#include <string>
#include <random>

Window::Window(int width, int height, const std::string& title)
    : _width(width), _height(height), _title(title)
{
    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);
    if (_window == NULL)
       throw std::logic_error(SDL_GetError());
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == NULL)
       throw std::logic_error(SDL_GetError());
    SDL_RenderGetViewport(_renderer, &_viewPort);
}

Window::~Window()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void Window::draw() const
{
    //Reset view port and clear buffer
    SDL_RenderSetViewport(_renderer, &_viewPort);
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Draw scene
    if (_scene != NULL)
        _scene->draw(_renderer);

    //Swap buffer
    SDL_RenderPresent(_renderer);
}

void Window::update(float deltaTime)
{
    //Game engine
    if (_scene != NULL)
        _scene->update(deltaTime);

    //Render
    draw();
}

const SDL_Rect& Window::getViewPort() const
{
    return _viewPort;
}

void Window::setScene(Scene* scene)
{
    _scene = scene;
}
