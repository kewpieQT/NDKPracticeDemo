package com.kewpie.nativepractice.base;

import com.kewpie.nativepractice.utils.LogUtil;

public class Animal {
    protected String name = "duck";

    public static int num = 0;
    public Animal(){}

    public Animal(String name){this.name = name;}

    public String getName(){
        return this.name;
    }

    public static int getNum(){
        return num;
    }

    //C++ 调用 Java 的实例方法
    public void callInstanceMethod(int num){
        LogUtil.Companion.i("call instance method and num is "+num);
    }

    //C++ 调用 Java 的类静态方法
    public static String callStaticMethod(String str){
        if (str != null){
            LogUtil.Companion.i("call static method with " + str);
        }else{
            LogUtil.Companion.i("call static method with null");
        }
        return "";
    }

    public static String callStaticMethod(String[] strs,int num){
        if (strs!=null){
            for (String str : strs){
                LogUtil.Companion.i("str in array is " + str);
            }
        }
        return "";
    }
}
