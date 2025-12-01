#pragma once

#include <string>
#include <stdexcept>

class Socket {
public:
    Socket();
    explicit Socket(int fd);

    void bindAndListen(int port);
    int acceptConnection();
    void setNonBlocking();

    int fd() const { return fd_; }

private:
    int fd_;
};
