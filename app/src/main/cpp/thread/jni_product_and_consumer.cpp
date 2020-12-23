//
// Created by Kewpie Qin on 12/23/20.
//
#include <jvm.h>
#include <base.h>
#include <pthread.h>
#include <queue>
#include <unistd.h>

using namespace std;
std::queue<int> data;

pthread_mutex_t dataMutex;
pthread_cond_t dataCond;

void *product(void *) {
    while (data.size() < 10) {
        pthread_mutex_lock(&dataMutex);
        LOGI("product lock");

        LOGI("product goods");
        data.push(1);

        if (data.size() >= 9) {
            LOGI("product wait");
            pthread_cond_wait(&dataCond, &dataMutex);
        }

        LOGI("product unlock");
        pthread_mutex_unlock(&dataMutex);

        LOGI("product sleep");
        sleep(1);
    }

    pthread_exit(0);
}

void *consumer(void *) {
    while (1) {
        pthread_mutex_lock(&dataMutex);
        LOGD("consumer lock");
        if (data.size() > 0) {
            LOGD("consumer goods");
            data.pop();
        }
        if (data.size() <= 0) {
            LOGD("consumer weak up");
            pthread_cond_signal(&dataCond);
        }

        LOGD("consumer unlock");
        pthread_mutex_unlock(&dataMutex);
        LOGD("consumer sleep");
        sleep(9);
    }

    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIThread_startProductAndConsumerThread(JNIEnv *env,
                                                                           jobject thiz) {
    pthread_t productHandler;
    pthread_t consumerHandler;

    pthread_cond_init(&dataCond, nullptr);
    pthread_mutex_init(&dataMutex, nullptr);

    pthread_create(&productHandler, nullptr, product, nullptr);
    pthread_create(&consumerHandler, nullptr, consumer, nullptr);

}