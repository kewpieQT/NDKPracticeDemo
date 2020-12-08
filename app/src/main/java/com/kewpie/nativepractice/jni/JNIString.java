package com.kewpie.nativepractice.jni;

public class JNIString {
    static{
        System.loadLibrary("native-lib");
    }

    public native String callNativeString(String str);

    public native void stringMethod(String str);
}
