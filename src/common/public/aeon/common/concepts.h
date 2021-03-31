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

/*!
 * The given type must be an enum
 */
template <typename T>
concept enumerable = std::is_enum_v<T>;

/*!
 * The given type must be an enum, with a signed underlying type (such as int)
 */
template <typename T>
concept signed_enumerable = enumerable<T> &&std::is_signed_v<std::underlying_type_t<T>>;

/*!
 * The given type must be an enum, with an unsigned underlying type (such as unsigned int)
 */
template <typename T>
concept unsigned_enumerable = enumerable<T> &&std::is_unsigned_v<std::underlying_type_t<T>>;

/*!
 * The given type must be integral or std::atomic integral
 */
template <typename T>
concept integral_or_atomic_integral = std::integral<T> ||
                                      (type_traits::is_atomic_v<T> && std::integral<typename T::value_type>);

} // namespace aeon::common::concepts
