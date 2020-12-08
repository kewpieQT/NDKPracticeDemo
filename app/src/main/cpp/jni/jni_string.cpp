//
// Created by Kewpie Qin on 12/8/20.
//

#include <base.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_kewpie_nativepractice_jni_JNIString_callNativeString(JNIEnv *env, jobject thiz,
                                                              jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);
    LOGD("java string is %s", str);

    env->ReleaseStringUTFChars(str_, str);

    return env->NewStringUTF("this is C style string");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIString_stringMethod(JNIEnv *env, jobject thiz, jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);

    char buf[128];
    int len = env->GetStringUTFLength(str_);

    LOGD("java string length is %d", len);
    env->GetStringUTFRegion(str_, 0, len, buf);
    //直接打印 C 风格字符串会在尾部出现乱码
    //不使用 UTF 编码的相关方法，只打印出字符串的第一个字符
    LOGD("C style jstring is %s", buf);

    //转换成 string 类型后显示正常
    std::string s(str);
    s = s.substr(0, len - 1);
    LOGD("C++ style jstring is %s", s.data());

    env->ReleaseStringUTFChars(str_, str);
}