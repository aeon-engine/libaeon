// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/common/bits.h>
#include <type_traits>
#include <cstdint>

namespace aeon::common
{

template <typename underlying_type_t>
class flag
{
public:
    using underlying_type = underlying_type_t;

    constexpr flag(const std::int16_t ai) noexcept
        : value{static_cast<underlying_type>(ai)}
    {
    }
    constexpr flag(const std::uint16_t ai) noexcept
        : value{static_cast<underlying_type>(ai)}
    {
    }
    constexpr flag(const std::int32_t ai) noexcept
        : value{static_cast<underlying_type>(ai)}
    {
    }
    constexpr flag(const std::uint32_t ai) noexcept
        : value{static_cast<underlying_type>(ai)}
    {
    }
    constexpr flag(const std::int64_t ai) noexcept
        : value{static_cast<underlying_type>(ai)}
    {
    }
    constexpr flag(const std::uint64_t ai) noexcept
        : value{static_cast<underlying_type>(ai)}
    {
    }
    constexpr operator underlying_type() const noexcept
    {
        return value;
    }

    underlying_type value;
};

template <typename enum_type_t>
class flags
{
public:
    using enum_type = enum_type_t;
    using underlying_type = std::underlying_type_t<enum_type_t>;

    static_assert(std::is_enum_v<enum_type>, "Flags can only work with an enum type.");
    static_assert(std::is_unsigned_v<underlying_type>, "Underlying type must be unsigned.");

    constexpr flags() noexcept
        : value_{}
    {
    }

    constexpr flags(const enum_type value) noexcept
        : value_{static_cast<underlying_type>(value)}
    {
    }

    constexpr flags(const flag<underlying_type> value) noexcept
        : value_{value}
    {
    }

    constexpr flags(const flags<enum_type> &) noexcept = default;
    constexpr auto operator=(const flags<enum_type> &) noexcept -> flags<enum_type> & = default;
    constexpr flags(flags<enum_type> &&) noexcept = default;
    constexpr auto operator=(flags<enum_type> &&) noexcept -> flags<enum_type> & = default;

    ~flags() = default;

    constexpr auto &operator&=(const underlying_type mask) noexcept
    {
        value_ &= mask;
        return *this;
    }

    constexpr auto &operator&=(const enum_type mask) noexcept
    {
        value_ &= static_cast<underlying_type>(mask);
        return *this;
    }

    constexpr auto &operator|=(const flags<enum_type> f) noexcept
    {
        value_ |= f.value_;
        return *this;
    }

    constexpr auto &operator|=(const enum_type f) noexcept
    {
        value_ |= static_cast<underlying_type>(f);
        return *this;
    }

    constexpr auto &operator^=(const flags<enum_type> f) noexcept
    {
        value_ ^= f.value_;
        return *this;
    }

    constexpr auto &operator^=(const enum_type f) noexcept
    {
        value_ ^= static_cast<underlying_type>(f);
        return *this;
    }

    constexpr operator underlying_type() const noexcept
    {
        return value_;
    }

    constexpr auto operator|(const flags<enum_type> f) const noexcept
    {
        return flags<enum_type>{flag<underlying_type>{value_ | f.value_}};
    }

    constexpr auto operator|(const enum_type f) const noexcept
    {
        return flags<enum_type>{flag<underlying_type>{value_ | static_cast<underlying_type>(f)}};
    }

    constexpr auto operator^(const flags<enum_type> f) const noexcept
    {
        return flags<enum_type>{flag<underlying_type>{value_ ^ f.value_}};
    }

    constexpr auto operator^(const enum_type f) const noexcept
    {
        return flags<enum_type>{flag<underlying_type>{value_ ^ static_cast<underlying_type>(f)}};
    }

    constexpr auto operator&(const underlying_type mask) const noexcept
    {
        return flags<enum_type>{flag<underlying_type>{value_ & mask}};
    }

    constexpr auto operator&(const enum_type f) const noexcept
    {
        return flags<enum_type>{flag<underlying_type>{value_ & static_cast<underlying_type>(f)}};
    }

    constexpr auto operator~() const noexcept
    {
        return flags<enum_type>(flag<underlying_type>{~value_});
    }

    constexpr auto operator!() const noexcept
    {
        return !value_;
    }

    [[nodiscard]] constexpr auto is_set(const enum_type f) const noexcept
    {
        const auto value = static_cast<underlying_type>(f);
        return bits::check_flag(value_, value) && value != 0;
    }

    constexpr void set(const enum_type f) noexcept
    {
        value_ |= static_cast<underlying_type>(f);
    }

    constexpr void set(const enum_type f, const bool condition) noexcept
    {
        if (condition)
            set(f);
        else
            unset(f);
    }

    constexpr void unset(const enum_type f) noexcept
    {
        value_ &= ~static_cast<underlying_type>(f);
    }

    constexpr void conditional_set(const bool condition, const enum_type f) noexcept
    {
        if (condition)
            set(f);
    }

    constexpr void conditional_unset(const bool condition, const enum_type f) noexcept
    {
        if (condition)
            unset(f);
    }

    constexpr void force_set(const underlying_type v) noexcept
    {
        value_ = v;
    }

private:
    underlying_type value_;
};

#define aeon_declare_flag_operators(f)                                                                                 \
    inline constexpr auto operator|(const f lhs, const f rhs) noexcept->aeon::common::flags<f>                         \
    {                                                                                                                  \
        return aeon::common::flags<f>(lhs) | rhs;                                                                      \
    }

} // namespace aeon::common
