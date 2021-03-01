// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/size2d.h>
#include <aeon/math/vector2.h>
#include <aeon/math/math.h>
#include <aeon/common/assert.h>
#include <algorithm>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline constexpr rectangle<T>::rectangle() noexcept
    : left{}
    , top{}
    , right{}
    , bottom{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr rectangle<T>::rectangle(const T left, const T top, const T right, const T bottom) noexcept
    : left{left}
    , top{top}
    , right{right}
    , bottom{bottom}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr rectangle<T>::rectangle(const vector2<T> left_top, const vector2<T> right_bottom) noexcept
    : left{left_top.x}
    , top{left_top.y}
    , right{right_bottom.x}
    , bottom{right_bottom.y}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr rectangle<T>::rectangle(const T left, const T top, const size2d<T> size) noexcept
    : rectangle{vector2{left, top}, size}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr rectangle<T>::rectangle(const vector2<T> left_top, const size2d<T> size) noexcept
    : left{left_top.x}
    , top{left_top.y}
    , right{left_top.x + width(size)}
    , bottom{left_top.y + height(size)}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr rectangle<T>::rectangle(const size2d<T> size) noexcept
    : left{0}
    , top{0}
    , right{width(size)}
    , bottom{height(size)}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr rectangle<T>::rectangle(const vector2<T> position, const size2d<T> size,
                                         const anchor_point anchor) noexcept
{
    *this = positioned(rectangle{0, 0, size}, position, anchor);
}

template <common::concepts::arithmetic_convertible T>
template <common::concepts::arithmetic_convertible U>
inline constexpr rectangle<T>::rectangle(const rectangle<U> &other) noexcept
    : left{static_cast<T>(other.left)}
    , top{static_cast<T>(other.top)}
    , right{static_cast<T>(other.right)}
    , bottom{static_cast<T>(other.bottom)}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto left(const rectangle<T> &rect) noexcept -> T
{
    return rect.left;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto top(const rectangle<T> &rect) noexcept -> T
{
    return rect.top;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto right(const rectangle<T> &rect) noexcept -> T
{
    return rect.right;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto bottom(const rectangle<T> &rect) noexcept -> T
{
    return rect.bottom;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto width(const rectangle<T> &rect) noexcept -> T
{
    return right(rect) - left(rect);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto height(const rectangle<T> &rect) noexcept -> T
{
    return bottom(rect) - top(rect);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto left_top(const rectangle<T> &rect) noexcept -> vector2<T>
{
    return {left(rect), top(rect)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto right_top(const rectangle<T> &rect) noexcept -> vector2<T>
{
    return {right(rect), top(rect)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto left_bottom(const rectangle<T> &rect) noexcept -> vector2<T>
{
    return {left(rect), bottom(rect)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto right_bottom(const rectangle<T> &rect) noexcept -> vector2<T>
{
    return {right(rect), bottom(rect)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto center(const rectangle<T> &rect) noexcept -> vector2<T>
{
    return {(left(rect) + right(rect)) / T(2), (top(rect) + bottom(rect)) / T(2)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto empty(const rectangle<T> &rect) noexcept -> bool
{
    return right(rect) == left(rect) || bottom(rect) == top(rect);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto null(const rectangle<T> &rect) noexcept -> bool
{
    return right(rect) == left(rect) && bottom(rect) == top(rect);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto valid(const rectangle<T> &rect) noexcept -> bool
{
    return left(rect) < right(rect) && top(rect) < bottom(rect);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto size(const rectangle<T> &rect) noexcept -> size2d<T>
{
    return {width(rect), height(rect)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto resized(const rectangle<T> &rect, const size2d<T> &size) noexcept -> rectangle<T>
{
    return {left_top(rect), size};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto resized(const rectangle<T> &rect, const T width, const T height) noexcept -> rectangle<T>
{
    return resized(rect, size2d{width, height});
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void set_size(rectangle<T> &rect, const size2d<T> &size) noexcept
{
    rect = resized(rect, size);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void set_size(rectangle<T> &rect, const T width, const T height) noexcept
{
    rect = resized(rect, width, height);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void translate(rectangle<T> &rect, const T x, const T y) noexcept
{
    rect = translated(rect, x, y);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void translate(rectangle<T> &rect, const U x, const U y) noexcept
{
    rect = translated(rect, x, y);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void translate(rectangle<T> &rect, const vector2<T> &vec) noexcept
{
    rect = translated(rect, vec);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void translate(rectangle<T> &rect, const vector2<U> &vec) noexcept
{
    rect = translated(rect, vec);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto translated(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>
{
    return {rect.left + x, rect.top + y, rect.right + x, rect.bottom + y};
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto translated(const rectangle<T> &rect, const U x, const U y) noexcept -> rectangle<T>
{
    const auto x_new = static_cast<T>(x);
    const auto y_new = static_cast<T>(y);
    return {rect.left + x_new, rect.top + y_new, rect.right + x_new, rect.bottom + y_new};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto translated(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> rectangle<T>
{
    return translated(rect, vec.x, vec.y);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto translated(const rectangle<T> &rect, const vector2<U> &vec) noexcept -> rectangle<T>
{
    return translated(rect, static_cast<T>(vec.x), static_cast<T>(vec.y));
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void set_position(rectangle<T> &rect, const T x, const T y) noexcept
{
    rect = positioned(rect, x, y);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void set_position(rectangle<T> &rect, const vector2<T> &vec) noexcept
{
    rect = positioned(rect, vec);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void set_position(rectangle<T> &rect, const T x, const T y, const anchor_point anchor) noexcept
{
    rect = positioned(rect, x, y, anchor);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void set_position(rectangle<T> &rect, const vector2<T> &vec, const anchor_point anchor) noexcept
{
    rect = positioned(rect, vec, anchor);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto positioned(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>
{
    const auto w = width(rect);
    const auto h = height(rect);
    return {x, y, x + w, y + h};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto positioned(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> rectangle<T>
{
    return positioned(rect, vec.x, vec.y);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto positioned(const rectangle<T> &rect, const T x, const T y, const anchor_point anchor) noexcept
    -> rectangle<T>
{
    const auto w = width(rect);
    const auto h = height(rect);

    switch (anchor)
    {
        case anchor_point::left_top:
            return {x, y, x + w, y + h};
        case anchor_point::left_center:
        {
            const auto top = y - (h / T(2));
            return {x, top, x + w, top + h};
        }
        case anchor_point::left_bottom:
            return {x, y - h, x + w, y};
        case anchor_point::right_top:
            return {x - w, y, x, y + h};
        case anchor_point::right_center:
        {
            const auto top = y - (h / T(2));
            return {x - w, top, x, top + h};
        }
        case anchor_point::right_bottom:
            return {x - w, y - h, x, y};
        case anchor_point::top_center:
        {
            const auto left = x - (w / T(2));
            return {left, y, left + w, y + h};
        }
        case anchor_point::bottom_center:
        {
            const auto left = x - (w / T(2));
            return {left, y - h, left + w, y};
        }
        case anchor_point::center:
        {
            const auto left = x - (w / T(2));
            const auto top = y - (h / T(2));
            return {left, top, left + w, top + h};
        }
        default:
        {
            aeon_assert_fail("Unexpected anchor point.");
            return {};
        }
    }
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto positioned(const rectangle<T> &rect, const vector2<T> &vec, const anchor_point anchor) noexcept
    -> rectangle<T>
{
    return positioned(rect, vec.x, vec.y, anchor);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto contains(const rectangle<T> &inner, const rectangle<T> &outer) noexcept -> bool
{
    return (left(inner) >= left(outer) && top(inner) >= top(outer) && right(inner) <= right(outer) &&
            bottom(inner) <= bottom(outer));
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto contains(const vector2<T> &vec, const rectangle<T> &rect) noexcept -> bool
{
    return (vec.x >= left(rect) && vec.y >= top(rect) && vec.x <= right(rect) && vec.y <= bottom(rect));
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto overlaps(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept -> bool
{
    return left(rect1) < right(rect2) && left(rect2) < right(rect1) && top(rect1) < bottom(rect2) &&
           top(rect2) < bottom(rect1);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto intersection(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept -> rectangle<T>
{
    // clang-format off
    return {
        std::max(left(rect1), left(rect2)),
        std::max(top(rect1), top(rect2)),
        std::min(right(rect1), right(rect2)),
        std::min(bottom(rect1), bottom(rect2))};
    // clang-format on
}

template <common::concepts::arithmetic_convertible T, typename... U>
inline constexpr auto bounding_box(const rectangle<T> &first, const rectangle<U> &...rectangles) noexcept
    -> rectangle<T>
{
    // clang-format off
    return {
        min(left(first), left(rectangles)...),
        min(top(first), top(rectangles)...),
        max(right(first), right(rectangles)...),
        max(bottom(first), bottom(rectangles)...)};
    // clang-format on
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void inflate(rectangle<T> &rect, const T val) noexcept
{
    rect = inflated(rect, val);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto inflated(const rectangle<T> &rect, const T val) noexcept -> rectangle<T>
{
    return rect + val;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(rectangle<T> &rect, const T val) noexcept
{
    rect = scaled(rect, val);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(rectangle<T> &rect, const U val) noexcept
{
    rect = scaled(rect, val);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(rectangle<T> &rect, const T x, const T y) noexcept
{
    rect = scaled(rect, x, y);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(rectangle<T> &rect, const U x, const U y) noexcept
{
    rect = scaled(rect, x, y);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(rectangle<T> &rect, const vector2<T> &vec) noexcept
{
    rect = scaled(rect, vec);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(rectangle<T> &rect, const vector2<U> &vec) noexcept
{
    rect = scaled(rect, vec);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(rectangle<T> &rect, const size2d<T> &size) noexcept
{
    rect = scaled(rect, size);
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(rectangle<T> &rect, const size2d<U> &size) noexcept
{
    rect = scaled(rect, size);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto scaled(const rectangle<T> &rect, const T val) noexcept -> rectangle<T>
{
    return rect * val;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto scaled(const rectangle<T> &rect, const U val) noexcept -> rectangle<T>
{
    return rect * static_cast<T>(val);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto scaled(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>
{
    return scaled(rect, {x, y});
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto scaled(const rectangle<T> &rect, const U x, const U y) noexcept -> rectangle<T>
{
    return scaled(rect, {static_cast<T>(x), static_cast<T>(y)});
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto scaled(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> rectangle<T>
{
    return rect * vec;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto scaled(const rectangle<T> &rect, const vector2<U> &vec) noexcept -> rectangle<T>
{
    return rect * vector2<T>{vec};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto scaled(const rectangle<T> &rect, const size2d<T> &size) noexcept -> rectangle<T>
{
    return rect * size;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto scaled(const rectangle<T> &rect, const size2d<U> &size) noexcept -> rectangle<T>
{
    return rect * size2d<T>{size};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto distance(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept -> T
{
    return distance(center(rect1), center(rect2));
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto distance(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> T
{
    return distance(center(rect), vec);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto area(const rectangle<T> &rect) noexcept -> T
{
    return width(rect) * height(rect);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto closest_point(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::clamp(vec.x, left(rect), right(rect)), std::clamp(vec.y, top(rect), bottom(rect))};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void normalize(rectangle<T> &rect) noexcept
{
    rect = normalized(rect);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto normalized(const rectangle<T> &rect) noexcept -> rectangle<T>
{
    auto l = left(rect);
    auto r = right(rect);

    if (width(rect) < T(0))
        std::swap(l, r);

    auto t = top(rect);
    auto b = bottom(rect);

    if (height(rect) < T(0))
        std::swap(t, b);

    return {l, t, r, b};
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto slice_horizontal(const rectangle<T> &rect, const U ratio,
                                       std::enable_if_t<std::is_floating_point_v<U>> *) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>
{
    aeon_assert_value_in_range(ratio, 0.0f, 1.0f);

    const auto slice_point = static_cast<T>((static_cast<U>(height(rect)) * ratio) + top(rect));
    return slice_horizontal_absolute(rect, slice_point);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto slice_horizontal_absolute(const rectangle<T> &rect, const T value) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>
{
    aeon_assert_value_in_range(value, top(rect), bottom(rect));

    return {{left(rect), top(rect), right(rect), value}, {left(rect), value, right(rect), bottom(rect)}};
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto slice_vertical(const rectangle<T> &rect, const U ratio,
                                     std::enable_if_t<std::is_floating_point_v<U>> *) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>
{
    aeon_assert_value_in_range(ratio, 0.0f, 1.0f);

    const auto slice_point = static_cast<T>((static_cast<U>(width(rect)) * ratio) + left(rect));
    return slice_vertical_absolute(rect, slice_point);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto slice_vertical_absolute(const rectangle<T> &rect, const T value) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>
{
    aeon_assert_value_in_range(value, left(rect), right(rect));

    return {{left(rect), top(rect), value, bottom(rect)}, {value, top(rect), right(rect), bottom(rect)}};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto round(const rectangle<T> &rect) noexcept -> rectangle<T>
{
    return {std::round(left(rect)), std::round(top(rect)), std::round(right(rect)), std::round(bottom(rect))};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator==(const rectangle<T> &lhs, const rectangle<T> &rhs) noexcept -> bool
{
    return left(lhs) == left(rhs) && top(lhs) == top(rhs) && right(lhs) == right(rhs) && bottom(lhs) == bottom(rhs);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator!=(const rectangle<T> &lhs, const rectangle<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) - rhs, top(lhs) - rhs, right(lhs) + rhs, bottom(lhs) + rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) - rhs.x, top(lhs) - rhs.y, right(lhs) + rhs.x, bottom(lhs) + rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) + rhs, top(lhs) + rhs, right(lhs) - rhs, bottom(lhs) - rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) + rhs.x, top(lhs) + rhs.y, right(lhs) - rhs.x, bottom(lhs) - rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) * -rhs, top(lhs) * -rhs, right(lhs) * rhs, bottom(lhs) * rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const rectangle<T> &lhs, const size2d<T> &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) * -rhs.width, top(lhs) * -rhs.height, right(lhs) * rhs.width, bottom(lhs) * rhs.height};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(rectangle<T> &lhs, const size2d<T> &rhs) noexcept -> rectangle<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) * -rhs.x, top(lhs) * -rhs.y, right(lhs) * rhs.x, bottom(lhs) * rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>
{
    lhs = lhs * rhs;
    return lhs;
}

} // namespace aeon::math
