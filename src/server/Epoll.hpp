#pragma once

#include <vector>
#include <sys/epoll.h>

class Epoll {
public:
    Epoll();
    ~Epoll();

    void add(int fd, uint32_t events);
    void mod(int fd, uint32_t events);
    void remove(int fd);

    std::vector<epoll_event> wait(int timeout_ms = -1);

    int fd() const { return epollFd_; }

private:
    int epollFd_;
};
