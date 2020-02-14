//
// Created by HCH on 2020-02-14.
//



#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "com_watanow_lbslogicpkg_LbsLogicMain.h"

#define  USE_IN_ANDROID
//#define  USE_IN_IOS

#ifdef USE_IN_ANDROID
#define LOG_TAG "LbsProcess"
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#else
#define LOGE(msg) printf(msg)
#define LOGI(msg) printf(msg)
#endif

void LbsLogicProcess()
{

    LOGI("LbsLogicProcess");
}
