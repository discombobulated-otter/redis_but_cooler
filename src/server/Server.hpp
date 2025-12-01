#pragma once

#include "Socket.hpp"
#include "Epoll.hpp"
#include "EventLoop.hpp"
#include "../db/Database.hpp"

class Server {
public:
    explicit Server(int port);
    void run();

private:
    int port_;
    Socket listenSock_;
    Epoll epoll_;
    EventLoop loop_;
    Database db_;

    void setupListenSocket();
    void acceptNewConnections();
};
