// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline constexpr auto operator+=(mat_view &lhs, const T rhs) noexcept -> mat_view &
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
inline constexpr auto operator-=(mat_view &lhs, const T rhs) noexcept -> mat_view &
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
inline constexpr auto operator*=(mat_view &lhs, const T rhs) noexcept -> mat_view &
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
inline constexpr auto operator/=(mat_view &lhs, const T rhs) noexcept -> mat_view &
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

namespace internal
{

template <typename T, typename U, typename V>
inline constexpr auto compare(const mat_view_base<T> &lhs, const mat_view_base<U> &rhs) noexcept -> bool
{
    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            if (lhs.template at<V>(x, y) != rhs.template at<V>(x, y))
                return false;
        }
    }

    return true;
}

} // namespace internal

template <typename T, typename U>
inline constexpr auto operator==(const mat_view_base<T> &lhs, const mat_view_base<U> &rhs) noexcept -> bool
{
    if (dimensions(lhs) != dimensions(rhs))
        return false;

    if (element_type(lhs) != element_type(rhs))
        return false;

    switch (element_type(lhs).name)
    {
        case common::element_type_name::u8:
            return internal::compare<T, U, std::uint8_t>(lhs, rhs);
        case common::element_type_name::s8:
            return internal::compare<T, U, std::int8_t>(lhs, rhs);
        case common::element_type_name::u16:
            return internal::compare<T, U, std::uint16_t>(lhs, rhs);
        case common::element_type_name::s16:
            return internal::compare<T, U, std::int16_t>(lhs, rhs);
        case common::element_type_name::u32:
            return internal::compare<T, U, std::uint32_t>(lhs, rhs);
        case common::element_type_name::s32:
            return internal::compare<T, U, std::int32_t>(lhs, rhs);
        case common::element_type_name::u64:
            return internal::compare<T, U, std::uint64_t>(lhs, rhs);
        case common::element_type_name::s64:
            return internal::compare<T, U, std::int64_t>(lhs, rhs);
        case common::element_type_name::f32:
            return internal::compare<T, U, float>(lhs, rhs);
        case common::element_type_name::f64:
            return internal::compare<T, U, double>(lhs, rhs);
        case common::element_type_name::undefined:
        default:
            return false;
    }
}

template <typename T, typename U>
inline constexpr auto operator!=(const mat_view_base<T> &lhs, const mat_view_base<U> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math
