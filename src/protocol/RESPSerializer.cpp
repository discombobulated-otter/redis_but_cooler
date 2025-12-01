#include "RESPSerializer.hpp"
#include <string>

std::string RESP::simpleString(std::string_view s) {
    return "+" + std::string(s) + "\r\n";
}

std::string RESP::bulkString(std::string_view s) {
    return "$" + std::to_string(s.size()) + "\r\n" + std::string(s) + "\r\n";
}

std::string RESP::error(std::string_view s) {
    return "-" + std::string(s) + "\r\n";
}

std::string RESP::integer(long long v) {
    return ":" + std::to_string(v) + "\r\n";
}
