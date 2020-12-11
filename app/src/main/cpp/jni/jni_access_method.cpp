//
// Created by Kewpie Qin on 12/11/20.
//
#include <base.h>
#include <string>

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIAccessMethod_accessStaticMethod(JNIEnv *env, jobject thiz,
                                                                      jobject animal) {
    jclass cls = env->GetObjectClass(animal);

    jmethodID jmId = env->GetStaticMethodID(cls, "callStaticMethod",
                                            "(Ljava/lang/String;)Ljava/lang/String;");

    env->CallStaticObjectMethod(cls, jmId, env->NewStringUTF("native string"));

}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIAccessMethod_accessInstanceMethod(JNIEnv *env, jobject thiz,
                                                                        jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jmethodID jmId = env->GetMethodID(cls, "callInstanceMethod", "(I)V");
    env->CallVoidMethod(animal, jmId, 10);



    jmethodID arrJmId = env->GetStaticMethodID(cls, "callStaticMethod",
                                               "([Ljava/lang/String;I)Ljava/lang/String;");
    jclass strClass = env->FindClass("java/lang/String");
    int size = 2;
    jobjectArray strArray = env->NewObjectArray(size, strClass, nullptr);
    jstring itemStr;
    for (int i = 0; i < size; ++i) {
        std::string str = "string in native " + std::to_string(i);
        itemStr = env->NewStringUTF(str.c_str());

        env->SetObjectArrayElement(strArray, i, itemStr);
    }
    env->CallStaticObjectMethod(cls, arrJmId, strArray, size);
}