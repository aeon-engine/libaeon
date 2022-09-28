// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/type_traits.h>
#include <concepts>
#include <type_traits>
#include <tuple>

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
concept signed_enumerable = enumerable<T> && std::is_signed_v<std::underlying_type_t<T>>;

/*!
 * The given type must be an enum, with an unsigned underlying type (such as unsigned int)
 */
template <typename T>
concept unsigned_enumerable = enumerable<T> && std::is_unsigned_v<std::underlying_type_t<T>>;

/*!
 * The given type must be integral or std::atomic integral
 */
template <typename T>
concept integral_or_atomic_integral = std::integral<T> ||
    (type_traits::is_atomic_v<T> &&std::integral<typename T::value_type>);

/*!
 * Helper struct to be used with brace_constructible. Can use used to check if a given type is brace constructible with
 * a certain amount of types; but the type itself doesn't matter.
 */
struct any_convertible
{
    template <class T>
    constexpr operator T();
};

/*!
 * The given type T must be brace constructible with the given argument types
 */
template <typename T, typename... args_t>
concept brace_constructible = requires
{
    T{std::declval<args_t>()...};
};

/*!
 * The given type T must be brace constructible with the given argument types
 */
template <brace_constructible T, typename... args_t>
inline constexpr bool is_brace_constructible_v = brace_constructible<T, args_t...>;

/*!
 * Check if an index is valid for the given tuple.
 */
template <typename T, std::size_t N>
constexpr bool is_tuple_element = requires(T t)
{
    typename std::tuple_element_t<N - 1, std::remove_const_t<T>>;
    {
        get<N - 1>(t)
        } -> std::convertible_to<std::tuple_element_t<N - 1, T> &>;
}
&&is_tuple_element<T, N - 1>;

/*!
 * Check if an index is valid for the given tuple.
 */
template <typename T>
constexpr bool is_tuple_element<T, 0> = true;

/*!
 * The given type T must be a tuple-like type. A type is tuple-like when the tuple functions apply to it: std::get,
 * std::tuple_element and std::tuple_size.
 */
template <typename T>
concept tuple_like = !std::is_reference_v<T> && requires
{
    typename std::tuple_size<T>::type;
    requires std::same_as<decltype(std::tuple_size_v<T>), size_t>;
}
&&is_tuple_element<T, std::tuple_size_v<T>>;

} // namespace aeon::common::concepts
