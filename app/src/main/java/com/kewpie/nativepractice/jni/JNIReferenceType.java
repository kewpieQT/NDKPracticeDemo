package com.kewpie.nativepractice.jni;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class JNIReferenceType {
    static{
        System.loadLibrary("native-lib");
    }
    public native String callNativeStringArray(String[] strArray);
}
