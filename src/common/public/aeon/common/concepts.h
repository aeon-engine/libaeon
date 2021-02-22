// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/type_traits.h>
#include <concepts>
#include <type_traits>

namespace aeon::common::concepts
{

/*!
 * Given type must be arithmetic (int, float, etc.)
 */
template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

/*!
 * Given type must be arithmetic (int, float, etc.), or convertible to one
 */
template <typename T>
concept arithmetic_convertible = (std::is_arithmetic_v<T> ||
                                  type_traits::is_convertible_to_arithmetic_v<T>)&&!std::is_enum_v<T>;

} // namespace aeon::common::concepts
