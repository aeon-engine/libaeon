// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/concepts.h>
#include <aeon/math/range.h>
#include <aeon/math/vector3.h>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
class line_segment3d : public range<vector3<T>>
{
public:
    /*!
     * Create an empty line_segment3d. This initializes begin and end to [0, 0].
     */
    constexpr line_segment3d() noexcept;

    /*!
     * Create a range based on the given begin and end.
     */
    constexpr line_segment3d(const vector3<T> &begin, const vector3<T> &end) noexcept;

    /*!
     * Create a range based on the given begin and end.
     */
    constexpr line_segment3d(const T begin_x, const T begin_y, const T begin_z, const T end_x, const T end_y,
                             const T end_z) noexcept;

    ~line_segment3d() noexcept = default;

    constexpr line_segment3d(const line_segment3d &) noexcept = default;
    constexpr auto operator=(const line_segment3d &) noexcept -> line_segment3d & = default;

    constexpr line_segment3d(line_segment3d &&) noexcept = default;
    constexpr auto operator=(line_segment3d &&) noexcept -> line_segment3d & = default;
};

} // namespace aeon::math

#include <aeon/math/impl/line_segment3d_impl.h>
