#ifndef OPENCVSCENE_H
#define OPENCVSCENE_H

#include <iostream>
#include "window.h"
#include "scene.h"
#include <opencv2/opencv.hpp>
#include "vertexextractor.h"


class OpenCVScene : public Scene
{
    Window& _gameWindow;
    VertexExtractor *_vertexExtractor;
    SDL_Texture* _cameraTexture;
    int _hPointIndex;
public:
    OpenCVScene(Window& window, Window& gameWindow, VertexExtractor *vertexExtractor);
    ~OpenCVScene();

    virtual void draw() const;
    virtual void update(float deltaTime);
    virtual void handleEvent(const SDL_Event& event);
};

#endif // OPENCVSCENE_H
