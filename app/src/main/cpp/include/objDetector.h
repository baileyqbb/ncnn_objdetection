//
// Created by qianb on 2018/11/14.
//

#ifndef OBJDETECTIONNCNN_OBJDETECTOR_H
#define OBJDETECTIONNCNN_OBJDETECTOR_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

struct Object
{
    cv::Rect_<float> rect;
    int label;
    float prob;
};

class objDetector {
public:
    virtual void Init()=0;
    virtual int Detect(cv::Mat& bgr, std::vector<Object>& objects)=0;
    virtual int Detect_draw(cv::Mat& bgr)=0;
    //virtual void Quit()=0;
    virtual ~objDetector(){};
};

/*** factory part ***/

class objDetector_factory
{
public:

    typedef objDetector * (*creator)(void);

    static void register_creator(const std::string& name, creator& create_func);
    static objDetector * create_detector(const std::string& name);
    static std::vector<std::string> list(void);

private:
    objDetector_factory(){};


};

class  only_for_auto_register
{
public:
    only_for_auto_register(std::string name, objDetector_factory::creator func)
    {
        objDetector_factory::register_creator(name,func);
    }

};

#define REGISTER_OBJDETECTOR_CREATOR(name,func) \
	static  only_for_auto_register dummy_objDetector_creator_## name (#name, func)

#endif //OBJDETECTIONNCNN_OBJDETECTOR_H
