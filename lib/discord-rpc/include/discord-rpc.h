#pragma once
#include <jni.h>
#include <stdint.h>

// clang-format off

#if defined(DISCORD_DYNAMIC_LIB)
#  if defined(_WIN32)
#    if defined(DISCORD_BUILDING_SDK)
#      define DISCORD_EXPORT __declspec(dllexport)
#    else
#      define DISCORD_EXPORT __declspec(dllimport)
#    endif
#  else
#    define DISCORD_EXPORT __attribute__((visibility("default")))
#  endif
#else
#  define DISCORD_EXPORT
#endif

// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DiscordRichPresence {
    const char* state;   /* max 128 bytes */
    const char* details; /* max 128 bytes */
    int64_t startTimestamp;
    int64_t endTimestamp;
    const char* largeImageKey;  /* max 32 bytes */
    const char* largeImageText; /* max 128 bytes */
    const char* smallImageKey;  /* max 32 bytes */
    const char* smallImageText; /* max 128 bytes */
    const char* partyId;        /* max 128 bytes */
    int partySize;
    int partyMax;
    const char* matchSecret;    /* max 128 bytes */
    const char* joinSecret;     /* max 128 bytes */
    const char* spectateSecret; /* max 128 bytes */
    int8_t instance;
    const char* button1Text;
    const char* button1Url;
    const char* button2Text;
    const char* button2Url;
} DiscordRichPresence;

typedef struct DiscordJoinRequest {
    const char* userId;
    const char* username;
    const char* discriminator;
    const char* avatar;
} DiscordJoinRequest;

typedef struct DiscordEventHandlers {
    void (*ready)(JNIEnv*, jobject);
    void (*disconnected)(JNIEnv*, jobject, int errorCode, const char* message);
    void (*errored)(JNIEnv*, jobject, int errorCode, const char* message);
    void (*joinGame)(JNIEnv*, jobject, const char* joinSecret);
    void (*spectateGame)(JNIEnv*, jobject, const char* spectateSecret);
    void (*joinRequest)(JNIEnv*, jobject, const DiscordJoinRequest* request);
} DiscordEventHandlers;

#define DISCORD_REPLY_NO 0
#define DISCORD_REPLY_YES 1
#define DISCORD_REPLY_IGNORE 2

DISCORD_EXPORT void Discord_Initialize(JNIEnv* env, jobject activity,
                                        const char* applicationId,
                                        DiscordEventHandlers* handlers,
                                        int autoRegister,
                                        const char* optionalSteamId);
DISCORD_EXPORT void Discord_Shutdown(JNIEnv* env, jobject activity);

/* checks for incoming messages, dispatches callbacks */
DISCORD_EXPORT void Discord_RunCallbacks(JNIEnv* env, jobject activity);

/* If you disable the lib starting its own io thread, you'll need to call this from your own */
#ifdef DISCORD_DISABLE_IO_THREAD
DISCORD_EXPORT void Discord_UpdateConnection(JNIEnv* env, jobject activity);
#endif

DISCORD_EXPORT void Discord_UpdatePresence(JNIEnv* env, jobject activity, const DiscordRichPresence* presence);

DISCORD_EXPORT void Discord_Respond(JNIEnv* env, jobject activity, const char* userid, /* DISCORD_REPLY_ */ int reply);

#ifdef __cplusplus
} /* extern "C" */
#endif


