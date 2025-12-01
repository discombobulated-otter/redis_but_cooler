#pragma once

#include "Buffer.hpp"
#include "../protocol/RESPParser.hpp"
#include "../db/Database.hpp"

class Connection {
public:
    explicit Connection(int fd);

    int fd() const { return fd_; }

    bool handleRead(Database& db);
    bool handleWrite();

private:
    int fd_;
    Buffer readBuf_;
    Buffer writeBuf_;
    RESPParser parser_;
};
