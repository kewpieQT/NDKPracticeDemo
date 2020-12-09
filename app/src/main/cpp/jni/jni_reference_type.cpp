//
// Created by Kewpie Qin on 12/9/20.
//
#include <base.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_kewpie_nativepractice_jni_JNIReferenceType_callNativeStringArray(JNIEnv *env, jobject thiz,
                                                                          jobjectArray str_array) {
    int len = env->GetArrayLength(str_array);
    LOGD("len is %d", len);

    jstring firstString = static_cast<jstring>(env->GetObjectArrayElement(str_array, 0));
    const char *str = env->GetStringUTFChars(firstString, 0);
    LOGD("first str is %s", str);
    env->ReleaseStringUTFChars(firstString, str);

    return env->NewStringUTF(str);
}