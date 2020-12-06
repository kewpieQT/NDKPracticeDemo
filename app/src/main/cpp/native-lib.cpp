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

