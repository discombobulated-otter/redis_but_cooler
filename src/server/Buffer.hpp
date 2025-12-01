#pragma once

#include <string>
#include <string_view>

class Buffer {
public:
    void append(const std::string& data) {
        buf_ += data;
    }

    void append(std::string_view data) {
        buf_.append(data.data(), data.size());
    }

    std::string_view peek() const {
        return buf_;
    }

    void consume(size_t n) {
        buf_.erase(0, n);
    }

    bool empty() const {
        return buf_.empty();
    }

    size_t size() const {
        return buf_.size();
    }

private:
    std::string buf_;
};
