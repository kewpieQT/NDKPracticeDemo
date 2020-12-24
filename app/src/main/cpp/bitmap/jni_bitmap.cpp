//
// Created by Kewpie Qin on 12/24/20.
//
#include <base.h>
#include <android/bitmap.h>
#include <cstring>

jobject generateBitmap(JNIEnv *env, uint32_t width, uint32_t height);

extern "C"
JNIEXPORT jobject JNICALL
Java_com_kewpie_nativepractice_jni_JNIBitmap_callNativeMirrorBitmap(JNIEnv *env, jobject thiz,
                                                                    jobject bitmap) {

    //存储 Bitmap 的相关信息
    AndroidBitmapInfo bitmapInfo;
    //将 bitmap 的相关信息存放到 bitmapInfo 中
    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);
    LOGD("bitmap width is %d", bitmapInfo.width);
    LOGD("bitmap height is %d", bitmapInfo.height);

    //指向一个数组的指针，用于存储 Bitmap 的像素信息
    //注意这里是一个一维数组
    //bitmap 的像素通常来说是一个二维数组
    //这里将每一行的像素添加到上一行的末尾，形成一个一维数组
    //处理的时候通过 bitmap 的 width 去分段处理
    void *bitmapPixels;
    
    //获取 Bitmap 的像素信息
    AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels);

    //注意类型是 uint32_t
    uint32_t width = bitmapInfo.width;
    uint32_t height = bitmapInfo.height;

    //原始像素索引
    int idx = 0;
    //创建一个数组用于存放镜像处理后的像素
    uint32_t *mirrorBitmapPixels = new uint32_t[width * height];
    for (int i = 0; i < height; ++i) {//逐行遍历
        for (int j = width - 1; j >= 0; --j) {//获取当前行的镜像像素位置索引
            //顺序遍历每一个像素
            uint32_t pixel = ((uint32_t *) bitmapPixels)[idx++];
            //放到镜像数组中对应的镜像点
            mirrorBitmapPixels[width * i + j] = pixel;
        }
    }
    //解锁
    AndroidBitmap_unlockPixels(env, bitmap);

    //通过调用 Java 方法创建一个空的 bitmap，具体操作参考 2-7 JNI 访问 JAVA 类方法
    //public static Bitmap createBitmap(int width, int height, @NonNull Config config)
    jobject newBitmap = generateBitmap(env, width, height);

    //获取空的 bitmap 的像素数组
    void *newBitmapPixels;
    AndroidBitmap_lockPixels(env, newBitmap, &newBitmapPixels);

    //拷贝镜像后的像素数组，放置到空的 bitmap 的像素数组中去
    //注意最后一个长度参数，需要考虑 uint32_t 类型的因素
    memcpy((uint32_t *) newBitmapPixels, mirrorBitmapPixels, sizeof(uint32_t) * width * height);

    AndroidBitmap_unlockPixels(env, newBitmap);

    //释放不用的内存
    delete[] mirrorBitmapPixels;
    return newBitmap;
}

jobject generateBitmap(JNIEnv *env, uint32_t width, uint32_t height) {

    jclass bitmapClz = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmapFunction = env->GetStaticMethodID(bitmapClz, "createBitmap",
                                                            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

    jstring configName = env->NewStringUTF("ARGB_8888");
    jclass bitmapConfigClass = env->FindClass("android/graphics/Bitmap$Config");

    jmethodID valueOfBitmapConfigFunction = env->GetStaticMethodID(bitmapConfigClass, "valueOf",
                                                                   "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");


    jobject config = env->CallStaticObjectMethod(bitmapConfigClass, valueOfBitmapConfigFunction,
                                                 configName);


    jobject bitmap = env->CallStaticObjectMethod(bitmapClz, createBitmapFunction, width, height,
                                                 config);

    return bitmap;
}