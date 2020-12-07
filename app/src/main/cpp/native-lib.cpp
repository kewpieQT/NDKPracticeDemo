#include <jni.h>
#include <string>
#include <base.h>
#include "people/people.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_kewpie_nativepractice_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    people p;

    return env->NewStringUTF(p.getString().c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_kewpie_nativepractice_jni_JNIBasicType_callNativeInt(JNIEnv *env, jobject thiz, jint num) {
    LOGD("java int value is %d",num);
    int c_num = num * 2;
    return c_num;
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_com_kewpie_nativepractice_jni_JNIBasicType_callNativeByte(JNIEnv *env, jobject thiz, jbyte b) {
    LOGD("java byte value is %d",b);
    jbyte c_byte = b + (jbyte)10;
    return c_byte;
}

extern "C"
JNIEXPORT jchar JNICALL
Java_com_kewpie_nativepractice_jni_JNIBasicType_callNativeChar(JNIEnv *env, jobject thiz, jchar c) {
    LOGD("java char value is %c",c);
    jchar c_char = c + (jchar)3;
    return c_char;
}

extern "C"
JNIEXPORT jshort JNICALL
Java_com_kewpie_nativepractice_jni_JNIBasicType_callNativeShort(JNIEnv *env, jobject thiz,
                                                 jshort sh) {
    LOGD("java short value is %d",sh);
    jshort c_short = sh + (jshort)10;
    return c_short;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_kewpie_nativepractice_jni_JNIBasicType_callNativeLong(JNIEnv *env, jobject thiz, jlong l) {
    LOGD("java long value is %lld",l);
    jlong c_long = l + 100;
    return c_long;
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_kewpie_nativepractice_jni_JNIBasicType_callNativeFloat(JNIEnv *env, jobject thiz,
                                                                jfloat f) {
    LOGD("java float value is %f",f);
    jfloat c_float = f + (jfloat)10.0;
    return c_float;
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_kewpie_nativepractice_jni_JNIBasicType_callNativeDouble(JNIEnv *env, jobject thiz,
                                                   jdouble d) {
    LOGD("java double value is %f",d);
    jdouble c_double = d + 20.0;
    return c_double;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_kewpie_nativepractice_jni_JNIBasicType_callNativeBoolean(JNIEnv *env, jobject thiz,
                                                                  jboolean b) {
    LOGD("java boolean value is %d",b);
    jboolean c_boolean = (jboolean)!b;
    return c_boolean;
}