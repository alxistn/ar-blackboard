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


OpenCVScene::OpenCVScene(Window& window)
    : Scene(window), _mode(0)
{
    _cap.open(1);
    _cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    _cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
    _cameraTexture = SDL_CreateTexture(
            _window->getRenderer(),
            SDL_PIXELFORMAT_BGR24,
            SDL_TEXTUREACCESS_STREAMING,
            (int)_cap.get(cv::CAP_PROP_FRAME_WIDTH),
            (int)_cap.get(cv::CAP_PROP_FRAME_HEIGHT)
        );
}

OpenCVScene::~OpenCVScene()
{
    if (_cameraTexture){SDL_DestroyTexture(_cameraTexture);}
    cv::destroyAllWindows();
}

void OpenCVScene::draw() const
{
    if (_mode == 0 &&_cameraTexture){
        SDL_RenderCopy(_window->getRenderer(), _cameraTexture, NULL, NULL );
    }
}

void OpenCVScene::update(float deltaTime)
{
    if (_cap.isOpened()){
        cv::Mat frame;
        _cap >> frame;
        fillTexture(_cameraTexture, frame);
    }
}

void OpenCVScene::handleEvent(const SDL_Event& event)
{
    
}
