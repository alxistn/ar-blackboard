#include "opencvscene.h"
#include <vector>

static void fillTexture(SDL_Texture * texture, cv::Mat const &mat)
{
    unsigned char * texture_data = NULL;
    int texture_pitch = 0;

    SDL_LockTexture(texture, 0, (void **)&texture_data, &texture_pitch);
    memcpy(texture_data, (void *)mat.data, mat.size().height * mat.size().width * mat.channels());
    SDL_UnlockTexture(texture);
}


OpenCVScene::OpenCVScene(Window& window, Window& gameWindow)
    : Scene(window), _gameWindow(gameWindow), _mode(0), _hPointIndex(0)
{
    _vertexExtractor = new VertexExtractor(1,window, gameWindow);
    _cameraTexture = SDL_CreateTexture(
            _window->getRenderer(),
            SDL_PIXELFORMAT_BGR24,
            SDL_TEXTUREACCESS_STREAMING,
            _window->getWidth(),
            _window->getHeight()
        );
}

OpenCVScene::~OpenCVScene()
{
    if (_cameraTexture){SDL_DestroyTexture(_cameraTexture);}
}

void OpenCVScene::draw() const
{
    if (_cameraTexture){
        SDL_RenderCopy(_window->getRenderer(), _cameraTexture, NULL, NULL );
    }
}

void OpenCVScene::update(float deltaTime)
{
    cv::Mat dst = cv::Mat::zeros(_window->getHeight(), _window->getWidth(), CV_8UC3);
    _vertexExtractor->updateFrame();
    if (_mode == 0){
        _vertexExtractor->getFrame().copyTo(dst);
        std::vector<cv::Point2f> gameProjectionPoints = _vertexExtractor->getHumographyPoints();
        cv::line(dst, gameProjectionPoints[0], gameProjectionPoints[1],cv::Scalar(0,0,200), 3, 4);
        cv::line(dst, gameProjectionPoints[1], gameProjectionPoints[2],cv::Scalar(0,0,200), 3, 4);
        cv::line(dst, gameProjectionPoints[2], gameProjectionPoints[3],cv::Scalar(0,0,200), 3, 4);
        cv::line(dst, gameProjectionPoints[3], gameProjectionPoints[0],cv::Scalar(0,0,200), 3, 4);
    }
    if (_mode == 1){
        _vertexExtractor->updateCorrectedRegion();

        cv::resize(_vertexExtractor->getCorrectedRegion(),
                   dst(cv::Rect(0,0,_gameWindow.getWidth()/2, _gameWindow.getHeight()/2)),
                   cv::Size(_gameWindow.getWidth()/2, _gameWindow.getHeight()/2));

        cv::Mat tmp = _vertexExtractor->getCorrectedRegion();
        std::vector<std::vector<cv::Point>> shapes = _vertexExtractor->getShapes();
        for (std::vector<cv::Point>& shape : shapes){
             cv::Scalar color( rand()&255, rand()&255, rand()&255 );
             int size = shape.size() - 1;
             cv::line(dst, shape[0], shape[size], color);
             while (size - 1 >= 0){
                 cv::line(tmp, shape[size], shape[size - 1], color);
                 size--;
             }
        }
        cv::resize(tmp,
                   dst(cv::Rect(_gameWindow.getWidth()/2,0,_gameWindow.getWidth()/3, _gameWindow.getHeight()/3)),
                   cv::Size(_gameWindow.getWidth()/3, _gameWindow.getHeight()/3));


    }
    fillTexture(_cameraTexture, dst);
}

void OpenCVScene::handleEvent(const SDL_Event& event)
{   
    switch (event.type)
    {
    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
            case SDLK_a: _hPointIndex = 0; break;
            case SDLK_z: _hPointIndex = 3; break;
            case SDLK_q: _hPointIndex = 1; break;
            case SDLK_s: _hPointIndex = 2; break;
            case SDLK_w:
                _mode = 0;
                break;
            case SDLK_x:
                _mode = 1;
                break;
            case SDLK_c:
            if (_mode == 1){
                _vertexExtractor->updateShapesOutlines();
            }
            break;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        switch (event.button.button)
        {
            case SDL_BUTTON_LEFT:
                _vertexExtractor->updateHumographyPoints(_hPointIndex, cv::Point2f(event.motion.x,event.motion.y));
                //_vertexExtractor->updateHomography();
                break;
        }
        break;
    }
}
