//
// Created by Kewpie Qin on 12/15/20.
//
#include <base.h>

extern "C"
JNIEXPORT jobject JNICALL
Java_com_kewpie_nativepractice_jni_JNIConstructorClass_invokeAnimalConstructors(JNIEnv *env,
                                                                                jobject thiz) {

    jclass cls = env->FindClass("com/kewpie/nativepractice/base/Animal");
    jmethodID jmethodId = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    jobject animal = env->NewObject(cls, jmethodId, env->NewStringUTF("dog"));
    return animal;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_kewpie_nativepractice_jni_JNIConstructorClass_allocObjectConstructor(JNIEnv *env,
                                                                              jobject thiz) {
    jclass cls = env->FindClass("com/kewpie/nativepractice/base/Animal");
    jmethodID jmethodId = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    jobject animal = env->AllocObject(cls);
    env->CallNonvirtualVoidMethod(animal,cls,jmethodId,env->NewStringUTF("lion"));
    return animal;
}
