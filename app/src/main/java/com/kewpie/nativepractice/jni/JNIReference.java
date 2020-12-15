package com.kewpie.nativepractice.jni;

public class JNIReference {
    static{
        System.loadLibrary("native-lib");
    }
    public native String errorCacheLocalReference();

    public native String cacheWithGlobalReference();

    public native void useWeakGlobalReference();
}
