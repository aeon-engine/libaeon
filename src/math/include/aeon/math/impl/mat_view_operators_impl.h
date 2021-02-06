// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline constexpr auto operator+=(mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) noexcept -> mat_view<T> &
{
    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            lhs.at(x, y) += rhs;
        }
    }

    return lhs;
}

template <typename T>
inline constexpr auto operator-=(mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) noexcept -> mat_view<T> &
{
    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            lhs.at(x, y) -= rhs;
        }
    }

    return lhs;
}

template <typename T>
inline constexpr auto operator*=(mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) noexcept -> mat_view<T> &
{
    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            lhs.at(x, y) *= rhs;
        }
    }

    return lhs;
}

template <typename T>
inline constexpr auto operator/=(mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) noexcept -> mat_view<T> &
{
    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            lhs.at(x, y) /= rhs;
        }
    }

    return lhs;
}

template <typename T>
inline constexpr auto operator==(const mat_view<T> &lhs, const mat_view<T> &rhs) noexcept -> bool
{
    if (dimensions(lhs) != dimensions(rhs))
        return false;

    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            if (lhs.at(x, y) != rhs.at(x, y))
                return false;
        }
    }

    return true;
}

template <typename T>
inline constexpr auto operator!=(const mat_view<T> &lhs, const mat_view<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math
