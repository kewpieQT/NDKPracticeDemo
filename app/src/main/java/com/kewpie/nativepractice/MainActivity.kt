package com.kewpie.nativepractice

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.kewpie.nativepractice.base.Animal
import com.kewpie.nativepractice.jni.*
import com.kewpie.nativepractice.load.JNIDynamicLoad
import com.kewpie.nativepractice.utils.LogUtil
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        // Example of a call to a native method
//        sample_text.text = stringFromJNI()

        chapter2_7()
    }

    fun chapter2_7(){
        val animal = Animal("dog")
        val jniAccessMethod = JNIAccessMethod()
        sample_text.setOnClickListener {
            jniAccessMethod.accessInstanceMethod(animal)
            jniAccessMethod.accessStaticMethod(animal)
        }
    }

    fun chapter2_6() {
        val jniAccessField = JNIAccessField()
        val animal = Animal("dog")
        sample_text.setOnClickListener {
            jniAccessField.accessStaticField(animal)
            jniAccessField.accessInstanceField(animal)

            JNIAccessField.staticAccessInstanceField()

            LogUtil.i("name is " + animal.name)
            LogUtil.i("num is " + Animal.num)
            LogUtil.i("static num is "+JNIAccessField.num)
        }
    }

    var strings = arrayOf("apple", "pear", "banana");

    fun chapter2_5() {
        var jniReferenceType = JNIReferenceType()
        sample_text.setOnClickListener {
            LogUtil.i("array item is " + jniReferenceType.callNativeStringArray(strings))
        }
    }

    fun chapter2_4() {
        var jniString = JNIString()
        sample_text.setOnClickListener {
            LogUtil.i(jniString.callNativeString("java string"))
            jniString.stringMethod("java string")
        }
    }

    fun chapter2_3() {
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
