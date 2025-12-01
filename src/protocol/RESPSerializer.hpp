#pragma once

#include <string>
#include <string_view>

namespace RESP {

    std::string simpleString(std::string_view s);
    std::string bulkString(std::string_view s);
    std::string error(std::string_view s);
    std::string integer(long long v);

}
