#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <chrono>
#include "Command.hpp"

class Database {
public:
    std::string execute(const Command& cmd);

private:
    std::unordered_map<std::string, std::string> store_;
    std::unordered_map<std::string, long long> expires_; // unix ms

    bool isExpired(const std::string& key);
    long long nowMs() const;
};
