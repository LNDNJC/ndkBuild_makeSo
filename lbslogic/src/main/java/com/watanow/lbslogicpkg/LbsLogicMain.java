package com.watanow.lbslogicpkg;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class LbsLogicMain {
    static {
        System.loadLibrary("lbslogic");
    }

    public native int ndkLbsLogic(int a, int b);

    public native void ndkLbsArrayLogic(ArrayList<Integer> array);

    public native void ndkLbsStringLogic(String str);
}
