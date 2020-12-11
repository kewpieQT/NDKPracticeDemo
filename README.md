# NDKPracticeDemo
Android CMake以及NDK实践基础 https://www.imooc.com/learn/1212

## Java 与 JNI 的交互
### 2-2 函数的动态注册
**优点：**
未使用动态注册时，调用 native 方法，会根据包名、类名、函数名、形参列表去 C 层寻找匹配的函数。
使用动态注册后，可以省去查找匹配的时间，提高程序的运行效率。

**动态注册的实现关键 ：JNI_OnLoad 函数**
（对应代码：src/main/cpp/jni/jni_dynamic_load.cpp）

&emsp;&emsp;当 Android 执行 System.loadLibrary() 函数时，首先会去执行 C 组件里的 JNI_OnLoad() 函数，在函数内部通过调用env->RegisterNatives() 函数，将 Java 中定义的 native 函数与 C++ 中的实现函数绑定起来，并注册到系统中去。

**学习本节课程遇到的其它问题**

**问题：** 

&emsp;&emsp;LOGD只能在native-lib.cpp才能打印出日志,而在其他.cpp文件中就会报错: error: undefined reference to '__android_log_print'

**解决方案：**

&emsp;&emsp;在 CMakeLists.txt 文件中新建一个 target_link_libraries 函数，将log日志库与其它 .cpp 编译的 lib 动态库链接。 
&emsp;&emsp;target_link_libraries 内部也会受到排列顺序的影响，将其它 .cpp 文件编译的动态库名字放在第一个，就可以正常打印 log，但是有可能会导致其它库中 .cpp 运行时出现 undefined reference 错误。

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

