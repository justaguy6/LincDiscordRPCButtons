#include <jni.h>
#include <string>
#include <android/log.h>
#include "../lib/discord-rpc/include/discord-rpc.h"

extern "C" {

    void onReadyCallback() {
     
    }

    void onDisconnectedCallback(int errorCode, const char* message) {
       
    }

    void onErrorCallback(int errorCode, const char* message) {
        
    }

    void onJoinCallback(const char* joinSecret) {
       
    }

    void onSpectateCallback(const char* spectateSecret) {
      
    }

    void onRequestCallback(const DiscordJoinRequest* request) {
        
    }

    JNIEXPORT void JNICALL Java_com_example_myapplication_DiscordRpc_init(JNIEnv* env, jobject /* this */, jstring clientID, jstring steamAppID) {
        const char* _clientID = env->GetStringUTFChars(clientID, 0);
        const char* _steamAppID = env->GetStringUTFChars(steamAppID, 0);

        ::DiscordEventHandlers handlers{};
        memset(&handlers, 0, sizeof(handlers));
        handlers.ready = onReadyCallback;
        handlers.disconnected = onDisconnectedCallback;
        handlers.errored = onErrorCallback;
        handlers.joinGame = onJoinCallback;
        handlers.spectateGame = onSpectateCallback;
        handlers.joinRequest = onRequestCallback;
        ::Discord_Initialize(_clientID, &handlers, 1, _steamAppID);

        env->ReleaseStringUTFChars(clientID, _clientID);
        env->ReleaseStringUTFChars(steamAppID, _steamAppID);
    }

    JNIEXPORT void JNICALL Java_com_example_myapplication_DiscordRpc_process(JNIEnv* env, jobject /* this */) {
        
        ::Discord_RunCallbacks();
    }

    JNIEXPORT void JNICALL Java_com_example_myapplication_DiscordRpc_updatePresence(JNIEnv* env, jobject /* this */,
        jstring state, jstring details, jlong startTimestamp, jlong endTimestamp,
        jstring largeImageKey, jstring largeImageText,
        jstring smallImageKey, jstring smallImageText,
        jstring partyID, jint partySize, jint partyMax, jstring matchSecret, jstring joinSecret, jstring spectateSecret,
        jbyte instance, jstring button1Text, jstring button1Url, jstring button2Text, jstring button2Url) {
        const char* _state = env->GetStringUTFChars(state, 0);
        const char* _details = env->GetStringUTFChars(details, 0);
        const char* _largeImageKey = env->GetStringUTFChars(largeImageKey, 0);
        const char* _largeImageText = env->GetStringUTFChars(largeImageText, 0);
        const char* _smallImageKey = env->GetStringUTFChars(smallImageKey, 0);
        const char* _smallImageText = env->GetStringUTFChars(smallImageText, 0);
       
