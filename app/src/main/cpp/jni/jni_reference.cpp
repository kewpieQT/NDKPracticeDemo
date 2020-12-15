//
// Created by Kewpie Qin on 12/15/20.
//
#include "base.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_kewpie_nativepractice_jni_JNIReference_errorCacheLocalReference(JNIEnv *env,
                                                                         jobject thiz) {
    jclass cls = env->FindClass("java/lang/String");
    jmethodID jmethodId = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    jstring str = static_cast<jstring>(env->NewObject(cls, jmethodId,
                                                      env->NewStringUTF("myString")));
    env->DeleteLocalRef(cls);
    return str;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_kewpie_nativepractice_jni_JNIReference_cacheWithGlobalReference(JNIEnv *env,
                                                                         jobject thiz) {
    static jclass cls = nullptr;
    if (cls == nullptr) {
        jclass jcls = env->FindClass("java/lang/String");
        cls = static_cast<jclass>(env->NewGlobalRef(jcls));
        env->DeleteLocalRef(jcls);
        LOGD("init global class");
    } else {
        LOGD("use cached");
    }
    jmethodID jmethodId = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    return static_cast<jstring>(env->NewObject(cls, jmethodId, env->NewStringUTF("global ref")));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIReference_useWeakGlobalReference(JNIEnv *env, jobject thiz) {
    static jclass cls = nullptr;
    if (cls == nullptr){
      jclass jcls =  env->FindClass("java/lang/String");
      cls = static_cast<jclass>(env->NewWeakGlobalRef(jcls));
    }

    jboolean isNullClass = env->IsSameObject(cls, nullptr);
    if (!isNullClass){
        jmethodID jmethodId = env->GetMethodID(cls,"<init>","(Ljava/lang/String;)V");
        env->NewObject(cls,jmethodId,env->NewStringUTF("weak ref"));
    }

}