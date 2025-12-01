#include "Server.hpp"
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <sys/fcntl.h>

Server::Server(int port)
    : port_(port), loop_(epoll_)
{
    setupListenSocket();
}

void Server::setupListenSocket()
{
    listenSock_.bindAndListen(port_);
    listenSock_.setNonBlocking();

    epoll_.add(listenSock_.fd(), EPOLLIN | EPOLLET);

    std::cout << "Listening on port " << port_ << "\n";
}

void Server::acceptNewConnections()
{
    while (true) {
        int client_fd = listenSock_.acceptConnection();
        if (client_fd < 0) break;

        ::fcntl(client_fd, F_SETFL, O_NONBLOCK);
        loop_.addConnection(client_fd);
    }
}

void Server::run()
{
    while (true) {
        auto events = epoll_.wait();

        for (auto& ev : events) {
            int fd = ev.data.fd;

            if (fd == listenSock_.fd()) {
                acceptNewConnections();
            } else {
                // delegate to event loop
                loop_.processEvent(db_, ev);
            }
        }
    }
}
