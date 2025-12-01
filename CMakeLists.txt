cmake_minimum_required(VERSION 3.16)
project(redis_but_cooler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(redis_but_cooler
    src/main.cpp
    src/server/Server.cpp
    src/server/Socket.cpp
    src/server/Epoll.cpp
    src/server/Connection.cpp
    src/server/EventLoop.cpp
    src/protocol/RESPParser.cpp
    src/protocol/RESPSerializer.cpp
    src/db/Database.cpp
    src/db/Command.cpp
    src/util/Logger.cpp
)
