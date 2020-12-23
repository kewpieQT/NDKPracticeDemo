package com.kewpie.nativepractice.jni;

public class JNIThread {
    static {
        System.loadLibrary("native-lib");
    }

    public native void createNativeThread();

    public native void createNativeThreadWithArgs();

    public native void joinNativeThread();

    public native void waitNativeThread();

    public native void notifyNativeThread();

    public native void startProductAndConsumerThread();
}
