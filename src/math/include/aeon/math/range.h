// Copyright (c) 2012-2019 Robin Degen

/*!
 * \file
 * \brief Mathmatical operations for a range.
 */

#pragma once

namespace aeon::math
{

/*!
 * Class that represents a range (begin-end).
 */
template <typename T>
class range
{
public:
    /*!
     * Create an empty range. This initializes begin and end to 0.
     */
    range() noexcept;

    /*!
     * Create a range based on the given begin and end.
     */
    range(const T begin, const T end) noexcept;

    ~range() noexcept = default;

    range(const range &) noexcept = default;
    auto operator=(const range &) noexcept -> range & = default;

    range(range &&) noexcept = default;
    auto operator=(range &&) noexcept -> range & = default;

    T begin;
    T end;
};

/*!
 * Get the begin of a range
 * \param[in] range - Range
 * \return Begin of a range
 */
template <typename T>
[[nodiscard]] inline auto begin(const range<T> &range) noexcept -> T;

/*!
 * Get the end of a range
 * \param[in] range - Range
 * \return End of a range
 */
template <typename T>
[[nodiscard]] inline auto end(const range<T> &range) noexcept -> T;

/*!
 * Get the size of a range
 * \param[in] range - Range
 * \return Size of a range (end-begin)
 */
template <typename T>
[[nodiscard]] inline auto size(const range<T> &range) noexcept -> T;

template <typename T>
inline auto operator==(const range<T> &lhs, const range<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const range<T> &lhs, const range<T> &rhs) noexcept -> bool;

} // namespace aeon::math

#include <aeon/math/impl/range_impl.h>
