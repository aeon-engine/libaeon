// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/common/from_chars.h>
#include <aeon/common/type_traits.h>
#include <aeon/common/string.h>
#include <cstdint>

namespace aeon::common
{

template <typename from_t, typename to_t>
struct converting_variant_conversion
{
    [[nodiscard]] static auto convert(const from_t &from)
    {
        if constexpr (std::is_same_v<to_t, std::string>)
        {
            if constexpr (std::is_same_v<from_t, bool>)
            {
                return from ? "true" : "false";
            }
            else
            {
                return std::to_string(from);
            }
        }
        else
        {
            return static_cast<to_t>(from);
        }
    }
};

template <typename to_t>
struct converting_variant_conversion<std::string, to_t>
{
    [[nodiscard]] static auto convert(const std::string &from)
    {
        if constexpr (type_traits::is_any_same_v<to_t, std::int8_t, std::int16_t>)
        {
            std::int32_t value{};
            const auto result = from_chars(std::data(from), std::data(from) + std::size(from), value);

            if (result.ec != std::errc{})
                throw std::bad_cast{};

            return static_cast<to_t>(value);
        }
        else if constexpr (type_traits::is_any_same_v<to_t, std::uint8_t, std::uint16_t>)
        {
            std::uint32_t value{};
            const auto result = from_chars(std::data(from), std::data(from) + std::size(from), value);

            if (result.ec != std::errc{})
                throw std::bad_cast{};

            return static_cast<to_t>(value);
        }
        else if constexpr (type_traits::is_any_same_v<to_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t,
                                                      float, double>)
        {
            to_t value{};
            const auto result = from_chars(std::data(from), std::data(from) + std::size(from), value);

            if (result.ec != std::errc{})
                throw std::bad_cast{};

            return value;
        }
        else if constexpr (std::is_same_v<to_t, bool>)
        {
            if (string::iequals<char>(from, "true") || from == "1")
                return true;

            if (string::iequals<char>(from, "false") || from == "0")
                return false;

            throw std::bad_cast{};
        }
        else
        {
            return static_cast<to_t>(from);
        }
    }
};

} // namespace aeon::common
