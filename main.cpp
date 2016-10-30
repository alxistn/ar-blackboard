///*

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <opencv2/opencv.hpp>

#include "window.h"
#include "vertexextractor.h"

//?????????????
#include <iostream>

#include "scene.h"
#include "opencvscene.h"
#include "gamescene.h"
#include "fpstimer.h"
#include <cstddef>
//??????????????

int start (Window *gameWindow, Window *openCVWindow, VertexExtractor *vertexExtractor)
{
  new GameScene(*gameWindow, vertexExtractor);

  if (openCVWindow)new OpenCVScene(*openCVWindow, *gameWindow, vertexExtractor);


  FPSTimer fpsTimer;
  fpsTimer.start();
  bool quit = false;
  SDL_Event event;
  while (quit == false) {

    //Events
    //Handle events on queue
    while(SDL_PollEvent(&event) != 0)
      {
    switch (event.type)
      {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYUP:
        if (vertexExtractor == NULL)
          break;
        switch (event.key.keysym.sym)
          {
          case SDLK_F1:
        vertexExtractor->setMode(0);
        gameWindow->deleteScene();
        break;
          case SDLK_F2:
        vertexExtractor->setMode(1);
        gameWindow->deleteScene();
        break;
          case SDLK_F3:
        vertexExtractor->setMode(1);
        gameWindow->deleteScene();
        vertexExtractor->updateShapesOutlines();
        break;
          case SDLK_F4:
        vertexExtractor->setMode(1);
        gameWindow->deleteScene();
        gameWindow->setScene(new GameScene(*gameWindow));
        static_cast<GameScene*>(gameWindow->getScene())->addShapes(vertexExtractor->getShapes());
        vertexExtractor->setMode(2);
        break;
          }
      }
    gameWindow->handleEvent(event);
    if (openCVWindow)openCVWindow->handleEvent(event);
      }
    if (openCVWindow && openCVWindow->hidden())
      quit = true;
    if(gameWindow->hidden())
      quit = true;

    //Logic
    float time = fpsTimer.getFrameTime();
    gameWindow->update(time);
    if (openCVWindow)openCVWindow->update(time);


    //Rendering
    gameWindow->draw();
    if (openCVWindow)openCVWindow->draw();

    //Update FPSTimer (& Cap FPS)
    fpsTimer.update();
  }
  return 0;
}


static int     findCamera(const int width, const int height){
    cv::VideoCapture    cap;
    int index = 0;
    int camHeight = 0;
    int camWidth = 0;

    while (index < 10){
        try{
            cap.open(index);
        }
        catch(cv::Exception){
            return -1;
        }

        if (cap.isOpened()){
            camWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
            camHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
            cap.release();
            if (camHeight == height && camWidth == width)
                return index;
        }
        index++;
    }
    return -1;
}


static SDL_DisplayMode* findMonitor(const std::vector<SDL_DisplayMode*>& monitors,
                                    const int width,
                                    const int height){
    for (auto monitor : monitors) {
        if (monitor == NULL)
            return NULL;
        if (monitor->h == height && monitor->w == width){
            return monitor;
        }
    }
    return NULL;
}

int main(){
    Window*             gameWindow = NULL;
    Window*             openCVWindow = NULL;
    VertexExtractor*    vertexExtractor = NULL;
    int                 cameraId;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::logic_error(SDL_GetError());
    findCamera(1920, 1080);
    std::cout << "ok" << std::endl;
    /*
    * detection ecrans
    */

    int vdn = SDL_GetNumVideoDisplays();
    if (vdn < 1){
        std::cout << "no video display connected" << std::endl;
        return 0;
    }
    std::vector<SDL_DisplayMode*> monitors;
    int index = vdn;
    while (index){
        SDL_DisplayMode *monitor = new SDL_DisplayMode;
         if (SDL_GetCurrentDisplayMode(--index, monitor) != 0)
             throw std::logic_error(SDL_GetError());
         std::cout << "width: " << monitor->w << " height: " << monitor->h << std::endl;
         monitors.push_back(monitor);
    }
    /*
    * selection de l'ecran
    */
    if (vdn > 0){
        SDL_DisplayMode* gameMonitor = findMonitor(monitors, 1920, 1080);
        if (gameMonitor == NULL)
            throw std::logic_error("cant find monitor for game");
        int flag = SDL_WINDOW_FULLSCREEN;
        if (vdn == 1) {
            flag = 0;
            gameMonitor->w = 800;
            gameMonitor->h = 600;
        }
        gameWindow = new Window(0,
                                0,
                                gameMonitor->w,
                                gameMonitor->h,
                                flag,
                                "game");
        if (vdn > 1){
            SDL_DisplayMode* openCVMonitor = findMonitor(monitors, 1800, 1600);
            if (openCVMonitor == NULL)
                throw std::logic_error("cant find monitor for openCV");
            gameWindow = new Window(gameMonitor->w,
                                    gameMonitor->h,
                                    openCVMonitor->w,
                                    openCVMonitor->h,
                                    SDL_WINDOW_FULLSCREEN,
                                    "configuration");
            cameraId = findCamera(1920,1080);
            if (cameraId < 0){
                throw std::logic_error("cant find right camera");
            }
            vertexExtractor = new VertexExtractor(cameraId, *openCVWindow, *gameWindow);
        }
        SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
        start(gameWindow, openCVWindow, vertexExtractor);
    }
    std::cout << "Closing Application." << std::endl;
    SDL_Quit();
    return 0;
}

//*/
/*
#include <opencv2/opencv.hpp>
#include <vector>
#include <SDL2/SDL.h>

#define GAMEWINDOW_WIDTH 1600
#define GAMEWINDOW_HEIGHT 1200
int lowThreshold = 0;

int main(){
    cv::VideoCapture    cap(1);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
    cv::Mat             _frame;
    cv::Mat             _correctedRegion(GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, CV_8UC3, cv::Scalar(0,0,255));

    cv::Mat                     _homographyMatrix;
    std::vector<cv::Point2f>    _theoricalPoint;
    std::vector<cv::Point2f>    _gameProjectionPoints;

    _theoricalPoint.push_back(cv::Point2f(0,0));
    _theoricalPoint.push_back(cv::Point2f(0,GAMEWINDOW_WIDTH));
    _theoricalPoint.push_back(cv::Point2f(GAMEWINDOW_HEIGHT,GAMEWINDOW_WIDTH));
    _theoricalPoint.push_back(cv::Point2f(GAMEWINDOW_HEIGHT,0));

    _gameProjectionPoints.push_back(cv::Point2f(535,185));
    _gameProjectionPoints.push_back(cv::Point2f(469,937));
    _gameProjectionPoints.push_back(cv::Point2f(1561,968));
    _gameProjectionPoints.push_back(cv::Point2f(1527,203));

    _gameProjectionPoints[0] = cv::Point2f(541,186);
    _gameProjectionPoints[3] = cv::Point2f(1533,204);
    _gameProjectionPoints[1] = cv::Point2f(475,943);
    _gameProjectionPoints[2] = cv::Point2f(1568,967);

    _homographyMatrix = cv::findHomography(_gameProjectionPoints, _theoricalPoint);

    std::vector<std::vector<cv::Point>> _contours;
    std::vector<cv::Vec4i> _hierarchy;


    if (cap.isOpened()){
        std::cerr << "capture device is open" << std::endl;
        while (true){
            if (cap.read(_frame)){
                //cv::line(frame, gameProjectionPoints[0], gameProjectionPoints[1],cv::Scalar(0,0,200), 3, 4);
                //cv::line(frame, gameProjectionPoints[1], gameProjectionPoints[2],cv::Scalar(0,0,200), 3, 4);
                //cv::line(frame, gameProjectionPoints[2], gameProjectionPoints[3],cv::Scalar(0,0,200), 3, 4);
                //cv::line(frame, gameProjectionPoints[3], gameProjectionPoints[0],cv::Scalar(0,0,200), 3, 4);

                //cv::imshow("frame", frame);

                // begin of work area extraction
                cv::warpPerspective(_frame,
                                    _correctedRegion,
                                    _homographyMatrix,
                                    cv::Size(GAMEWINDOW_HEIGHT, GAMEWINDOW_WIDTH));
                // to remove at the end of the debug
                cv::resize(_correctedRegion,_correctedRegion,cv::Size(GAMEWINDOW_WIDTH / 2, GAMEWINDOW_HEIGHT / 2));

                cv::imshow("corrected region", _correctedRegion);
                // end of work area extraction

                cv::Mat gray;
                cv::Mat threshold;
                cv::cvtColor(_correctedRegion, gray, cv::COLOR_BGR2GRAY);
                cv::threshold(gray, threshold,190,255,cv::THRESH_BINARY);
                cv::imshow("gray", gray);
                cv::imshow("threshold", threshold);

                cv::Mat dst = cv::Mat::zeros(threshold.rows, threshold.cols, CV_8UC3);
                _contours.clear();
                _hierarchy.clear();
                findContours( threshold, _contours, _hierarchy,
                    CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

                int idx = 0;
                for( ; idx >= 0; idx = _hierarchy[idx][0] )
                {
                    cv::Scalar color( rand()&255, rand()&255, rand()&255 );
                    cv::drawContours( dst, _contours, idx, color, 2, 8, _hierarchy );
                }

                cv::imshow("contours", dst);

            }
        cv::waitKey(1);
        }
    }

    cap.release();
}


//*/
