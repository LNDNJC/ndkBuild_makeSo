package com.watanow.lbslogicpkg;

import android.util.Log;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class LbsLogicMain {
    static {
        System.loadLibrary("lbslogic");
    }

    public void func()
    {
        System.out.println("func");
    }

    public String  callback(String str, int a)
    {
        Log.e("Java", "callback : " + a);

        return "ok";
    }

    public static void callback_for_thread(int i)
    {
        Log.e("Java", "callback_for_thread : " + i);
    }

    public native int ndkLbsLogic(int a, int b);

    public native void ndkLbsIntArrayLogic(int []arr);

    public native void ndkLbsStringLogic(String str);

    public native void ndkLogic();

    public native void ndkLogicInt(int i);

    public native void ndkLogicChar(char c);

    public native void ndkLogicCharArray(char []c);

    public native int startThread();

    public native int endThread();

    public native String getNumString(String str, int num);

}
