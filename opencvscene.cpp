#include "opencvscene.h"

OpenCVScene::OpenCVScene(Window& window)
    : Scene(window),_mode(0)
{
//    _cap = new cv::VideoCapture(1);
//    _cap->set(cv::CAP_PROP_FRAME_WIDTH, 1920);
//    _cap->set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
//
//    _chessBoardTexture = SDL_CreateTexture(_window->getRenderer(), SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_STATIC, _window->getHeight(), _window->getWidth());
}

OpenCVScene::~OpenCVScene()
{
//    if (_chessBoardTexture){
//        SDL_DestroyTexture(_chessBoardTexture);
//    }
//    cv::destroyAllWindows();
}

void OpenCVScene::draw() const
{
    if (_mode == 0)
    {
        //fillScreenChest();
    }

}

void    OpenCVScene::fillScreenChest() const
{
    
}

void    OpenCVScene::fillScreenRed() const
{
    SDL_Rect fillRect = { 0, 0, _window->getWidth(), _window->getHeight()};
    SDL_SetRenderDrawColor( _window->getRenderer(), 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( _window->getRenderer(), &fillRect );
}

void    OpenCVScene::fillScreenGreen() const
{
    SDL_Rect fillRect = { 0, 0, _window->getWidth(), _window->getHeight()};
    SDL_SetRenderDrawColor( _window->getRenderer(), 0x00, 0xFF, 0x00, 0xFF );
    SDL_RenderFillRect( _window->getRenderer(), &fillRect );
}

void    OpenCVScene::fillScreenBleu() const
{
    SDL_Rect fillRect = { 0, 0, _window->getWidth(), _window->getHeight()};
    SDL_SetRenderDrawColor( _window->getRenderer(), 0x00, 0x00, 0xFF, 0xFF );
    SDL_RenderFillRect( _window->getRenderer(), &fillRect );
}

void    OpenCVScene::fillScreenBlack() const
{
    SDL_Rect fillRect = { 0, 0, _window->getWidth(), _window->getHeight()};
    SDL_SetRenderDrawColor( _window->getRenderer(), 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( _window->getRenderer(), &fillRect );
}

void    OpenCVScene::fillScreenWhite() const
{
    SDL_Rect fillRect = { 0, 0, _window->getWidth(), _window->getHeight()};
    SDL_SetRenderDrawColor( _window->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderFillRect( _window->getRenderer(), &fillRect );
}


void OpenCVScene::update(float deltaTime)
{
//    if (_cap){
//    cv::Mat frame;
//    *_cap >> frame;
//    cv::waitKey(1);
//    cv::imshow("frame", frame);
//    }
    if (_mode == 0){

    }
}

void OpenCVScene::handleEvent(const SDL_Event& event)
{
    
}
