//
// Created by Kewpie Qin on 12/4/20.
//

#ifndef NATIVEPRACTICE_BASE_H
#define NATIVEPRACTICE_BASE_H

#include <android/log.h>
#include <jni.h>

#define LOG_TAG "NativeMethod"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif //NATIVEPRACTICE_BASE_H
