//
// Created by Kewpie Qin on 12/16/20.
//
#include <base.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIException_nativeInvokeJavaException(JNIEnv *env,
                                                                          jobject thiz) {
    jclass cls = env->GetObjectClass(thiz);
    jmethodID jmethodId = env->GetMethodID(cls, "operation", "()I");

    jmethodID mid2 = env->GetMethodID(cls, "<init>", "()V");
    jobject obj = env->NewObject(cls, mid2);
    env->CallIntMethod(obj, jmethodId);

    jthrowable exc = env->ExceptionOccurred();
    if(exc){
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIException_nativeThrowException(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("java/lang/IllegalArgumentException");
    env->ThrowNew(cls,"native throw exception");
}