#include "connection.h"

#include <android/log.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define TAG "BaseConnection"
#define LOG(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

int GetProcessId() {
    return getpid();
}

struct BaseConnectionAndroid : public BaseConnection {
    int sockfd = -1;
};

static BaseConnectionAndroid Connection;

/*static*/ BaseConnection* BaseConnection::Create() {
    return &Connection;
}

/*static*/ void BaseConnection::Destroy(BaseConnection*& c) {
    auto self = reinterpret_cast<BaseConnectionAndroid*>(c);
    self->Close();
    c = nullptr;
}

bool BaseConnection::Open() {
    auto self = reinterpret_cast<BaseConnectionAndroid*>(this);

    self->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (self->sockfd < 0) {
        LOG("Error creating socket: %s", strerror(errno));
        return false;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345); // Port to connect to (change as needed)
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // IP address to connect to (change as needed)

    if (connect(self->sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        LOG("Error connecting to server: %s", strerror(errno));
        close(self->sockfd);
        self->sockfd = -1;
        return false;
    }

    self->isOpen = true;
    return true;
}

bool BaseConnection::Close() {
    auto self = reinterpret_cast<BaseConnectionAndroid*>(this);

    if (self->sockfd >= 0) {
        close(self->sockfd);
        self->sockfd = -1;
        self->isOpen = false;
    }

    return true;
}

bool BaseConnection::Write(const void* data, size_t length) {
    auto self = reinterpret_cast<BaseConnectionAndroid*>(this);

    if (!self || self->sockfd < 0) {
        return false;
    }

    ssize_t ret = send(self->sockfd, data, length, 0);
    if (ret < 0 || (size_t)ret != length) {
        LOG("Error writing data to socket: %s", strerror(errno));
        Close();
        return false;
    }

    return true;
}

bool BaseConnection::Read(void* data, size_t length) {
    auto self = reinterpret_cast<BaseConnectionAndroid*>(this);

    if (!self || self->sockfd < 0) {
        return false;
    }

    ssize_t ret = recv(self->sockfd, data, length, MSG_WAITALL);
    if (ret < 0 || (size_t)ret != length) {
        LOG("Error reading data from socket: %s", strerror(errno));
        Close();
        return false;
    }

    return true;
}
