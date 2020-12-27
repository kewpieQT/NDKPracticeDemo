# NDKPracticeDemo
Android CMake以及NDK实践基础 https://www.imooc.com/learn/1212

## Java 与 JNI 的交互
### 2-2 函数的动态注册
**优点：**
未使用动态注册时，调用 native 方法，会根据包名、类名、函数名、形参列表去 native 层寻找匹配的函数。
使用动态注册后，可以省去查找匹配的时间，提高程序的运行效率。

**动态注册的实现关键 ：JNI_OnLoad 函数**
（对应代码：src/main/cpp/jni/jni_dynamic_load.cpp）

&emsp;&emsp;当 Android 执行 System.loadLibrary() 函数时，首先会去执行 C 组件里的 JNI_OnLoad() 函数，在函数内部通过调用env->RegisterNatives() 函数，将 Java 中定义的 native 函数与 C++ 中的实现函数绑定起来，并注册到系统中去。

**学习本节课程遇到的其它问题**

**问题：** 

&emsp;&emsp;LOGD只能在native-lib.cpp才能打印出日志,而在其他.cpp文件中就会报错: error: undefined reference to '__android_log_print'

**解决方案：**

&emsp;&emsp;在 CMakeLists.txt 文件中新建一个 target_link_libraries 函数，将log日志库与待编译的目标库链接。 
&emsp;&emsp;target_link_libraries 内部会受到排列顺序的影响，放在第一个的是等待编译的目标库，其它的是依赖库。
~~将其它 .cpp 文件编译的动态库名字放在第一个，就可以正常打印 log，但是有可能会导致其它库中 .cpp 运行时出现 undefined reference 错误。~~

### 2-3 JNI 中基础数据类型转换

* JNI 中基础类型的定义
* Java 与 JNI 中的基础数据类型转换实践

Java 与 JNI 中的基础数据类型基本都是一致的，下面代码是给 C/C++ 中的基础数据类型定义一个与 Java 中的基础数据类型相对应的别名，便于理解使用。（别名去掉 "j" 就是 Java 中的基础数据类型了）


```
typedef uint8_t  jboolean; /* unsigned 8 bits */
typedef int8_t   jbyte;    /* signed 8 bits */
typedef uint16_t jchar;    /* unsigned 16 bits */
typedef int16_t  jshort;   /* signed 16 bits */
typedef int32_t  jint;     /* signed 32 bits */
typedef int64_t  jlong;    /* signed 64 bits */
typedef float    jfloat;   /* 32-bit IEEE 754 */
typedef double   jdouble;  /* 64-bit IEEE 754 */
```

### 2-4 JNI 中字符串类型转换
（对应代码：src/main/cpp/jni/jni_string.cpp）

* JNI 中字符串类型的定义
* Java 中的字符串与 JNI 中字符串的转换调用实践
* JNI 中字符串操作的必备函数

Java 的字符串不能直接转成 C/C++ 风格的字符串，需要用到 GetStringChars 或者 GetStringUTFChars 相应的函数来转换，使用完毕后记得释放该指针的内存。（具体的相关操作请在代码中查看）

### 2-5 JNI 中引用类型转换 
（对应代码：src/main/cpp/jni/jni_reference_type.cpp）

* JNI 中引用类型的定义
* Java 中引用类型与 JNI 中引用类型的转换调用实践

其它知识点：


```
//获取目录中所有源文件的地址保存在 SOURCE_FILES 中。
aux_source_directory(. SOURCE_FILES)
aux_source_directory(./jni JNI_SOURCE_FILES)

//将 JNI_SOURCE_FILES 地址列表添加到 SOURCE_FILES 中
list(APPEND SOURCE_FILES ${JNI_SOURCE_FILES})

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        
        //提供需要编译的源文件地址
        //使用这种方式添加，避免了每次新建 .cpp 文件时，都需要手动添加该文件
        //如果新添加的文件无法正常编译链接
        //删除 app 目录下的 「.cxx」 及 「build」 文件夹，再点击 sync 进行编译 
       ${SOURCE_FILES})
```
### 2-6 JNI 访问 Java 类字段
（对应代码：src/main/cpp/jni/jni_access_field.cpp）

* 通过 JNI 去访问 Java 类中的字段
* 访问并修改类实例的字段
* 访问并修改类的静态字段

### 2-7 JNI 访问 Java 类方法
（对应代码：src/main/cpp/jni/jni_access_method.cpp）

* 通过 JNI 去访问 Java 类中的方法
* 访问 Java 类实例的方法
* 访问 Java 类的静态方法

### 2-8 JNI 子线程回调 Java 方法
（对应代码：src/main/cpp/jni/jni_invoke_method.cpp）

* JNI 函数内回调 Java 方法
* JNI 函数通过接口参数回调 Java 方法
* JNI 子线程如何回调 Java 的主线程方法

1、2 个函数操作步骤与 2-7 一致。

JNI 子线程如何回调 Java 的主线程方法（知识点与注意事项）：
1. Java 调用 Native 方法时所传递的 env 参数无法跨线程使用。
2. 可以在 JNI_OnLoad 方法中保存 static jvm 指针，在子线程中通过 jvm->AttachCurrentThread() 方法获取当前子线程的 env 指针。
3. 最后调用 Java 函数的步骤同上（切记调用 jvm->DetachCurrentThread() 方法）。 

### 2-9 JNI 创建 Java 类
（对应代码：src/main/cpp/jni/jni_constructor_class.cpp）

* JNI 调用类的构造方法创建类实例
* 两种不同的实现方式(NewObject、AllocObject)

共同点：两个方法都是用于构建一个新的类对象。
不同点：AllocObject 仅仅构建一个新的类对象（仅仅为类的对象分配内存空间），不初始化成员变量，也不调用构造函数。

NewObject 需要指明调用的构造方法，构建一个新的对象，并初始化成员变量。

### 3-1 JNI 引用类型管理
（对应代码：src/main/cpp/jni/jni_reference.cpp）
* 全局引用(NewGlobalRef)
* 局部引用(NewLocalRef)
* 弱引用(NewWeakGlobalRef)

局部引用在使用完成之后，需要及时释放引用(DeleteLocalRef)，避免因局部引用变多导致内存溢出，尤其是在循环体中创建局部引用。

### 3-2 JNI 异常处理
（对应代码：src/main/cpp/jni/jni_exception.cpp）
* JNI 调用 Java 方法时的异常处理

```
//判断是否发生异常
jthrowable exc = env->ExceptionOccurred();
    if(exc){
        //打印异常信息
        env->ExceptionDescribe();
        //清除异常，避免程序崩溃
        env->ExceptionClear();
    }
```
* 在 JNI 中抛出异常，交由上层处理

```
//创建需要抛出的异常类型
jclass cls = env->FindClass("java/lang/IllegalArgumentException");
//使用 ThrowNew 抛出异常，交由上层处理
env->ThrowNew(cls,"native throw exception");
```
### 4-1 JNI 线程的创建
（对应代码：src/main/cpp/thread/jni_thread.cpp）

* Posix API介绍以及线程库
* 线程创建和销毁操作
* 线程的同步操作

通过 pthread_create 创建线程。

```
int pthread_create(pthread_t* __pthread_ptr, pthread_attr_t const* __attr, void* (*__start_routine)(void*), void*);
```

四个参数按顺序分别为 「线程句柄」、「线程属性」、「线程执行函数」、「线程执行函数所需参数」。
返回值为 0 表示线程创建成功，非 0 表示创建失败。

销毁线程：
线程需要在「线程执行函数」中显示的销毁线程，否则会导致程序崩溃。
具体方法有：return 或 pthread_exit(0);

线程通过 pthread_join 同步线程。
```
int pthread_join(pthread_t __pthread, void** __return_value_ptr);
```

当前线程等待__pthread 线程执行完成后才继续执行，通过__return_value_ptr 获取__pthread 「线程执行函数」的返回值。
### 4-2 JNI 线程的同步
（对应代码：src/main/cpp/thread/jni_wait_notify.cpp）
* pthread_mutex_t 互斥锁
* pthread_cond_t 条件变量

加锁：pthread_mutex_lock(&mutex);

解锁：pthread_mutex_unlock(&mutex);

线程等待：pthread_cond_wait(&cond, &mutex);

线程唤醒：pthread_cond_signal(&cond);

加锁、解锁必须成对使用，避免死锁。
加锁后使线程等待，直接解锁会导致`Waiting for a blocking GC ProfileSaver`，请唤醒线程后再解锁。

当在另外一个加锁的线程中唤醒等待中的线程，必须等当前线程解锁后才会通知唤醒操作。

#### 实践案例
使用以上线程相关概念，实现一个简单的生产者消费者模型。（对应代码：src/main/cpp/thread/jni_product_and_consumer.cpp）

创建一个生产者线程负责生产商品，创建一个消费者线程负责消费商品。

如果商品数量大于9，视为爆仓不再生产商品。

每秒生产一个商品，每9秒消耗一个商品。

为了不爆仓，商品数量等于9时挂起生产者线程，等待消耗商品后通知生产者继续生产。（为了方便观察，消耗完商品后再唤醒生产线程继续生产商品）
### 4-3 JNI Bitmap 操作
* NDK 中的 Bitmap API 使用介绍
* 在 JNI 获取 Bitmap 的相关信息以及像素操作

```
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
```