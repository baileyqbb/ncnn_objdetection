#include <jni.h>
#include <string>

#include "mobilenetssd.h"

extern "C" {

mobilenetssd mMobilenetSSD;

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
    mMobilenetSSD.Init();
}

JNIEXPORT jint JNICALL
Java_com_example_qianb_objdetectionncnn_MainActivity_DetectionDraw(
        JNIEnv *env,
        jobject instance,
        jlong matAddrframe) {
    cv::Mat &mRgb = *(cv::Mat *) matAddrframe;
    cv::cvtColor(mRgb,mRgb,cv::COLOR_RGBA2BGR);//opencv default work on BGR order without alpha
    int res = mMobilenetSSD.Detect_draw(mRgb);
    cv::cvtColor(mRgb,mRgb,cv::COLOR_BGR2RGBA);//change back to android mode
    return res;
}
}