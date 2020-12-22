//
// Created by Kewpie Qin on 12/21/20.
//

#include <jni.h>
#include <base.h>
#include <pthread.h>
#include <unistd.h>

void *printThreadHello(void *) {
    LOGI("hello thread");
    pthread_exit(0);
}

struct ThreadArg {
    int id;
    int result;
};

void *printThreadWithArgs(void *args) {
    ThreadArg *arg = static_cast<ThreadArg *>(args);
    LOGI("thread args id is %d", arg->id);
    LOGI("thread args result is %d", arg->result);
    return nullptr;
}

void *printThreadUseTime(void *args) {
    ThreadArg *arg = static_cast<ThreadArg *>(args);
    timeval start;
    LOGI("thread id is %d", arg->id);
    gettimeofday(&start, nullptr);

    sleep(3);

    timeval end;
    gettimeofday(&end, nullptr);

    LOGI("thread use time is %d", end.tv_sec - start.tv_sec);


    return reinterpret_cast<void *>(arg->result);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIThread_createNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t handler;
    pthread_create(&handler, nullptr, printThreadHello, nullptr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIThread_createNativeThreadWithArgs(JNIEnv *env, jobject thiz) {
    ThreadArg *arg = new ThreadArg;
    arg->id = 1;
    arg->result = 100;
    pthread_t handler;
    pthread_create(&handler, nullptr, printThreadWithArgs, arg);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIThread_joinNativeThread(JNIEnv *env, jobject thiz) {
    ThreadArg *arg = new ThreadArg;
    arg->id = 2;
    arg->result = 200;
    pthread_t handler;
    pthread_attr_t attr;

    int result = pthread_create(&handler, nullptr, printThreadUseTime, arg);

    void *ret = nullptr;
    pthread_join(handler, &ret);

    LOGI("result is %d", ret);
    LOGI("create thread result is %d", result);
}