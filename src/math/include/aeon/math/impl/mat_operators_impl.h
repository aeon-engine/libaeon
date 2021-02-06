// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline constexpr auto operator+=(mat<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T> &
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
inline constexpr auto operator-=(mat<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T> &
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
inline constexpr auto operator*=(mat<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T> &
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
inline constexpr auto operator/=(mat<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T> &
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
inline constexpr auto operator+(const mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T>
{
    auto result = mat<T>{dimensions(lhs), stride(lhs), std::data(lhs)};
    return std::move(result += rhs);
}

template <typename T>
inline constexpr auto operator-(const mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T>
{
    auto result = mat<T>{dimensions(lhs), stride(lhs), std::data(lhs)};
    return std::move(result -= rhs);
}

template <typename T>
inline constexpr auto operator*(const mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T>
{
    auto result = mat<T>{dimensions(lhs), stride(lhs), std::data(lhs)};
    return std::move(result *= rhs);
}

template <typename T>
inline constexpr auto operator/(const mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T>
{
    auto result = mat<T>{dimensions(lhs), stride(lhs), std::data(lhs)};
    return std::move(result /= rhs);
}

} // namespace aeon::math
