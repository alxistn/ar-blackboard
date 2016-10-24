#include "window.h"

#include <stdexcept>
#include <string>
#include <random>
#include <iostream>

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
        _scene->draw(_renderer);

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

const SDL_Rect& Window::getViewPort() const
{
    return _viewPort;
}

void Window::setScene(Scene* scene)
{
    _scene = scene;
}

Scene* Window::getScene()
{
    return _scene;
}

#include "gamescene.h"
void Window::handleEvent(const SDL_Event& event)
{
    /*
    ** Window Events
    */

    //Here the window handle some key events
    if(event.type == SDL_KEYDOWN && SDL_GetWindowFlags(_window) & SDL_WINDOW_INPUT_FOCUS)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_UP:
                std::cout << "Key up pressed on Window " << _id << std::endl;
            break;

            case SDLK_DOWN:
                std::cout << "Key down pressed on Window " << _id << std::endl;
            break;

            case SDLK_LEFT:
                std::cout << "Key left pressed on Window " << _id << std::endl;
            break;

            case SDLK_RIGHT:
                std::cout << "Key right pressed on Window " << _id << std::endl;
            break;

            default:
                std::cout << "A key was pressed on Window " << _id << std::endl;
            break;
        }
    }
    //Here the window handles window specific events
    else if(event.type == SDL_WINDOWEVENT && event.window.windowID == _id)
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
