#include "Socket.hpp"
#include <sys/socket.h> // ye socket functions k liye hai
#include <sys/types.h> // ye bhi socket functions k liye hai lmao
#include <sys/fcntl.h> // ye non blocking k liye hai
#include <unistd.h>
#include <cstring>
#include <stdexcept> // ye vo runtime wale k liye hai
#include <netinet/in.h> // isko include karna padega for sockaddr_in



Socket::Socket() // this is like a constructor for this class aight? 
{
    fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
    if(fd_ < 0)
    {
        throw std::runtime_error("I am done with socket, ain't making any!!!");
    }
}
Socket::Socket(int fd)
    : fd_(fd)
{
    if (fd_ < 0) {
        throw std::runtime_error("Descriptor is invalid I guess?");
    }
}


void Socket::bindAndListen(int port)
{
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);


    int opt = 1;
    if(setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))<0)
    {
        throw std::runtime_error("setsockopt failed, bro");
    }
    if(::bind(fd_, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        throw std::runtime_error("Binding failed...");
    }
    if(::listen(fd_, SOMAXCONN) < 0)
    {
        throw std::runtime_error("Listening failed...");
    }
}

int Socket::acceptConnection()
{
    sockaddr_in addr{};
    socklen_t len = sizeof(addr);

    int client_fd = ::accept(fd_, (sockaddr*)&addr, &len);
    if(client_fd < 0)
    {
        return -1; // its like it is non fatal so user/ caller will handle it.
    }
    return client_fd;
}

void Socket::setNonBlocking()
{
    int flags = fcntl(fd_, F_GETFL, 0);
    if (flags < 0) {
        throw std::runtime_error("fcntl(F_GETFL) failed");
    }

    if (fcntl(fd_, F_SETFL, flags | O_NONBLOCK) < 0) {
        throw std::runtime_error("fcntl(F_SETFL, O_NONBLOCK) failed");
    }
}