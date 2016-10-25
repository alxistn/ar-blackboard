#include "opencvscene.h"

OpenCVScene::OpenCVScene(Window& window)
    : Scene(window),_mode(0)
{
    _cap = new cv::VideoCapture(1);
    _cap->set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    _cap->set(cv::CAP_PROP_FRAME_HEIGHT, 1080);

    _chessBoardTexture = SDL_CreateTexture(_window->getRenderer(), SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_STATIC, _window->getHeight(), _window->getWidth());
}

OpenCVScene::~OpenCVScene()
{
    if (_chessBoardTexture){
        SDL_DestroyTexture(_chessBoardTexture);
    }
    cv::destroyAllWindows();
}

void OpenCVScene::draw() const
{
    if (_mode == 0){
            SDL_RenderCopy(_window->getRenderer(), _chessBoardTexture, NULL, NULL );
    }else{
    }

}

void OpenCVScene::update(float deltaTime)
{
    if (_cap){
    cv::Mat frame;
    *_cap >> frame;
    cv::waitKey(1);
    cv::imshow("frame", frame);
    }
    if (_mode == 0){

    }
}

void OpenCVScene::handleEvent(const SDL_Event& event)
{
}
