# Redis Lite

A lightweight Redis-inspired in-memory key-value store written in modern C++20, built to explore internal Redis mechanisms.
Implements non-blocking I/O, epoll-based event handling, and RESP command parsing in a clean modular architecture.

A minimal, high-performance Redis-like in-memory key-value store implemented in **modern C++20**, built from scratch to understand the internal architecture of Redis.

This project implements:

* A TCP server using non-blocking sockets
* An `epoll`-based event loop
* A connection manager with read/write buffers
* RESP protocol parsing (arrays, bulk strings, integers, simple strings)
* Basic Redis commands:

  * `GET`
  * `SET`
  * `DEL`
  * `EXPIRE`
* Key expiration using millisecond timestamps
* A single-threaded design that mirrors Redis' event loop model

This codebase follows a clean modular layout inspired by real Redis internals:
`Socket.cpp`, `Epoll.cpp`, `EventLoop.cpp`, `Connection.cpp`, `RESPParser.cpp`, `RESPSerializer.cpp`, and `Database.cpp`.

---

## 🔧 Building

```bash
cmake -B build
cmake --build build -j
```

This produces the executable:

```
./build/redis_but_cooler
```

---

## 🚀 Running the server

```bash
./build/redis_but_cooler
```

The server listens on **port 6379**, the standard Redis port.

---

## 🧪 Testing with redis-cli

You can use the real Redis CLI:

```bash
redis-cli -p 6379
```

Try:

```
SET a 123
GET a
EXPIRE a 5
DEL a
```

---

## 📂 Project Structure

```
src/
  server/
    Socket.hpp / .cpp
    Epoll.hpp / .cpp
    EventLoop.hpp / .cpp
    Connection.hpp / .cpp
    Buffer.hpp
  protocol/
    RESPParser.hpp / .cpp
    RESPSerializer.hpp / .cpp
  db/
    Database.hpp / .cpp
    Command.hpp / .cpp
  util/
    Logger.hpp / .cpp
    Errors.hpp
    Time.hpp
```

---

## 🎯 Goals

* Understand Redis' event loop architecture
* Build a TCP server from scratch using Linux syscalls
* Learn how RESP parsing and serialization works
* Practice C++20, RAII, and clean modular design
* Ship a résumé-ready systems project

---

## 📝 Future Improvements

* Persistence (RDB / AOF)
* Pub/Sub
* Pipelines
* Memory-optimized object types
* LRU/LFU eviction policies
* Command table and extensible dispatcher
* Multi-threaded I/O (experimental)

---

## 📄 License

MIT License — free for modification and learning.
