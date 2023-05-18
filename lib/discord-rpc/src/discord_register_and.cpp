#include <jni.h>
#include <android/log.h>

extern "C" JNIEXPORT void JNICALL Java_com_example_app_Discord_Register(JNIEnv* env, jobject thiz, jstring applicationId, jstring command)
{
    // Obtenha os strings a partir dos argumentos jstring
    const char* appId = env->GetStringUTFChars(applicationId, NULL);
    const char* cmd = env->GetStringUTFChars(command, NULL);

    // Crie uma intenção (Intent) com a ação ACTION_VIEW
    jclass intentClass = env->FindClass("android/content/Intent");
    jmethodID intentConstructor = env->GetMethodID(intentClass, "<init>", "(Ljava/lang/String;)V");
    jobject intentObj = env->NewObject(intentClass, intentConstructor, env->NewStringUTF("android.intent.action.VIEW"));

    // Configure o data URI para o esquema personalizado
    jmethodID setDataMethod = env->GetMethodID(intentClass, "setData", "(Landroid/net/Uri;)Landroid/content/Intent;");
    jclass uriClass = env->FindClass("android/net/Uri");
    jmethodID parseMethod = env->GetStaticMethodID(uriClass, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
    jobject uriObj = env->CallStaticObjectMethod(uriClass, parseMethod, env->NewStringUTF(cmd));
    env->CallObjectMethod(intentObj, setDataMethod, uriObj);

    // Obtenha a referência da classe Activity atual
    jclass activityClass = env->GetObjectClass(thiz);

    // Obtenha o método estático startActivity() da classe Activity
    jmethodID startActivityMethod = env->GetMethodID(activityClass, "startActivity", "(Landroid/content/Intent;)V");

    // Inicie a intenção (Intent)
    env->CallVoidMethod(thiz, startActivityMethod, intentObj);

    // Libere os recursos e strings
    env->ReleaseStringUTFChars(applicationId, appId);
    env->ReleaseStringUTFChars(command, cmd);
}
