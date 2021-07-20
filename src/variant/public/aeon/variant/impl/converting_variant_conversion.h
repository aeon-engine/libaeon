// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/from_chars.h>
#include <aeon/common/type_traits.h>
#include <aeon/common/string.h>
#include <cstdint>

namespace aeon::variant
{

template <typename from_t, typename to_t, typename enable = int>
struct converting_variant_conversion
{
    [[nodiscard]] static auto convert([[maybe_unused]] const from_t &from) -> to_t
    {
        return static_cast<to_t>(from);
    }
};

template <>
struct converting_variant_conversion<std::string, bool>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const std::string &from) -> bool
    {
        if (common::string::iequals(from, "true") || from == "1")
            return true;

        if (common::string::iequals(from, "false") || from == "0")
            return false;

        throw std::bad_cast{};
    }
};

template <>
struct converting_variant_conversion<bool, std::string>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const bool &from) -> std::string
    {
        return from ? "true" : "false";
    }
};

template <typename to_t>
struct converting_variant_conversion<std::string, to_t,
                                     std::enable_if_t<std::is_integral_v<to_t> || std::is_floating_point_v<to_t>, int>>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const std::string &from) -> to_t
    {
        if constexpr (common::type_traits::is_any_same_v<to_t, std::int8_t, std::int16_t>)
        {
            std::int32_t value{};
            const auto result = common::from_chars(std::data(from), std::data(from) + std::size(from), value);

            if (result.ec != std::errc{})
                throw std::bad_cast{};

            return static_cast<to_t>(value);
        }
        else if constexpr (common::type_traits::is_any_same_v<to_t, std::uint8_t, std::uint16_t>)
        {
            std::uint32_t value{};
            const auto result = common::from_chars(std::data(from), std::data(from) + std::size(from), value);

            if (result.ec != std::errc{})
                throw std::bad_cast{};

            return static_cast<to_t>(value);
        }
        else if constexpr (common::type_traits::is_any_same_v<to_t, std::int32_t, std::uint32_t, std::int64_t,
                                                              std::uint64_t, float, double>)
        {
            to_t value{};
            const auto result = common::from_chars(std::data(from), std::data(from) + std::size(from), value);

            if (result.ec != std::errc{})
                throw std::bad_cast{};

            return value;
        }
        else
        {
            throw std::bad_cast{};
        }
    }
};

template <typename from_t>
struct converting_variant_conversion<
    from_t, std::string, std::enable_if_t<std::is_integral_v<from_t> || std::is_floating_point_v<from_t>, int>>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const from_t &from) -> std::string
    {
        return std::to_string(from);
    }
};

template <typename to_t>
struct converting_variant_conversion<chrono::calendar, to_t>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const chrono::calendar &from) -> to_t
    {
        throw std::bad_cast{};
    }
};

template <typename from_t>
struct converting_variant_conversion<from_t, chrono::calendar>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const from_t &from) -> chrono::calendar
    {
        throw std::bad_cast{};
    }
};

template <>
struct converting_variant_conversion<chrono::calendar, std::string>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const chrono::calendar &from) -> std::string
    {
        return from.to_string();
    }
};

template <>
struct converting_variant_conversion<std::string, chrono::calendar>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const std::string &from) -> chrono::calendar
    {
        return chrono::calendar{from};
    }
};

} // namespace aeon::variant
