//
// Created by Kewpie Qin on 12/23/20.
//
#include <jvm.h>
#include <base.h>
#include <pthread.h>

pthread_cond_t cond;
pthread_mutex_t mutex;
int flag = 0;

void *wait(void *) {
    pthread_mutex_lock(&mutex);
    LOGD("start lock wait thread");
    while (flag == 0) {
        LOGD("waiting...");
        pthread_cond_wait(&cond, &mutex);
    }
    LOGD("start unlock wait thread");
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

void *notify(void *) {
    pthread_mutex_lock(&mutex);
    LOGI("start lock notify thread");

    flag = 1;

    LOGI("start unlock notify thread");
    pthread_mutex_unlock(&mutex);

    LOGI("start weak up wait thread");
    pthread_cond_signal(&cond);

    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIThread_waitNativeThread(JNIEnv *env, jobject thiz) {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_t waitHandler;
    pthread_create(&waitHandler, nullptr, wait, nullptr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIThread_notifyNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t notifyHandler;
    pthread_create(&notifyHandler, nullptr, notify, nullptr);
}
