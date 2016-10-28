#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include <cstddef>
class Scene;

class Window
{
private:
    int _width;
    int _height;
    int _posx;
    int _posy;
    std::string _title;

    SDL_Window* _window = NULL;
    SDL_Renderer* _renderer = NULL;
    SDL_Rect _viewPort;
    Uint32 _id;

    Scene* _scene = NULL;

    bool _hidden = false;

public:
    Window(int x, int y, int w, int h, uint32_t flags, const std::string& title);
    ~Window();

    void draw() const;
    void update(float deltaTime);

    int             getHeight() const;
    int             getWidth() const;
    SDL_Renderer*   getRenderer() const;
    const SDL_Rect& getViewPort() const;
    void            deleteScene();
    Scene*          getScene() const;
    void            setScene(Scene* scene);


    void handleEvent(const SDL_Event& event);
    void hide();
    void show();

    bool hidden() const;
};

#endif // WINDOW_H
