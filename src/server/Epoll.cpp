#include "Epoll.hpp"
#include <stdexcept>
#include <unistd.h>

Epoll::Epoll() {
    epollFd_ = epoll_create1(0);
    if (epollFd_ < 0) {
        throw std::runtime_error("epoll_create1 failed");
    }
}

Epoll::~Epoll() {
    if (epollFd_ >= 0) {
        close(epollFd_);
    }
}

void Epoll::add(int fd, uint32_t events) {
    epoll_event ev{};
    ev.events = events;
    ev.data.fd = fd;

    if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &ev) < 0) {
        throw std::runtime_error("epoll_ctl ADD failed");
    }
}

void Epoll::mod(int fd, uint32_t events) {
    epoll_event ev{};
    ev.events = events;
    ev.data.fd = fd;

    if (epoll_ctl(epollFd_, EPOLL_CTL_MOD, fd, &ev) < 0) {
        throw std::runtime_error("epoll_ctl MOD failed");
    }
}

void Epoll::remove(int fd) {
    if (epoll_ctl(epollFd_, EPOLL_CTL_DEL, fd, nullptr) < 0) {
        throw std::runtime_error("epoll_ctl DEL failed");
    }
}

std::vector<epoll_event> Epoll::wait(int timeout_ms) {
    std::vector<epoll_event> events(64); // fixed buffer for now
    int n = epoll_wait(epollFd_, events.data(), events.size(), timeout_ms);
    if (n < 0) {
        throw std::runtime_error("epoll_wait failed");
    }
    events.resize(n);
    return events;
}
