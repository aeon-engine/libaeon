// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

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
    aeon_assert((val >= min && val <= max),                                                                            \
                "Value " #val " is out of range. Given value must be >= " #min " and <= " #max)

#define aeon_assert_index_bounds(val, count)                                                                           \
    aeon_assert((val < count), "Value " #val " is out of bounds. Given index must be < " #count)
#define aeon_assert_array_bounds(val, index)                                                                           \
    aeon_assert((index < (aeon_array_length(val))), "Array index " #index " is out of bounds for " #val)
#define aeon_assert_size_bounds(val, index)                                                                            \
    aeon_assert((static_cast<std::size_t>(index) < (std::size(val))),                                                  \
                "Array index " #index " is out of bounds for " #val)
