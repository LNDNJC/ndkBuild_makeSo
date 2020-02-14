LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := lbslogic

LOCAL_SRC_FILES := \
    LbsProcess.cpp \
    LbsMainLogic.cpp

LOCAL_LDLIBS :=  -llog

include $(BUILD_SHARED_LIBRARY)

