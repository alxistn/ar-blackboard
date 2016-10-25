#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

class Scene;

class Window
{
private:
    int _width;
    int _height;
    std::string _title;

    SDL_Window* _window = NULL;
    SDL_Renderer* _renderer = NULL;
    SDL_Rect _viewPort;
    Uint32 _id;

    Scene* _scene = NULL;

    bool _hidden = false;

public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void draw() const;
    void update(float deltaTime);

    SDL_Renderer* getRenderer() const;
    const SDL_Rect& getViewPort() const;
    void setScene(Scene* scene);
    Scene* getScene() const;

    void handleEvent(const SDL_Event& event);
    void hide();
    void show();

    bool hidden() const;
};

#endif // WINDOW_H
