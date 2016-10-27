#include "vertexextractor.h"

VertexExtractor::VertexExtractor(int cameraId, Window& openCVWindow, Window& gameWindow)
    :_cap(cameraId),_openCVWindow(openCVWindow), _gameWindow(gameWindow)
{
    //setup camera (should be 1920 1080)
    _cap.open(cameraId);
    _cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    _cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);

    _theoricalPoint.push_back(cv::Point2f(0,0));
    _theoricalPoint.push_back(cv::Point2f(0,_gameWindow.getHeight()));
    _theoricalPoint.push_back(cv::Point2f(_gameWindow.getWidth(),_gameWindow.getHeight()));
    _theoricalPoint.push_back(cv::Point2f(_gameWindow.getWidth(),0));

    _gameProjectionPoints.push_back(cv::Point2f(535,185));
    _gameProjectionPoints.push_back(cv::Point2f(469,937));
    _gameProjectionPoints.push_back(cv::Point2f(1561,968));
    _gameProjectionPoints.push_back(cv::Point2f(1527,203));
    updateFrame();
    updateHomography();
}

void VertexExtractor::updateFrame()
{
    _cap >> _frame;
}

cv::Mat VertexExtractor::getFrame()const
{
    return _frame;
}

cv::Mat VertexExtractor::getCorrectedRegion()const
{
    return _correctedRegion;
}

cv::Mat VertexExtractor::getThreshold() const
{
    return _threshold;
}

std::vector<std::vector<cv::Point> > VertexExtractor::getShapes() const
{
    return _contours;
}

std::vector<cv::Point2f> VertexExtractor::getHumographyPoints() const
{
    return _gameProjectionPoints;
}

void VertexExtractor::updateHumographyPoints(cv::Point2f up_left, cv::Point2f up_right, cv::Point2f down_right, cv::Point2f down_left)
{
    _gameProjectionPoints.clear();
    _gameProjectionPoints.push_back(up_left);
    _gameProjectionPoints.push_back(up_right);
    _gameProjectionPoints.push_back(down_right);
    _gameProjectionPoints.push_back(down_left);

}

void VertexExtractor::updateHumographyPoints(int index, cv::Point2f pt)
{
    _gameProjectionPoints[index] = pt;
}

void VertexExtractor::updateHomography()
{
    _homographyMatrix = cv::findHomography(_gameProjectionPoints, _theoricalPoint);
}

void VertexExtractor::updateCorrectedRegion()
{
    cv::warpPerspective(_frame,
                        _correctedRegion,
                        _homographyMatrix,
                        cv::Size(_gameWindow.getWidth(), _gameWindow.getHeight()));
}

void VertexExtractor::updateShapesOutlines()
{
    cv::Mat gray;
    cv::Mat threshold;
    cv::cvtColor(_correctedRegion, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, threshold, 140,150,cv::THRESH_BINARY_INV);

    cv::Mat dst = cv::Mat::zeros(threshold.rows, threshold.cols, CV_8UC3);
    _contours.clear();
    _hierarchy.clear();
    cv::findContours( threshold, _contours, _hierarchy,
        CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE );
    std::vector<std::vector<cv::Point>> newList;
    std::vector<cv::Point> newShape;

    for (std::vector<cv::Point>& shape : _contours){
        newShape.clear();
        cv::Point& pa = shape[0];
        newShape.push_back(shape[0]);
        for (cv::Point &pts : shape){
            if (cv::norm(pa-pts) > 10){
                newShape.push_back(pts);
                pa = pts;
            }
        }
        if (newShape.size() < 10)
            continue;
        newList.push_back(newShape);
    }
    _contours = newList;

}
