package com.kewpie.nativepractice.base;

public class Animal {
    protected String name;

    public static int num = 0;

    public Animal(String name){this.name = name;}

    public String getName(){
        return this.name;
    }

    public static int getNum(){
        return num;
    }
}
