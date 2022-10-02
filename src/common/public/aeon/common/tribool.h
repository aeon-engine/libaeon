// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

namespace aeon::common
{

namespace detail
{

struct indeterminate_t
{
};

} // namespace detail

class tribool;

constexpr auto indeterminate(const tribool value,
                             const detail::indeterminate_t dummy = detail::indeterminate_t()) noexcept -> bool;
using indeterminate_keyword_t = decltype(indeterminate);

/*!
 * Tribool that can be true, false or indeterminate
 */
class tribool
{
public:
    enum class value_t
    {
        false_value,
        true_value,
        indeterminate_value
    };

    constexpr tribool() noexcept
        : value{value_t::false_value}
    {
    }

    constexpr tribool(const bool value) noexcept
        : value{value ? value_t::true_value : value_t::false_value}
    {
    }

    constexpr tribool(indeterminate_keyword_t) noexcept
        : value{value_t::indeterminate_value}
    {
    }

    ~tribool() noexcept = default;

    constexpr tribool(const tribool &) noexcept = default;
    constexpr auto operator=(const tribool &) noexcept -> tribool & = default;

    constexpr tribool(tribool &&) noexcept = default;
    constexpr auto operator=(tribool &&) noexcept -> tribool & = default;

    constexpr operator bool() const noexcept
    {
        return value == value_t::true_value;
    }

    constexpr explicit operator int() const noexcept
    {
        return value == value_t::true_value ? 1 : 0;
    }

    [[nodiscard]] constexpr auto is_indeterminate() const noexcept
    {
        return indeterminate(*this);
    }

    value_t value;
};

constexpr auto indeterminate(const tribool val, const detail::indeterminate_t) noexcept -> bool
{
    return val.value == tribool::value_t::indeterminate_value;
}

constexpr auto operator&&(const tribool lhs, const tribool rhs) noexcept
{
    if (static_cast<bool>(!lhs) || static_cast<bool>(!rhs))
        return tribool{false};

    if (static_cast<bool>(lhs) && static_cast<bool>(rhs))
        return tribool{true};

    return tribool{indeterminate};
}

constexpr auto operator&&(const tribool lhs, const bool rhs) noexcept
{
    return rhs ? lhs : tribool{false};
}

constexpr auto operator&&(const bool lhs, const tribool rhs) noexcept
{
    return lhs ? rhs : tribool{false};
}

constexpr auto operator&&(indeterminate_keyword_t, const tribool rhs) noexcept
{
    return !rhs ? tribool{false} : tribool{indeterminate};
}

constexpr auto operator&&(const tribool lhs, indeterminate_keyword_t) noexcept
{
    return !lhs ? tribool{false} : tribool{indeterminate};
}

constexpr auto operator||(const tribool lhs, const tribool rhs) noexcept
{
    if (static_cast<bool>(!lhs) && static_cast<bool>(!rhs))
        return tribool{false};

    if (static_cast<bool>(lhs) || static_cast<bool>(rhs))
        return tribool{true};

    return tribool{indeterminate};
}

constexpr auto operator||(const tribool lhs, const bool rhs) noexcept
{
    return rhs ? tribool{true} : lhs;
}

constexpr auto operator||(const bool lhs, const tribool rhs) noexcept
{
    return lhs ? tribool{true} : rhs;
}

constexpr auto operator||(indeterminate_keyword_t, const tribool rhs) noexcept
{
    return rhs ? tribool{true} : tribool{indeterminate};
}

constexpr auto operator||(const tribool lhs, indeterminate_keyword_t) noexcept
{
    return lhs ? tribool{true} : tribool{indeterminate};
}

constexpr auto operator==(const tribool lhs, const tribool rhs) noexcept
{
    if (indeterminate(lhs) || indeterminate(rhs))
        return false;

    return static_cast<bool>((lhs && rhs) || (!lhs && !rhs));
}

constexpr auto operator==(const tribool lhs, const bool rhs) noexcept
{
    return lhs == tribool{rhs};
}

constexpr auto operator==(const bool lhs, const tribool rhs) noexcept
{
    return tribool{lhs} == rhs;
}

constexpr auto operator==(indeterminate_keyword_t, const tribool rhs) noexcept
{
    return tribool{indeterminate} == rhs;
}

constexpr auto operator==(const tribool lhs, indeterminate_keyword_t) noexcept
{
    return tribool{indeterminate} == lhs;
}

constexpr auto operator!=(const tribool lhs, const tribool rhs) noexcept
{
    if (indeterminate(lhs) || indeterminate(rhs))
        return true;

    return !((lhs && rhs) || (!lhs && !rhs));
}

constexpr auto operator!=(const tribool lhs, const bool rhs) noexcept
{
    return lhs != tribool{rhs};
}

constexpr auto operator!=(const bool lhs, const tribool rhs) noexcept
{
    return tribool{lhs} != rhs;
}

constexpr auto operator!=(indeterminate_keyword_t, const tribool rhs) noexcept
{
    return tribool{indeterminate} != rhs;
}

constexpr auto operator!=(const tribool lhs, indeterminate_keyword_t) noexcept
{
    return lhs != tribool{indeterminate};
}

} // namespace aeon::common
