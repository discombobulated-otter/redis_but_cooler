#pragma once

#include "Epoll.hpp"
#include "Connection.hpp"
#include <unordered_map>

class EventLoop {
public:
    EventLoop(Epoll& epoll);

    void addConnection(int fd);
    void removeConnection(int fd);

    void run(Database& db, int listen_fd);
    void processEvent(Database& db, const epoll_event& ev);

private:
    Epoll& epoll_;
    std::unordered_map<int, Connection> connections_;
};
