#include "EventLoop.hpp"
#include <sys/epoll.h>
#include <unistd.h>

EventLoop::EventLoop(Epoll& epoll)
    : epoll_(epoll)
{}

void EventLoop::addConnection(int fd)
{
    epoll_.add(fd, EPOLLIN | EPOLLOUT | EPOLLET);
    connections_.emplace(fd, Connection(fd));
}

void EventLoop::removeConnection(int fd)
{
    epoll_.remove(fd);
    connections_.erase(fd);
    close(fd);
}

void EventLoop::run(Database& db, int listen_fd)
{
    while (true) {
        auto events = epoll_.wait();

        for (auto& ev : events) {
            int fd = ev.data.fd;

            // New client connection
            if (fd == listen_fd) {
                continue; // Server handles accept elsewhere
            }

            auto it = connections_.find(fd);
            if (it == connections_.end())
                continue;

            Connection& conn = it->second;

            // READ event
            if (ev.events & EPOLLIN) {
                if (!conn.handleRead(db)) {
                    removeConnection(fd);
                    continue;
                }
            }

            // WRITE event
            if (ev.events & EPOLLOUT) {
                if (!conn.handleWrite()) {
                    removeConnection(fd);
                    continue;
                }
            }
        }
    }
}
void EventLoop::processEvent(Database& db, const epoll_event& ev)
{
    int fd = ev.data.fd;

    auto it = connections_.find(fd);
    if (it == connections_.end())
        return;

    Connection& conn = it->second;

    if (ev.events & EPOLLIN) {
        if (!conn.handleRead(db)) {
            removeConnection(fd);
            return;
        }
    }

    if (ev.events & EPOLLOUT) {
        if (!conn.handleWrite()) {
            removeConnection(fd);
            return;
        }
    }
}
