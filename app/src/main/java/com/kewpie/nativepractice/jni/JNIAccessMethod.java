package com.kewpie.nativepractice.jni;

import com.kewpie.nativepractice.base.Animal;

public class JNIAccessMethod {
    static {
        System.loadLibrary("native-lib");
    }

    public native void accessStaticMethod(Animal animal);

    public native void accessInstanceMethod(Animal animal);
}
