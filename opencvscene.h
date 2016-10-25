#ifndef OPENCVSCENE_H
#define OPENCVSCENE_H

#include <iostream>
#include <window.h>
//#include <opencv2/opencv.hpp>
#include "scene.h"

class OpenCVScene : public Scene
{
//    cv::VideoCapture *_cap;

    SDL_Texture* _chessBoardTexture;
    int _mode;

public:
    OpenCVScene(Window& window);
    ~OpenCVScene();

    virtual void draw() const;
    virtual void update(float deltaTime);
    virtual void handleEvent(const SDL_Event& event);

    void    fillScreenChest() const;
    void    fillScreenRed() const;
    void    fillScreenGreen() const;
    void    fillScreenBleu() const;
    void    fillScreenBlack() const;
    void    fillScreenWhite() const;
};

#endif // OPENCVSCENE_H
