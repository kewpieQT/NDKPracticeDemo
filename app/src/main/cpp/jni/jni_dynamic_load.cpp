//
// Created by Kewpie Qin on 12/4/20.
//
#include <base.h>
#include <jvm.h>
#define JAVA_CLASS "com/kewpie/nativepractice/load/JNIDynamicLoad"
jstring getMessage(JNIEnv *env,jobject jobj){
    return env->NewStringUTF("this is msg");
}

jint plus(JNIEnv * env,jobject jobj,int x ,int y){
    return x+y;
}
static JNINativeMethod gMethod[] =  {{"getNativeString","()Ljava/lang/String;",(void *)getMessage},{"sum","(II)I",(void *)plus}};

int registerNativeMethods(JNIEnv *env,const char* name,const JNINativeMethod* methods,
                          jint nMethods){
    jclass jcls;
    jcls = env->FindClass(name);
    if (jcls== nullptr){
        return JNI_FALSE;
    }
    if (env->RegisterNatives(jcls,methods,nMethods)<0){
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved){
    JNIEnv *env;
    if(vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK){
        return JNI_FALSE;
    }

    //把我们的C方法动态注册到系统中去
    //当JAVA层调用Native方法时，就不用根据包名、函数名、形参列表去一个个匹配方法
    //而是可以直接在系统中调用对应的方法，提高我们软件运行的速度。
    registerNativeMethods(env,JAVA_CLASS,gMethod,2);
    LOGD("jni onload call");
    return JNI_VERSION_1_6;
}