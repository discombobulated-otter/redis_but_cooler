#pragma once

#include <string>
#include <string_view>
#include <optional>
#include <vector>
#include "../db/Command.hpp"

class RESPParser {
public:
    // Parse RESP from a buffer; consumed = how many bytes were parsed
    std::optional<Command> parse(std::string_view data, size_t& consumed);

private:
    enum class State {
        ARRAY_LEN,
        BULK_LEN,
        BULK_DATA
    };

    State state_ = State::ARRAY_LEN;

    int arrayLen_ = 0;
    int bulkLen_  = 0;
    std::vector<std::string> parts_;
};
