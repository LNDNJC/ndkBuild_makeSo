//
// Created by HCH on 2020-01-30.
//
#define LOG_TAG "LbsProcess"

#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include "com_watanow_lbslogicpkg_LbsLogicMain.h"

#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

jstring getNumString(JNIEnv * a, jobject b, jstring str, jint num)
{
    jclass cls = a->GetObjectClass(b);
    jmethodID func = a->GetMethodID(cls, "callback", "(Ljava/lang/String;I)Ljava/lang/String;");
    LOGI("getNumString");

    return (jstring)a->CallObjectMethod(b, func, str, num);
    //
    //return str;
}

static const char* classPathName = "com/watanow/lbslogicpkg/LbsLogicMain";

static JNINativeMethod methods[] = {
        {"getNumString", "(Ljava/lang/String;I)Ljava/lang/String;", (void*)getNumString},
};

//Register several native methods for one class
int registerNativeMethods(JNIEnv* env, const char* className, JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;

    clazz = env->FindClass(className);
    if(clazz==NULL)
    {
        LOGE("Native registration unable to find class '%s'", className);
        return JNI_FALSE;
    }


    //실제 네이티브와 자바간에 함수를 연결한다.
    if(env->RegisterNatives(clazz, gMethods, numMethods) < 0)
    {
        LOGE("RegisterNatives failed for '%s'", className);
        return JNI_FALSE;
    }
    return JNI_TRUE;
}


//Register native methods for all classes we know about
int registerNatives(JNIEnv* env)
{
    if(!registerNativeMethods(env, classPathName, methods, sizeof(methods)/sizeof(methods[0])))
    {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

//This is called by the VM when the shared library is first loaded
typedef union
{
    JNIEnv* env;
    void* venv;
}UnionJNIEnvToVoid;


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    UnionJNIEnvToVoid uenv;
    uenv.venv = NULL;
    jint result = -1;
    JNIEnv* env = NULL;

    LOGI("JNI_OnLoad");

    if(vm->GetEnv(&uenv.venv, JNI_VERSION_1_6) != JNI_OK)
    {
        LOGE("ERROR: GetEnv failed");
        goto bail;
    }
    env = uenv.env;

    if(registerNatives(env) != JNI_TRUE)
    {
        LOGE("ERROR: registerNatives failed");
        goto bail;
    }

    result = JNI_VERSION_1_6;

    bail:
    return result;
}

JNIEXPORT jint JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLbsLogic
(JNIEnv *env, jobject obj, jint a, jint b)
{
     // 자바 클래스 적재함.
     jclass cls = env->GetObjectClass(obj);

     // 메소드 ID를 구한다. func가 함수명이며 함수 타입은 ()V다.
     jmethodID  funcM = env->GetMethodID( cls, "func", "()V");
     if( funcM == 0 )
     {
         LOGE("Method func ?? \n");
     }
     else
     {
         LOGI("Method func ok ....... \n");
          // 메소드를 호출한다.
          env->CallVoidMethod(obj, funcM, (jint)a, (jint)b);
     }

     return a+b;
}

JNIEXPORT void JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLbsIntArrayLogic
        (JNIEnv *env, jobject obj, jintArray c)
{
    jint *A = NULL;
    A = env->GetIntArrayElements( c, NULL);
    if( A == NULL )
    {
        LOGE("error1");
    }
    LOGI("ndkLbsIntArrayLogic : %d %d %d \n", A[0], A[1], A[2]);

    //env->ReleaseCharArrayElements(c, )
}

JNIEXPORT void JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLbsStringLogic
        (JNIEnv *env, jobject obj, jstring c)
{
    char strbuf[128];
    const char *sz = env->GetStringUTFChars(c, 0);
    strcpy(strbuf, sz);
    LOGI("show6 : %s", strbuf);
    env->ReleaseStringUTFChars(c, sz);

}

JNIEXPORT void JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLogic
        (JNIEnv *env, jobject obj)
{


}

JNIEXPORT void JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLogicInt
        (JNIEnv *env, jobject obj, jint c)
{
    LOGI("ndkLogicInt : %d \n", c);

}

JNIEXPORT void JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLogicChar
        (JNIEnv *env, jobject obj, jchar c)
{
    LOGI("ndkLogicChar : %c \n", c);

}

JNIEXPORT void JNICALL Java_com_watanow_lbslogicpkg_LbsLogicMain_ndkLogicCharArray
        (JNIEnv *env, jobject obj, jcharArray c)
{
    jchar *A = NULL;
    A = env->GetCharArrayElements( c, NULL);
    if( A == NULL )
    {
        LOGE("error1");
    }
    LOGI("ndkLogicCharArray : %c %c %c \n", A[0], A[1], A[2]);

    //env->ReleaseCharArrayElements(c, )

}


