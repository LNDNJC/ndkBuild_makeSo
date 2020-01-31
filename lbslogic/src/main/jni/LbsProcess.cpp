//
// Created by HCH on 2020-01-30.
//

#include "com_watanow_lbslogicpkg_LbsLogicMain.h"

JNIEXPORT jint JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLbsLogic
(JNIEnv *env, jobject obj, jint a, jint b)
{

     return a+b;
}

