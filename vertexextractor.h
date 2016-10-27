#ifndef VERTEEXTRACTOR_H
#define VERTEEXTRACTOR_H

#include <vector>
#include <window.h>
#include <opencv2/opencv.hpp>

class VertexExtractor
{
    cv::VideoCapture                    _cap;
    Window&                             _openCVWindow;
    Window&                             _gameWindow;
    cv::Mat                             _frame;
    cv::Mat                             _correctedRegion;
    cv::Mat                             _homographyMatrix;
    cv::Mat                             _threshold;
public:
    int                                 _threshold_upper;
    int                                 _threshold_lower;
private:
    std::vector<cv::Point2f>            _theoricalPoint;
    std::vector<cv::Point2f>            _gameProjectionPoints;
    std::vector<std::vector<cv::Point>> _contours;
    std::vector<cv::Vec4i>              _hierarchy;


public:
    VertexExtractor(int cameraId, Window& opencvWindow, Window& gameWindow);
    void                                updateFrame();
    cv::Mat                             getFrame()const;
    cv::Mat                             getCorrectedRegion()const;
    cv::Mat                             getThreshold()const;
    std::vector<std::vector<cv::Point>> getShapes()const;
    std::vector<cv::Point2f>            getHumographyPoints()const;
    void                                updateHumographyPoints(cv::Point2f up_left, cv::Point2f up_right, cv::Point2f down_right,cv::Point2f down_left);
    void                                updateHumographyPoints(int index, cv::Point2f pt);
    void                                updateHomography();
    void                                updateCorrectedRegion();
    void                                updateShapesOutlines();
};

#endif // VERTEEXTRACTOR_H
