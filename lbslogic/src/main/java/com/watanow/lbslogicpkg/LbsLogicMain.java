package com.watanow.lbslogicpkg;

public class LbsLogicMain {
    static {
        System.loadLibrary("lbslogic");
    }

    public native int ndkLbsLogic(int a, int b);
}
