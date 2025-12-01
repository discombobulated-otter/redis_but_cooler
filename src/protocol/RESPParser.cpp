#include "RESPParser.hpp"
#include <cstdlib>

std::optional<Command> RESPParser::parse(std::string_view data, size_t& consumed)
{
    consumed = 0;

    if (data.empty()) {
        return std::nullopt;
    }

    size_t pos = 0;

    // Expect array: *<count>\r\n
    if (state_ == State::ARRAY_LEN) {
        if (data[pos] != '*') return std::nullopt;

        size_t end = data.find("\r\n", pos);
        if (end == std::string_view::npos) return std::nullopt;

        arrayLen_ = std::atoi(data.substr(pos + 1, end - pos - 1).data());
        pos = end + 2;

        parts_.clear();
        parts_.reserve(arrayLen_);
        state_ = State::BULK_LEN;
    }

    // Parse each bulk string
    while (parts_.size() < (size_t)arrayLen_) {

        if (state_ == State::BULK_LEN) {
            if (pos >= data.size() || data[pos] != '$')
                return std::nullopt;

            size_t end = data.find("\r\n", pos);
            if (end == std::string_view::npos)
                return std::nullopt;

            bulkLen_ = std::atoi(data.substr(pos + 1, end - pos - 1).data());
            pos = end + 2;
            state_ = State::BULK_DATA;
        }

        if (state_ == State::BULK_DATA) {
            if (pos + bulkLen_ + 2 > data.size())
                return std::nullopt;

            parts_.emplace_back(data.substr(pos, bulkLen_));
            pos += bulkLen_ + 2;

            state_ = State::BULK_LEN;
        }
    }

    consumed = pos;

    Command cmd;
    cmd.parts = parts_;

    state_ = State::ARRAY_LEN;
    return cmd;
}
