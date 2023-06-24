// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/from_chars.h>
#include <aeon/common/type_traits.h>
#include <aeon/common/string_utils.h>
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
struct converting_variant_conversion<common::string, bool>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const common::string &from) -> bool
    {
        if (common::string_utils::iequals(from, "true") || from == "1")
            return true;

        if (common::string_utils::iequals(from, "false") || from == "0")
            return false;

        throw std::bad_cast{};
    }
};

template <>
struct converting_variant_conversion<bool, common::string>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const bool &from) -> common::string
    {
        return from ? "true" : "false";
    }
};

template <typename to_t>
struct converting_variant_conversion<common::string, to_t,
                                     std::enable_if_t<std::is_integral_v<to_t> || std::is_floating_point_v<to_t>, int>>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const common::string &from) -> to_t
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
    from_t, common::string, std::enable_if_t<std::is_integral_v<from_t> || std::is_floating_point_v<from_t>, int>>
{
    [[nodiscard]] static auto convert([[maybe_unused]] const from_t &from) -> common::string
    {
        // TODO: Fix when a to_u8string exists.
        const auto str = std::to_string(from);
        return common::string{std::cbegin(str), std::cend(str)};
    }
};

} // namespace aeon::variant
