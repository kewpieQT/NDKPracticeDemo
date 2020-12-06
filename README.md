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