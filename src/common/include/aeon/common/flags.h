// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/common/bits.h>
#include <type_traits>
#include <cstdint>

namespace aeon::common
{

class flag
{
public:
    constexpr flag(const std::int16_t ai) noexcept
        : value{static_cast<std::uint64_t>(ai)}
    {
    }
    constexpr flag(const std::uint16_t ai) noexcept
        : value{static_cast<std::uint64_t>(ai)}
    {
    }
    constexpr flag(const std::int32_t ai) noexcept
        : value{static_cast<std::uint64_t>(ai)}
    {
    }
    constexpr flag(const std::uint32_t ai) noexcept
        : value{static_cast<std::uint64_t>(ai)}
    {
    }
    constexpr flag(const std::int64_t ai) noexcept
        : value{static_cast<std::uint64_t>(ai)}
    {
    }
    constexpr flag(const std::uint64_t ai) noexcept
        : value{ai}
    {
    }
    constexpr operator std::uint64_t() const noexcept
    {
        return value;
    }

    std::uint64_t value;
};

template <typename enum_type_t>
class flags
{
    static_assert(std::is_enum<enum_type_t>::value, "Flags can only work with an enum type.");
    static_assert((sizeof(enum_type_t) <= sizeof(std::uint64_t)), "Enum too large.");

public:
    constexpr flags() noexcept
        : value_{}
    {
    }

    constexpr flags(const enum_type_t value) noexcept
        : value_{static_cast<std::uint64_t>(value)}
    {
    }

    constexpr flags(const flag value) noexcept
        : value_{value}
    {
    }

    constexpr flags(const flags<enum_type_t> &) noexcept = default;
    constexpr auto operator=(const flags<enum_type_t> &) noexcept -> flags<enum_type_t> & = default;
    constexpr flags(flags<enum_type_t> &&) noexcept = default;
    constexpr auto operator=(flags<enum_type_t> &&) noexcept -> flags<enum_type_t> & = default;

    ~flags() = default;

    constexpr auto &operator&=(const std::uint64_t mask) noexcept
    {
        value_ &= mask;
        return *this;
    }

    constexpr auto &operator&=(const enum_type_t mask) noexcept
    {
        value_ &= static_cast<std::uint64_t>(mask);
        return *this;
    }

    constexpr auto &operator|=(const flags<enum_type_t> f) noexcept
    {
        value_ |= f.value_;
        return *this;
    }

    constexpr auto &operator|=(const enum_type_t f) noexcept
    {
        value_ |= static_cast<std::uint64_t>(f);
        return *this;
    }

    constexpr auto &operator^=(const flags<enum_type_t> f) noexcept
    {
        value_ ^= f.value_;
        return *this;
    }

    constexpr auto &operator^=(const enum_type_t f) noexcept
    {
        value_ ^= static_cast<std::uint64_t>(f);
        return *this;
    }

    constexpr operator std::uint64_t() const noexcept
    {
        return value_;
    }

    constexpr auto operator|(const flags<enum_type_t> f) const noexcept
    {
        return flags<enum_type_t>(flag(value_ | f.value_));
    }

    constexpr auto operator|(const enum_type_t f) const noexcept
    {
        return flags<enum_type_t>(flag(value_ | static_cast<uint64_t>(f)));
    }

    constexpr auto operator^(const flags<enum_type_t> f) const noexcept
    {
        return flags<enum_type_t>(flag(value_ ^ f.value_));
    }

    constexpr auto operator^(const enum_type_t f) const noexcept
    {
        return flags<enum_type_t>(flag(value_ ^ static_cast<uint64_t>(f)));
    }

    constexpr auto operator&(const std::uint64_t mask) const noexcept
    {
        return flags<enum_type_t>(flag(value_ & mask));
    }

    constexpr auto operator&(const enum_type_t f) const noexcept
    {
        return flags<enum_type_t>(flag(value_ & static_cast<uint64_t>(f)));
    }

    constexpr auto operator~() const noexcept
    {
        return flags<enum_type_t>(flag(~value_));
    }

    constexpr auto operator!() const noexcept
    {
        return !value_;
    }

    [[nodiscard]] constexpr auto is_set(const enum_type_t f) const noexcept
    {
        const auto value = static_cast<uint64_t>(f);
        return bits::check_flag(value_, value) && value != 0;
    }

    constexpr void set(const enum_type_t f) noexcept
    {
        value_ |= static_cast<uint64_t>(f);
    }

    constexpr void unset(const enum_type_t f) noexcept
    {
        value_ &= ~static_cast<uint64_t>(f);
    }

    constexpr void conditional_set(const bool condition, const enum_type_t f) noexcept
    {
        if (condition)
            set(f);
    }

    constexpr void conditional_unset(const bool condition, const enum_type_t f) noexcept
    {
        if (condition)
            unset(f);
    }

    using enum_type = enum_type_t;

private:
    std::uint64_t value_;
};

#define aeon_declare_flag_operators(f)                                                                                 \
    inline constexpr auto operator|(const f lhs, const f rhs) noexcept->aeon::common::flags<f>                         \
    {                                                                                                                  \
        return aeon::common::flags<f>(lhs) | rhs;                                                                      \
    }                                                                                                                  \
                                                                                                                       \
    inline constexpr auto operator|(f lhs, aeon::common::flags<f> rhs) noexcept->aeon::common::flags<f>                \
    {                                                                                                                  \
        return lhs | rhs;                                                                                              \
    }

} // namespace aeon::common
