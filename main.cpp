
/*
#include <opencv2/opencv.hpp>
#include <vector>
#include <SDL2/SDL.h>

#define GAMEWINDOW_WIDTH 1600
#define GAMEWINDOW_HEIGHT 1200
int lowThreshold = 0;

void on_trackbar( int, void* )
{}
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
                cv::threshold(gray, threshold, 140,150,cv::THRESH_BINARY_INV);
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


///*




#include <iostream>

#include "window.h"
#include "opencvscene.h"
#include "gamescene.h"
#include "fpstimer.h"
#include <cstddef>
#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   768
#define WINDOW_TITLE    "Box2D Scene"

int main ()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::logic_error(SDL_GetError());

    //detect numbers of monitors
    SDL_DisplayMode monitorA;
    SDL_DisplayMode monitorB;
    uint32 flags;

    int vdn = SDL_GetNumVideoDisplays();
    SDL_Rect screens[2];
    if (vdn < 1)
        return 0;
    if (vdn == 1){
       SDL_GetCurrentDisplayMode(0, &monitorA);
       screens[0].x = 0;
       screens[0].y = 0;
       screens[0].h = monitorA.h;
       screens[0].w = monitorA.w / 2;
       screens[1].x = monitorA.h;
       screens[1].y = 0;
       screens[1].h = monitorA.h;
       screens[1].w = monitorA.w / 2;
       flags = SDL_WINDOW_BORDERLESS;
    }
    if (vdn >= 2){
       SDL_GetCurrentDisplayMode(1, &monitorA);
       SDL_GetCurrentDisplayMode(0, &monitorB);
       screens[0].x = 0;
       screens[0].y = 0;
       screens[0].h = monitorA.h;
       screens[0].w = monitorA.w;
       screens[1].x = 1920;
       screens[1].y = 0;
       screens[1].h = monitorB.h;
       screens[1].w = monitorB.w;
       flags = SDL_WINDOW_FULLSCREEN;
    }


    Window mainWindow(screens[1].x, screens[1].y,screens[1].w,screens[1].h, flags, WINDOW_TITLE);
    Window openCVWindow(screens[0].x, screens[0].y,screens[0].w,screens[0].h, flags, "opencv parameter");
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    GameScene gameScene(mainWindow);
    OpenCVScene openCVScene(openCVWindow, mainWindow);

    FPSTimer fpsTimer;
    fpsTimer.start();
    bool quit = false;
    SDL_Event event;
    while (quit == false) {

        //Events
        //Handle events on queue
        while(SDL_PollEvent(&event) != 0)
        {
            //User requests quit
            if (event.type == SDL_QUIT)
                quit = true;
            else {
                mainWindow.handleEvent(event);
                openCVWindow.handleEvent(event);
            }
        }
        if (openCVWindow.hidden() || mainWindow.hidden())
            quit = true;

        //Logic
        float time = fpsTimer.getFrameTime();
        mainWindow.update(time);
        openCVWindow.update(time);


        //Rendering
        mainWindow.draw();
        openCVWindow.draw();

        //Logic & Rendering
        //mainWindow.update(fpsTimer.getFrameTime());


        //Update FPSTimer (& Cap FPS)
        fpsTimer.update();
    }
    std::cout << "Closing Application." << std::endl;
    SDL_Quit();
}
//*/
