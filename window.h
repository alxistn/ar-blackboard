#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

#include "scene.h"

class Window
{
private:
    int _width;
    int _height;
    std::string _title;

    SDL_Window* _window = NULL;
    SDL_Renderer* _renderer = NULL;
    SDL_Rect _viewPort;

    Scene* _scene = NULL;

public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void draw() const;
    void update(float deltaTime);

    const SDL_Rect& getViewPort() const;
    void setScene(Scene* scene);
};

#endif // WINDOW_H
