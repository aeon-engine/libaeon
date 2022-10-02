// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/math/impl/units_prefixes.h>
#include <aeon/common/type_traits.h>
#include <type_traits>

namespace aeon::math
{

/*!
 * Check if a given unit is of the same type (ie. a unit of distance, or a unit of mass etc.)
 */
template <typename T, typename U>
struct unit_is_same_type
{
    static constexpr auto value = std::is_same<typename T::type, typename U::type>::value;
};

/*!
 * Convenience value variant of unit_is_same_type.
 */
template <typename T, typename U>
inline constexpr auto unit_is_same_type_v = unit_is_same_type<T, U>::value;

/*!
 * Get the unit type from a given combination of unit template arguments
 * <type, void> or <prefix, type>
 */
template <typename T, typename U>
struct unit_type
{
    using type = std::conditional_t<std::is_same_v<U, void>, T, U>;
};

/*!
 * Convenience type variant of unit_type.
 */
template <typename T, typename U>
using unit_type_t = typename unit_type<T, U>::type;

/*!
 * Get the unit prefix from a given combination of unit template arguments (or void).
 * <type, void> or <prefix, type>
 */
template <typename T, typename U>
struct unit_prefix
{
    using type = std::conditional_t<std::is_same_v<U, void>, void, T>;
};

/*!
 * Convenience type variant of unit_prefix.
 */
template <typename T, typename U>
using unit_prefix_t = typename unit_prefix<T, U>::type;

/*!
 * Get the prefix multiplication modifier value for a given template.
 * If the template isn't a prefix, value is 1.0.
 */
template <typename T>
struct prefix_value
{
private:
    static constexpr auto get() noexcept -> double
    {
        if constexpr (std::is_base_of_v<prefix, T>)
        {
            return T::value;
        }
        else
        {
            return 1.0;
        }
    }

public:
    static constexpr auto value = get();
};

/*!
 * Convenience value variant of prefix_value.
 */
template <typename T>
inline constexpr auto prefix_value_v = prefix_value<T>::value;

/*!
 * Check if a given unit type is a base type (like meters or grams)
 */
template <typename T>
struct is_base_type
{
    static constexpr auto value = std::is_same_v<T, typename T::type::base_type>;
};

/*!
 * Convenience value variant of is_base_type.
 */
template <typename T>
inline constexpr auto is_base_type_v = is_base_type<T>::value;

/*!
 * Check if a given unit type has a multiplier conversion value.
 */
template <typename T>
concept unit_with_multiplier = requires(T)
{
    T::multiplier;
};

/*!
 * Check if a given unit type has an offset conversion value.
 */
template <typename T>
concept unit_with_offset = requires(T)
{
    T::offset;
};

} // namespace aeon::math
