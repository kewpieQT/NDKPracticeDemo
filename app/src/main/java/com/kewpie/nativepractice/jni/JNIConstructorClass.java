package com.kewpie.nativepractice.jni;

import com.kewpie.nativepractice.base.Animal;

public class JNIConstructorClass {
    static{
        System.loadLibrary("native-lib");
    }

    public native Animal invokeAnimalConstructors();

    public native Animal allocObjectConstructor();
}
