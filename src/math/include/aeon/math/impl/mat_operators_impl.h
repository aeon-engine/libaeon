// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline constexpr auto operator+=(mat &lhs, const T rhs) -> mat &
{
    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            lhs.at<T>(x, y) += rhs;
        }
    }

    return lhs;
}

template <typename T>
inline constexpr auto operator-=(mat &lhs, const T rhs) -> mat &
{
    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            lhs.at<T>(x, y) -= rhs;
        }
    }

    return lhs;
}

template <typename T>
inline constexpr auto operator*=(mat &lhs, const T rhs) -> mat &
{
    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            lhs.at<T>(x, y) *= rhs;
        }
    }

    return lhs;
}

template <typename T>
inline constexpr auto operator/=(mat &lhs, const T rhs) -> mat &
{
    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            lhs.at<T>(x, y) /= rhs;
        }
    }

    return lhs;
}

template <typename T>
inline constexpr auto operator+(const mat_view &lhs, const T rhs) -> mat
{
    auto result = mat{element_type(lhs), dimensions(lhs), stride(lhs), std::data(lhs)};
    return std::move(result += rhs);
}

template <typename T>
inline constexpr auto operator-(const mat_view &lhs, const T rhs) -> mat
{
    auto result = mat{element_type(lhs), dimensions(lhs), stride(lhs), std::data(lhs)};
    return std::move(result -= rhs);
}

template <typename T>
inline constexpr auto operator*(const mat_view &lhs, const T rhs) -> mat
{
    auto result = mat{element_type(lhs), dimensions(lhs), stride(lhs), std::data(lhs)};
    return std::move(result *= rhs);
}

template <typename T>
inline constexpr auto operator/(const mat_view &lhs, const T rhs) -> mat
{
    auto result = mat{element_type(lhs), dimensions(lhs), stride(lhs), std::data(lhs)};
    return std::move(result /= rhs);
}

} // namespace aeon::math
