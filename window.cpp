#include "window.h"
#include "scene.h"

#include <stdexcept>
#include <string>
#include <random>
#include <iostream>

Window::Window(int x, int y, int w, int h, uint32 flags, const std::string& title)
    : _width(w), _height(h),_posx(x),_posy(y), _title(title)
{
    _window = SDL_CreateWindow(_title.c_str(), _posx, _posy, _width, _height, flags);
    if (_window == NULL)
       throw std::logic_error(SDL_GetError());
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == NULL)
       throw std::logic_error(SDL_GetError());
    SDL_RenderGetViewport(_renderer, &_viewPort);
    _id = SDL_GetWindowID(_window);
}

Window::~Window()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void Window::draw() const
{
    if (hidden())
        return;

    //Reset view port and clear buffer
    SDL_RenderSetViewport(_renderer, &_viewPort);
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Draw scene
    if (_scene != NULL)
        _scene->draw();

    //Swap buffer
    SDL_RenderPresent(_renderer);
}

void Window::update(float deltaTime)
{
    if (hidden())
        return;

    //Game engine
    if (_scene != NULL)
        _scene->update(deltaTime);
}

SDL_Renderer* Window::getRenderer() const
{
    return _renderer;
}

const SDL_Rect& Window::getViewPort() const
{
    return _viewPort;
}

void Window::deleteScene()
{
    if (_scene) {
        delete _scene;
        _scene = NULL;
    }
}

void Window::setScene(Scene* scene)
{
    _scene = scene;
    if (_scene->getWindow() != this)
        _scene->setWindow(this);
}

Scene* Window::getScene() const
{
    return _scene;
}

int Window::getWidth() const
{
    return _width;
}

int Window::getHeight() const
{
    return _height;
}

void Window::handleEvent(const SDL_Event& event)
{
    /*
    ** Window Events
    */
    //Here the window handles window specific events
    if(event.type == SDL_WINDOWEVENT && event.window.windowID == _id)
    {
        switch(event.window.event)
        {
            //Hide on close
            case SDL_WINDOWEVENT_CLOSE:
            hide();
            break;
        }
    }

    /*
    ** Scene Events
    */
    if (SDL_GetWindowFlags(_window) & SDL_WINDOW_INPUT_FOCUS)
        _scene->handleEvent(event);
}

void Window::hide()
{
    SDL_HideWindow(_window);
    _hidden = true;
}

void Window::show()
{
    SDL_ShowWindow(_window);
    _hidden = false;
}

bool Window::hidden() const
{
    return _hidden;
}

void Window::focus(){
    SDL_RaiseWindow(_window);
}
