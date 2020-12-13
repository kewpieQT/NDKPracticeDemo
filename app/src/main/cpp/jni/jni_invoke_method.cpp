#include <jni.h>
#include <base.h>
#include <sys/types.h>
#include <pthread.h>
#include "jvm.h"

//
// Created by Kewpie Qin on 12/13/20.
//
void *threadCallback(void *);

static jclass  threadClazz;
static jmethodID threadMethod;
static jobject threadObject;

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIInvokeMethod_nativeCallback(JNIEnv *env, jobject thiz,
                                                                     jobject i_callback_method) {
    LOGI("NativeCallback");
    jclass cls = env->GetObjectClass(i_callback_method);
    jmethodID jmethodId = env->GetMethodID(cls,"callback", "()V");
    env->CallVoidMethod(i_callback_method,jmethodId);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIInvokeMethod_nativeThreadCallback(JNIEnv *env, jobject thiz,
                                                                        jobject i_thread_callback) {
    threadObject = env->NewGlobalRef(i_thread_callback);
    threadClazz = env->GetObjectClass(i_thread_callback);
    threadMethod = env->GetMethodID(threadClazz,"callback", "()V");

    pthread_t handle;
    pthread_create(&handle, nullptr,threadCallback, nullptr);
}

void *threadCallback(void *){
    JavaVM *gVM = getJvm();
    JNIEnv *env = nullptr;
    if (gVM->AttachCurrentThread(&env, nullptr)==0){

        env->CallVoidMethod(threadObject,threadMethod);
        gVM->DetachCurrentThread();
    }
    return 0;
}