// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/concepts.h>
#include <aeon/math/range.h>
#include <aeon/math/vector2.h>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
class line_segment2d : public range<vector2<T>>
{
public:
    /*!
     * Create an empty line_segment2d. This initializes begin and end to [0, 0].
     */
    constexpr line_segment2d() noexcept;

    /*!
     * Create a range based on the given begin and end.
     */
    constexpr line_segment2d(const vector2<T> &begin, const vector2<T> &end) noexcept;

    /*!
     * Create a range based on the given begin and end.
     */
    constexpr line_segment2d(const T begin_x, const T begin_y, const T end_x, const T end_y) noexcept;

    ~line_segment2d() noexcept = default;

    constexpr line_segment2d(const line_segment2d &) noexcept = default;
    constexpr auto operator=(const line_segment2d &) noexcept -> line_segment2d & = default;

    constexpr line_segment2d(line_segment2d &&) noexcept = default;
    constexpr auto operator=(line_segment2d &&) noexcept -> line_segment2d & = default;
};

} // namespace aeon::math

#include <aeon/math/impl/line_segment2d_impl.h>
