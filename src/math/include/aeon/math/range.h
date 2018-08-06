/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
inline auto begin(const range<T> &range) noexcept -> T;

/*!
 * Get the end of a range
 * \param[in] range - Range
 * \return End of a range
 */
template <typename T>
inline auto end(const range<T> &range) noexcept -> T;

/*!
 * Get the size of a range
 * \param[in] range - Range
 * \return Size of a range (end-begin)
 */
template <typename T>
inline auto size(const range<T> &range) noexcept -> T;

template <typename T>
inline auto operator==(const range<T> &lhs, const range<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const range<T> &lhs, const range<T> &rhs) noexcept -> bool;

} // namespace aeon::math

#include <aeon/math/impl/range_impl.h>
