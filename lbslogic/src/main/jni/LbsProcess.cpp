//
// Created by HCH on 2020-01-30.
//
#define LOG_TAG "LbsProcess"

#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "com_watanow_lbslogicpkg_LbsLogicMain.h"
#include "LbsMainLogic.h"

#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

int thr_id;
int end_flag;
static const char* classPathName = "com/watanow/lbslogicpkg/LbsLogicMain";
jclass jObject;
jmethodID funccb;
pthread_t p_thread[2];

JavaVM * glpVM = NULL;

void Notify(int i);

jstring getNumString(JNIEnv * a, jobject b, jstring str, jint num)
{
    jclass cls = a->GetObjectClass(b);
    jmethodID func = a->GetMethodID(cls, "callback", "(Ljava/lang/String;I)Ljava/lang/String;");
    LOGI("getNumString");

    return (jstring)a->CallObjectMethod(b, func, str, num);
    //
    //return str;
}

void *t_function(void *data)
{
    int end_flag = 1;
    int id;
    int i=0;
    id = *((int *)data);

    while(end_flag)
    {
        LbsLogicProcess();
        Notify(i);
        i++;
        sleep(1);
    }
}

JNIEXPORT jint JNICALL startThread_Native
        (JNIEnv * env, jobject thiz) {

    end_flag = 1 ;
    int b = 2 ;

    __android_log_print( ANDROID_LOG_INFO, "NATIVE", "Call start thread" ) ;
    jclass cls ;
    cls = env->FindClass(classPathName) ;
    if ( cls == NULL ) {
        __android_log_print( ANDROID_LOG_INFO, "NATIVE", "Can't find the class.") ;
    }

    jObject = (jclass)env->NewGlobalRef( cls ) ;
    funccb = env->GetStaticMethodID( cls, "callback_for_thread", "(I)V" ) ;
    if ( funccb == 0 ) {
        __android_log_print( ANDROID_LOG_INFO, "NATIVE", "Can't find the function." ) ;
        env->DeleteGlobalRef( jObject ) ;
    }
    else {
        __android_log_print( ANDROID_LOG_INFO, "NATIVE", "Method connect success....\n") ;
        env->CallStaticVoidMethod( cls, funccb, 10 ) ;
    }

    thr_id = pthread_create( &p_thread[1], NULL, t_function, (void*)&b ) ;
    if ( thr_id < 0 ) {
        __android_log_print( ANDROID_LOG_INFO, "NATIVE", "Create thread fail.\n" ) ;
        return -1 ;
    }
    return 0 ;
}

JNIEXPORT jint JNICALL endThread_Native
        (JNIEnv * env, jobject thiz) {

    __android_log_print( ANDROID_LOG_INFO, "NATIVE", "Call end thread" ) ;
    end_flag = 0 ;
    return 0 ;
}

void Notify(int n) {
    int value = 0 ;
    value = n ;
    if ( !glpVM ) {
        __android_log_print( ANDROID_LOG_INFO, "NATIVE", "error (!glpVM)" ) ;
        return ;
    }

    if ( !funccb ) {
        __android_log_print( ANDROID_LOG_INFO, "NATIVE", "error (!funccb)" ) ;
        return ;
    }

    JNIEnv* env = NULL ;
    glpVM->AttachCurrentThread(  &env, NULL ) ;
    if ( env == NULL || jObject == NULL ) {
        glpVM->DetachCurrentThread() ;
        __android_log_print( ANDROID_LOG_INFO, "NATIVE", "error (env == NULL || AVM_JM.JObject == NULL)" ) ;
        return ;
    }

    env->CallStaticVoidMethod(  jObject, funccb, value ) ;
    glpVM->DetachCurrentThread( ) ;
}




static JNINativeMethod methods[] = {
        {"getNumString", "(Ljava/lang/String;I)Ljava/lang/String;", (void*)getNumString},
        {"startThread", "()I", (void*)startThread_Native },
        {"endThread", "()I", (void*)endThread_Native },
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

    glpVM = vm;

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


