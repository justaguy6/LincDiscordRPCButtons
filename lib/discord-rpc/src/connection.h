#pragma once

// This is to wrap the platform specific kinds of connect/read/write.

#include <stdint.h>
#include <stdlib.h>
#include <jni.h>

class BaseConnection {
public:
    static BaseConnection* Create();
    static void Destroy(BaseConnection*&);
    bool isOpen{false};
    bool Open();
    bool Close();
    bool Write(const void* data, size_t length);
    bool Read(void* data, size_t length);

private:
    jobject m_javaChannel = nullptr;
    JNIEnv* m_jniEnv = nullptr;
};
