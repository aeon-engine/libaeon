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
 * Define a trait to check if a certain struct or class has a member variable.
 * \param trait_name The name of the type trait
 * \param member_type The value type of the member variable to be checked
 * \param member_name The name of the member variable to be checked.
 */
#define aeon_define_member_value_check_trait(trait_name, member_type, member_name)                                     \
    template <typename T>                                                                                              \
    struct trait_name                                                                                                  \
    {                                                                                                                  \
        struct member_value_t                                                                                          \
        {                                                                                                              \
            member_type member_name;                                                                                   \
        };                                                                                                             \
                                                                                                                       \
        struct member_value_check_t : T, member_value_t                                                                \
        {                                                                                                              \
        };                                                                                                             \
                                                                                                                       \
        template <typename C, C>                                                                                       \
        struct check_member_type_t;                                                                                    \
                                                                                                                       \
        template <typename C>                                                                                          \
        static constexpr char (&f(check_member_type_t<double member_value_t::*, &C::member_name> *))[1];               \
        template <typename C>                                                                                          \
        static constexpr char (&f(...))[2];                                                                            \
                                                                                                                       \
        static constexpr auto value = sizeof(f<member_value_check_t>(nullptr)) == 2;                                   \
    }

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

template <typename T>
struct is_std_vector
{
    static constexpr auto value = std::is_same_v<T, std::vector<typename T::value_type, typename T::allocator_type>>;
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

} // namespace aeon::common::type_traits
