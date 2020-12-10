package com.kewpie.nativepractice.jni;

import com.kewpie.nativepractice.base.Animal;

public class JNIAccessField {
    static {
        System.loadLibrary("native-lib");
    }

    public static int num = 0;

    public native void accessStaticField(Animal animal);

    public native void accessInstanceField(Animal animal);

    public static native void staticAccessInstanceField();
}
