#include "Connection.hpp"
#include <unistd.h>
#include <vector>

Connection::Connection(int fd)
    : fd_(fd)
{}

bool Connection::handleRead(Database& db)
{
    char temp[4096];
    int n = ::read(fd_, temp, sizeof(temp));

    if (n <= 0) {
        return false; // client closed or error
    }

    readBuf_.append(std::string_view(temp, n));

    size_t consumed = 0;

    while (true) {
        auto result = parser_.parse(readBuf_.peek(), consumed);
        if (!result.has_value()) break;

        readBuf_.consume(consumed);

        std::string reply = db.execute(result.value());
        writeBuf_.append(reply);
    }

    return true;
}

bool Connection::handleWrite()
{
    if (writeBuf_.empty()) {
        return true;
    }

    std::string_view out = writeBuf_.peek();
    int n = ::write(fd_, out.data(), out.size());

    if (n < 0) {
        return false;
    }

    writeBuf_.consume(n);
    return true;
}
