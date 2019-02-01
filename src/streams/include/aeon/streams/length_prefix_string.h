// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <type_traits>
#include <string>
#include <cstdint>

namespace aeon::streams
{

template <typename T = std::uint32_t>
struct length_prefix_string
{
    explicit length_prefix_string(std::string &str)
        : string(str)
    {
        static_assert(std::is_integral_v<T>, "Length prefix must be integral type.");
    }

    explicit length_prefix_string(const std::string &str)
        : string(const_cast<std::string &>(str))
    {
        static_assert(std::is_integral_v<T>, "Length prefix must be integral type.");
    }

    std::string &string;
};

} // namespace aeon::streams
