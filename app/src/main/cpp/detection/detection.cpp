//
// Created by qianb on 2018/11/14.
//

#include <string.h>
#include <stdlib.h>
#include <android/log.h>
#include <time.h>

#include "detection.h"

#define  LOG_TAG    "Detection"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG, __VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG, __VA_ARGS__)

static unsigned long get_current_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return (tv.tv_sec*1000000 + tv.tv_usec);
}

class only_for_extractor_auto_register
{
public:
    only_for_extractor_auto_register(const std::string& name, objDetector_factory::creator creator)
    {
        objDetector_factory::register_creator(name,creator);
    }

};

static objDetector * ncnn_mobilenetssd_creator(void)
{
    return new ncnn_mobilenetssd();
}


void detection::Init() {
    const char * type="ncnn";
    REGISTER_OBJDETECTOR_CREATOR(ncnn, ncnn_mobilenetssd_creator);

    p_detector = objDetector_factory::create_detector(type);
    if(p_detector==nullptr)
    {
        std::cerr<<type<<" is not supported"<<std::endl;
        std::cerr<<"supported types: ";
        std::vector<std::string> type_list=objDetector_factory::list();

        for(int i=0;i<type_list.size();i++)
            std::cerr<<" "<<type_list[i];

        std::cerr<<std::endl;

        LOGD("[%s] p_detector is NULL.....\n", __FUNCTION__);
        return;
    }

    p_detector->Init();

}

int detection::Detect(cv::Mat &bgr, std::vector<Object> &objects) {
    return p_detector->Detect(bgr, objects);
}

int detection::Detect_draw(cv::Mat &bgr) {
    unsigned long t1 = get_current_time();
    int res = p_detector->Detect_draw(bgr);
    t1 = get_current_time() - t1;
    LOGD("--------------- Detection time: %d ms\n", t1/1000);
    return res;

}

void detection::Quit() {
    delete p_detector;
    p_detector = NULL;
}