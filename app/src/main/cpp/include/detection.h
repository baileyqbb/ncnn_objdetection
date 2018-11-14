//
// Created by qianb on 2018/11/14.
//

#ifndef OBJDETECTIONNCNN_DETECTION_H
#define OBJDETECTIONNCNN_DETECTION_H

#include "ncnn_mobilenetssd.h"

class detection{
public:
    void Init();
    int Detect(cv::Mat& bgr, std::vector<Object>& objects);
    int Detect_draw(cv::Mat& bgr);
    void Quit();

private:
    objDetector* p_detector;
};

#endif //OBJDETECTIONNCNN_DETECTION_H
