#pragma once

#include <string>
#include <vector>

struct Command {
    std::vector<std::string> parts;

    // Convenience helpers
    std::string name() const {
        return parts.empty() ? "" : parts[0];
    }

    size_t argc() const {
        return parts.size();
    }

    std::string arg(size_t i) const {
        return (i < parts.size()) ? parts[i] : "";
    }
};
