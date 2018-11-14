#include <jni.h>
#include <string>

#include "detection.h"

extern "C" {

detection m_detection;

JNIEXPORT jstring JNICALL
Java_com_example_qianb_objdetectionncnn_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT void JNICALL
Java_com_example_qianb_objdetectionncnn_MainActivity_DetectionInit(
        JNIEnv *env,
        jobject) {
    m_detection.Init();
}

JNIEXPORT jint JNICALL
Java_com_example_qianb_objdetectionncnn_MainActivity_DetectionDraw(
        JNIEnv *env,
        jobject instance,
        jlong matAddrframe) {
    cv::Mat &mRgb = *(cv::Mat *) matAddrframe;
    cv::cvtColor(mRgb,mRgb,cv::COLOR_RGBA2BGR);//opencv default work on BGR order without alpha
    int res = m_detection.Detect_draw(mRgb);
    cv::cvtColor(mRgb,mRgb,cv::COLOR_BGR2RGBA);//change back to android mode
    return res;
}
}