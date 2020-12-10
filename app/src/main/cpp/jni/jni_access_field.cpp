//
// Created by Kewpie Qin on 12/10/20.
//
#include <base.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIAccessField_accessStaticField(JNIEnv *env, jobject thiz,
        jobject animal) {
    jclass cls = env->GetObjectClass(animal);

    jfieldID fid = env->GetStaticFieldID(cls,"num","I");

    jint newNum  = env->GetStaticIntField(cls,fid);

    env->SetStaticIntField(cls,fid,newNum+1);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIAccessField_accessInstanceField(JNIEnv *env, jobject thiz,
        jobject animal) {
    jclass cls = env->GetObjectClass(animal);

    jfieldID  fid = env->GetFieldID(cls,"name","Ljava/lang/String;");

    jstring str = env->NewStringUTF("this is new name");

    env->SetObjectField(animal,fid,str);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kewpie_nativepractice_jni_JNIAccessField_staticAccessInstanceField(JNIEnv *env,jclass clazz) {

    jfieldID fid = env->GetStaticFieldID(clazz,"num","I");

    jint newNum  = env->GetStaticIntField(clazz,fid);

    env->SetStaticIntField(clazz,fid,++newNum);
}