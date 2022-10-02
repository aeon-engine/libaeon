// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/from_chars.h>
#include <aeon/common/type_traits.h>
#include <aeon/common/string_utils.h>
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
struct converting_variant_conversion<std::u8string, bool>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const std::u8string &from) -> bool
    {
        if (common::string_utils::iequals(from, u8"true") || from == u8"1")
            return true;

        if (common::string_utils::iequals(from, u8"false") || from == u8"0")
            return false;

        throw std::bad_cast{};
    }
};

template <>
struct converting_variant_conversion<bool, std::u8string>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const bool &from) -> std::u8string
    {
        return from ? u8"true" : u8"false";
    }
};

template <typename to_t>
struct converting_variant_conversion<std::u8string, to_t,
                                     std::enable_if_t<std::is_integral_v<to_t> || std::is_floating_point_v<to_t>, int>>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const std::u8string &from) -> to_t
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
    from_t, std::u8string, std::enable_if_t<std::is_integral_v<from_t> || std::is_floating_point_v<from_t>, int>>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const from_t &from) -> std::u8string
    {
        // TODO: Fix when a to_u8string exists.
        const auto str = std::to_string(from);
        return std::u8string{std::cbegin(str), std::cend(str)};
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
struct converting_variant_conversion<chrono::calendar, std::u8string>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const chrono::calendar &from) -> std::u8string
    {
        return from.to_string();
    }
};

template <>
struct converting_variant_conversion<std::u8string, chrono::calendar>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const std::u8string &from) -> chrono::calendar
    {
        return chrono::calendar{from};
    }
};

} // namespace aeon::variant
