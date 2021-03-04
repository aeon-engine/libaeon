// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <cstdint>
#include <vector>

namespace aeon::common::type_traits
{

namespace internal
{

template <typename T>
struct empty_base
{
};

} // namespace internal

/*!
 * Get the amount of arguments in a function signature type.
 */
template <typename return_type_t>
struct function_signature_argument_count;

template <typename return_type_t, typename... args_t>
struct function_signature_argument_count<return_type_t(args_t...)>
{
    static constexpr auto value = sizeof...(args_t);
};

/*!
 * Derive from another class/struct optionally based on a given condition.
 * If the condition is false, a dummy inheritance will take place instead.
 */
template <bool condition, typename T>
using optional_base = std::conditional_t<condition, T, internal::empty_base<T>>;

/*!
 * Get a representing integer type based on given number of bits
 */
template <unsigned int bits>
struct integer_type_from_bits;

template <>
struct integer_type_from_bits<8>
{
    using signed_t = std::int8_t;
    using unsigned_t = std::uint8_t;
};

template <>
struct integer_type_from_bits<16>
{
    using signed_t = std::int16_t;
    using unsigned_t = std::uint16_t;
};

template <>
struct integer_type_from_bits<32>
{
    using signed_t = std::int32_t;
    using unsigned_t = std::uint32_t;
};

template <>
struct integer_type_from_bits<64>
{
    using signed_t = std::int64_t;
    using unsigned_t = std::uint64_t;
};

template <typename>
struct is_std_vector : std::false_type
{
};

template <typename T, typename A>
struct is_std_vector<std::vector<T, A>> : std::true_type
{
};

/*!
 * Check if a given type is an std::vector
 */
template <typename T>
static constexpr auto is_std_vector_v = is_std_vector<T>::value;

/*!
 * Variadic version of is_same_v
 */
template <class T, class... U>
static constexpr auto is_any_same_v = (std::is_same_v<T, U> || ...);

/*!
 * Change one type into another while preserving const
 */
template <typename T, typename U>
struct preserve_const
{
    using type = std::conditional_t<std::is_const_v<std::remove_pointer_t<T>>, const U, U>;
};

/*!
 * Change one type into another while preserving const
 */
template <typename T, typename U>
using preserve_const_t = typename preserve_const<T, U>::type;

/*!
 * Change one type into another while preserving volatile
 */
template <typename T, typename U>
struct preserve_volatile
{
    using type = std::conditional_t<std::is_volatile_v<std::remove_pointer_t<T>>, volatile U, U>;
};

/*!
 * Change one type into another while preserving volatile
 */
template <typename T, typename U>
using preserve_volatile_t = typename preserve_volatile<T, U>::type;

/*!
 * Change one type into another while preserving const and volatile
 */
template <typename T, typename U>
struct preserve_cv
{
    using type = preserve_const_t<T, preserve_volatile_t<T, U>>;
};

/*!
 * Change one type into another while preserving const and volatile
 */
template <typename T, typename U>
using preserve_cv_t = typename preserve_cv<T, U>::type;

/*!
 * Check if the given type is convertible to any integer
 */
template <typename T>
struct is_convertible_to_integral
{
    static constexpr auto value = std::is_convertible_v<T, std::int8_t> || std::is_convertible_v<T, std::uint8_t> ||
                                  std::is_convertible_v<T, std::int16_t> || std::is_convertible_v<T, std::uint16_t> ||
                                  std::is_convertible_v<T, std::int32_t> || std::is_convertible_v<T, std::uint32_t> ||
                                  std::is_convertible_v<T, std::int64_t> || std::is_convertible_v<T, std::uint64_t>;
};

/*!
 * Check if the given type is convertible to any integer
 */
template <typename T>
static constexpr auto is_convertible_to_integral_v = is_convertible_to_integral<T>::value;

/*!
 * Check if the given type is convertible to a floating point value
 */
template <typename T>
struct is_convertible_to_floating_point
{
    static constexpr auto value = std::is_convertible_v<T, float> || std::is_convertible_v<T, double>;
};

/*!
 * Check if the given type is convertible to a floating point value
 */
template <typename T>
static constexpr auto is_convertible_to_floating_point_v = is_convertible_to_floating_point<T>::value;

/*!
 * Check if the given type is convertible to any number
 */
template <typename T>
struct is_convertible_to_arithmetic
{
    static constexpr auto value = is_convertible_to_integral_v<T> || is_convertible_to_floating_point_v<T>;
};

/*!
 * Check if the given type is convertible to any number
 */
template <typename T>
static constexpr auto is_convertible_to_arithmetic_v = is_convertible_to_arithmetic<T>::value;

} // namespace aeon::common::type_traits
