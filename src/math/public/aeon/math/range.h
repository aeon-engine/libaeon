// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

/*!
 * \file
 * \brief Mathematical operations for a range.
 */

#pragma once

#include <aeon/common/concepts.h>

namespace aeon::math
{

/*!
 * Class that represents a range (begin-end).
 */
template <common::concepts::arithmetic_convertible T>
class range
{
public:
    /*!
     * Create an empty range. This initializes begin and end to 0.
     */
    constexpr range() noexcept;

    /*!
     * Create a range based on the given begin and end.
     */
    constexpr range(const T begin, const T end) noexcept;

    ~range() noexcept = default;

    constexpr range(const range &) noexcept = default;
    constexpr auto operator=(const range &) noexcept -> range & = default;

    constexpr range(range &&) noexcept = default;
    constexpr auto operator=(range &&) noexcept -> range & = default;

    T begin;
    T end;
};

/*!
 * Get the begin of a range
 * \param[in] range - Range
 * \return Begin of a range
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto begin(const range<T> &range) noexcept -> T;

/*!
 * Get the end of a range
 * \param[in] range - Range
 * \return End of a range
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto end(const range<T> &range) noexcept -> T;

/*!
 * Get the size of a range
 * \param[in] range - Range
 * \return Size of a range (end-begin)
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto size(const range<T> &range) noexcept -> T;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator==(const range<T> &lhs, const range<T> &rhs) noexcept -> bool;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator!=(const range<T> &lhs, const range<T> &rhs) noexcept -> bool;

} // namespace aeon::math

#include <aeon/math/impl/range_impl.h>
