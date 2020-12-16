package com.kewpie.nativepractice.jni;

public class JNIException {
    static {
        System.loadLibrary("native-lib");
    }

    public native void nativeInvokeJavaException();

    public native void nativeThrowException() throws IllegalArgumentException;

    private int operation() {
         return 2 / 0;
    }
}
