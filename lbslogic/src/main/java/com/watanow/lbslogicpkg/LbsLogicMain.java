package com.watanow.lbslogicpkg;

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

    public native int ndkLbsLogic(int a, int b);

    public native void ndkLbsArrayLogic(int []arr);

    public native void ndkLbsStringLogic(String str);
}
