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

#pragma once

#include <aeon/common/preprocessor.h>
#include <cassert>

#define aeon_assert(condition, message) assert((condition) && message)
#define aeon_assert_fail(message) aeon_assert(false, message)

#define aeon_assert_value_min(val, min)                                                                                \
    aeon_assert((val >= min), "Value " #val " is out of range. Given value must be >= " #min)
#define aeon_assert_value_max(val, max)                                                                                \
    aeon_assert((val <= max), "Value " #val " is out of range. Given value must be <= " #max)
#define aeon_assert_value_in_range(val, min, max)                                                                      \
    aeon_assert((val >= min || val <= max),                                                                            \
                "Value " #val " is out of range. Given value must be >= " #min " and <= " #max)

#define aeon_assert_index_bounds(val, count)                                                                           \
    aeon_assert((val < count), "Value " #val " is out of bounds. Given index must be < " #count)
#define aeon_assert_array_bounds(val, index)                                                                           \
    aeon_assert((index < (aeon_array_length(val))), "Array index " #index " is out of bounds for " #val)
