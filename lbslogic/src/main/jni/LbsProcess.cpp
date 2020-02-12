//
// Created by HCH on 2020-01-30.
//

#include <stdio.h>
#include <string.h>
#include "com_watanow_lbslogicpkg_LbsLogicMain.h"

JNIEXPORT jint JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLbsLogic
(JNIEnv *env, jobject obj, jint a, jint b)
{
     // 자바 클래스 적재함.
     jclass cls = env->GetObjectClass(obj);

     // 메소드 ID를 구한다. func가 함수명이며 함수 타입은 ()V다.
     jmethodID  funcM = env->GetMethodID( cls, "func", "()V");
     if( funcM == 0 )
     {
          printf("Method func ?? \n");
     }
     else
     {
          printf("Method func ok ....... \n");
          // 메소드를 호출한다.
          env->CallVoidMethod(obj, funcM, (jint)a, (jint)b);
     }

     return a+b;
}

JNIEXPORT void JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLbsArrayLogic
        (JNIEnv *env, jobject obj, jintArray c)
{
    jint *A = NULL;
    A = env->GetIntArrayElements( c, NULL);
    if( A == NULL )
    {
        printf("error1");
    }
    printf("show3 : %d %d %d \n", A[0], A[1], A[2]);

    //env->ReleaseCharArrayElements(c, )
}

JNIEXPORT void JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLbsStringLogic
        (JNIEnv *env, jobject obj, jstring c)
{
    char strbuf[128];
    const char *sz = env->GetStringUTFChars(c, 0);
    strcpy(strbuf, sz);
    printf("show6 : %s", strbuf);
    env->ReleaseStringUTFChars(c, sz);

}


