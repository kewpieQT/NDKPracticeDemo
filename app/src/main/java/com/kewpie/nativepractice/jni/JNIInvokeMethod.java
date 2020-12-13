package com.kewpie.nativepractice.jni;

import com.kewpie.nativepractice.base.ICallbackMethod;
import com.kewpie.nativepractice.base.IThreadCallback;

public class JNIInvokeMethod {
    static{
        System.loadLibrary("native-lib");
    }

    public native void nativeCallback(ICallbackMethod iCallbackMethod);

    public native void nativeThreadCallback(IThreadCallback iThreadCallback);
}
