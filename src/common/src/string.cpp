// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/common/string.h>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <sstream>
#include <iomanip>

namespace aeon::common::string
{

auto char_to_hex(const char c) -> std::string
{
    std::ostringstream ss;
    ss << '%' << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<short>(c & 0xff);
    return ss.str();
}

auto hex_to_char(const std::string &str) -> char
{
    if (str.empty())
        return 0;

    std::istringstream in(str);

    short c = 0;
    in >> std::hex >> c;

    if (in.fail())
        throw std::runtime_error("stream decode failure");

    return static_cast<char>(c & 0xff);
}

} // namespace aeon::common::string
