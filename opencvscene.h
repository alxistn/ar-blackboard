#ifndef OPENCVSCENE_H
#define OPENCVSCENE_H

#include "scene.h"
#include <iostream>
#include <window.h>
#include <opencv2/opencv.hpp>
class OpenCVScene : public Scene
{
    cv::VideoCapture *_cap;

    SDL_Texture* _chessBoardTexture;
    int _mode;

public:
    OpenCVScene(Window& window);
    ~OpenCVScene();

    virtual void draw() const;
    virtual void update(float deltaTime);
    virtual void handleEvent(const SDL_Event& event);
};

#endif // OPENCVSCENE_H
