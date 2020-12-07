package com.kewpie.nativepractice.utils

import android.util.Log

class LogUtil {
    companion object {
        var TAG = "NavtiveMethod"

        fun d(msg: String) {
            d(msg, tag = TAG)
        }

        fun d(msg: String, tag: String = TAG) {
            Log.d(tag, msg)
        }

        fun i(msg: String) {
            i(msg, tag = TAG)
        }

        fun i(msg: String, tag: String = TAG) {
            Log.i(tag, msg)
        }

        fun e(msg: String) {
            e(msg, tag = TAG)
        }

        fun e(msg: String, tag: String = TAG) {
            Log.e(tag, msg)
        }
    }
}