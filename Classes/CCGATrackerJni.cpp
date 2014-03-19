//
//  CCGATrackerJni.cpp
//  chain
//
//  Created by Kosuke Takami on 2014/03/19.
//
//

#include "CCGATracker.h"
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"

#define  LOG_TAG    "CCGATrackerCocos2dX"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
//#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxActivity"
#define CLASS_NAME "com/sukesan1984/chain/CCGATrackerCocos2dX"

typedef struct JniMethodInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} JniMethodInfo;

extern "C"
{
    // get env and cache it
    static JNIEnv* getJNIEnv(void)
    {
        JNIEnv *env = 0;
        
        // get jni environment
        if (cocos2d::JniHelper::getJavaVM()->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
        {
            LOGD("Failed to get the environment using GetEnv()");
        }
        
        if (cocos2d::JniHelper::getJavaVM()->AttachCurrentThread(&env, 0) < 0)
        {
            LOGD("Failed to get the environment using AttachCurrentThread()");
        }
        
        return env;
    }
    
    // get class and make it a global reference, release it at endJni().
    static jclass getClassID(JNIEnv *pEnv)
    {
        jclass ret = pEnv->FindClass(CLASS_NAME);
        if (! ret)
        {
            LOGD("Failed to find class of %s", CLASS_NAME);
        }
        
        return ret;
    }
    
    static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *methodName, const char *paramCode)
    {
        jmethodID methodID = 0;
        JNIEnv *pEnv = 0;
        bool bRet = false;
        
        do
        {
            pEnv = getJNIEnv();
            if (! pEnv)
            {
                break;
            }
            
            jclass classID = getClassID(pEnv);
            
            methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
                LOGD("Failed to find static method id of %s", methodName);
                break;
            }
            
            methodinfo.classID = classID;
            methodinfo.env = pEnv;
            methodinfo.methodID = methodID;
            
            bRet = true;
        } while (0);
        
        return bRet;
    }
    void trackViewJNI(char const *view)
	{
		JniMethodInfo methodInfo;
        
		if (!getStaticMethodInfo(methodInfo, "trackView", "(Ljava/lang/String;)V"))
		{
			return;
		}
        
		jstring stringArg = methodInfo.env->NewStringUTF(view);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
		methodInfo.env->DeleteLocalRef(stringArg);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}
	
	void trackEventJNI(char const *category,char const *action,char const *label,int value)
	{
		JniMethodInfo methodInfo;
        
		if (!getStaticMethodInfo(methodInfo, "trackEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V"))
		{
			return;
		}
        
		jstring categoryArg = methodInfo.env->NewStringUTF(category);
		jstring actionArg = methodInfo.env->NewStringUTF(action);
		jstring labelArg = methodInfo.env->NewStringUTF(label);
		
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, categoryArg,actionArg,labelArg,value);
		methodInfo.env->DeleteLocalRef(categoryArg);
		methodInfo.env->DeleteLocalRef(actionArg);
		methodInfo.env->DeleteLocalRef(labelArg);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}
}