#ifndef VERTEEXTRACTOR_H
#define VERTEEXTRACTOR_H

#include <vector>
#include <opencv2/opencv.hpp>

class VertexExtractor
{
    cv::VideoCapture _cap;
    cv::Mat _frame;
    std::vector<cv::Point2f> scene;

public:
    VertexExtractor();
    bool updateFrame();
    bool isMatrixSetup() const;
    void setupMatrix(const cv::Point2f corner_up_left,
                     const cv::Point2f corner_up_right,
                     const cv::Point2f corner_down_right,
                     const cv::Point2f corner_down_left);
};

#endif // VERTEEXTRACTOR_H
