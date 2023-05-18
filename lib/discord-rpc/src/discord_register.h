#include <jni.h>
#include <android/log.h>
#include "discord-rpc.h"

void Java_com_example_app_Discord_Register(JNIEnv* env, jobject thiz, jstring applicationId, jstring command)
{
    const char* appId = env->GetStringUTFChars(applicationId, NULL);
    const char* cmd = env->GetStringUTFChars(command, NULL);

    // Chame a função Discord_Register aqui
    Discord_Register(appId, cmd);

    // Libere os recursos e strings
    env->ReleaseStringUTFChars(applicationId, appId);
    env->ReleaseStringUTFChars(command, cmd);
}

void Java_com_example_app_Discord_RegisterSteamGame(JNIEnv* env, jobject thiz, jstring applicationId, jstring steamId)
{
    const char* appId = env->GetStringUTFChars(applicationId, NULL);
    const char* steamIdStr = env->GetStringUTFChars(steamId, NULL);

    // Chame a função Discord_RegisterSteamGame aqui
    Discord_RegisterSteamGame(appId, steamIdStr);

    // Libere os recursos e strings
    env->ReleaseStringUTFChars(applicationId, appId);
    env->ReleaseStringUTFChars(steamId, steamIdStr);
}
