package com.kewpie.nativepractice

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.kewpie.nativepractice.jni.JNIBasicType
import com.kewpie.nativepractice.load.JNIDynamicLoad
import com.kewpie.nativepractice.utils.LogUtil
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        // Example of a call to a native method
//        sample_text.text = stringFromJNI()
        var jniBasicType = JNIBasicType()
        sample_text.setOnClickListener {
            LogUtil.i("java show " + jniBasicType.callNativeInt(3))
            LogUtil.i("java show " + jniBasicType.callNativeShort(3.toShort()))
            LogUtil.i("java show " + jniBasicType.callNativeLong(3))

            LogUtil.i("java show " + jniBasicType.callNativeFloat(3f))
            LogUtil.i("java show " + jniBasicType.callNativeDouble(3.0))

            LogUtil.i("java show " + jniBasicType.callNativeChar('A'))
            LogUtil.i("java show " + jniBasicType.callNativeByte(2.toByte()))

            LogUtil.i("java show " + jniBasicType.callNativeBoolean(false))
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String


    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
