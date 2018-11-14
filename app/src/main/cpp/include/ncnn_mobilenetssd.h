//
// Created by qianb on 2018/11/13.
//

#ifndef OBJDETECTIONNCNN_MOBILENETSSD_H
#define OBJDETECTIONNCNN_MOBILENETSSD_H
#include <stdio.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ncnn/net.h"
#include "objDetector.h"


class ncnn_mobilenetssd: public objDetector{
public:
    ncnn_mobilenetssd() = default;
    ~ncnn_mobilenetssd();
    void Init();
    int Detect(cv::Mat& bgr, std::vector<Object>& objects);
    int Detect_draw(cv::Mat& bgr);
    void Quit();

private:
    ncnn::Net m_mobilenet;
    const float mean_vals[3] = {127.5f, 127.5f, 127.5f};
    const float norm_vals[3] = {1.0/127.5,1.0/127.5,1.0/127.5};
    const int target_size = 300;

};


#endif //OBJDETECTIONNCNN_MOBILENETSSD_H
