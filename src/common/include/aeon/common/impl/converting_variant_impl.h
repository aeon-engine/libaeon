// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/common/impl/converting_variant_enum_traits.h>
#include <aeon/common/impl/converting_variant_conversion.h>
#include <cassert>

namespace aeon::common
{

namespace internal
{

template <typename T>
static constexpr auto is_supported_variant_type_v =
    type_traits::is_any_same_v<T, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t,
                               std::int64_t, std::uint64_t, float, double, std::string, bool>;

} // namespace internal

inline converting_variant::converting_variant() noexcept
    : data_{}
    , type_{static_cast<std::uint32_t>(type::unknown)}
    , user_index_{0}
{
}

template <typename T, std::enable_if_t<!std::is_same_v<converting_variant, T>, int>>
inline converting_variant::converting_variant(T &&value, const int user_index)
    : data_{typename internal::converting_variant_object_traits<T>::type{std::forward<T>(value)}}
    , type_{static_cast<std::uint32_t>(internal::converting_variant_enum_traits<T>::type)}
    , user_index_{static_cast<std::uint32_t>(user_index)}
{
}

template <typename T, std::enable_if_t<!std::is_same_v<converting_variant, T>, int>>
inline converting_variant::converting_variant(const T &value, const int user_index)
    : data_{typename internal::converting_variant_object_traits<T>::type{value}}
    , type_{static_cast<std::uint32_t>(internal::converting_variant_enum_traits<T>::type)}
    , user_index_{static_cast<std::uint32_t>(user_index)}
{
}

inline auto converting_variant::type() const noexcept -> enum class type { return static_cast<enum class type>(type_); }

inline auto converting_variant::is_user_type() const noexcept -> bool
{
    return type() == type::user;
}

inline auto converting_variant::user_index() const noexcept -> int
{
    if (!is_user_type() || is_null())
        return 0;

    return user_index_;
}

inline auto converting_variant::is_null() const noexcept -> bool
{
    return data_.index() == 0;
}

template <typename T>
inline void converting_variant::set_value(T &&value, const int user_index)
{
    *this = converting_variant{std::forward<T>(value), user_index};
}

template <typename T>
inline void converting_variant::set_value(const T &value, const int user_index)
{
    *this = converting_variant{value, user_index};
}

template <typename T>
inline auto converting_variant::get_value() const -> T
{
    if (is_null())
        throw std::bad_variant_access{};

    if constexpr (internal::is_supported_variant_type_v<T>)
    {
        switch (type())
        {
            case type::int8:
                return get_value_internal<std::int8_t, T>();
            case type::uint8:
                return get_value_internal<std::uint8_t, T>();
            case type::int16:
                return get_value_internal<std::int16_t, T>();
            case type::uint16:
                return get_value_internal<std::uint16_t, T>();
            case type::int32:
                return get_value_internal<std::int32_t, T>();
            case type::uint32:
                return get_value_internal<std::uint32_t, T>();
            case type::int64:
                return get_value_internal<std::int64_t, T>();
            case type::uint64:
                return get_value_internal<std::uint64_t, T>();
            case type::float_t:
                return get_value_internal<float, T>();
            case type::double_t:
                return get_value_internal<double, T>();
            case type::boolean:
                return get_value_internal<bool, T>();
            case type::string:
                return get_value_internal<std::string, T>();
            case type::user:
            case type::unknown:
            default:
                throw std::bad_variant_access{};
        }
    }
    else
    {
        return std::any_cast<T>(std::get<std::any>(data_));
    }
}

template <typename from_t, typename to_t>
inline auto converting_variant::get_value() const -> to_t
{
    if constexpr (internal::is_supported_variant_type_v<from_t>)
    {
        return static_cast<to_t>(get_value<from_t>());
    }
    else
    {
        return get_user_value_internal<from_t, to_t>();
    }
}

template <typename T>
inline void converting_variant::convert_value()
{
    set_value(get_value<T>(), user_index_);
}

template <typename from_t, typename to_t>
inline void converting_variant::convert_value()
{
    set_value(get_value<from_t, to_t>());
}

template <typename from_t, typename to_t>
inline auto converting_variant::get_value_internal() const -> to_t
{
    assert(!is_null());
    assert(internal::converting_variant_enum_traits<from_t>::type == static_cast<enum class type>(type_));

    if constexpr (std::is_same_v<from_t, to_t>)
        return std::get<from_t>(data_);
    else
        return converting_variant_conversion<from_t, to_t>::convert(std::get<from_t>(data_));
}

template <typename from_t, typename to_t>
inline auto converting_variant::get_user_value_internal() const -> to_t
{
    assert(!is_null());
    assert(is_user_type());

    const auto &value = std::any_cast<from_t>(std::get<std::any>(data_));

    if constexpr (std::is_same_v<from_t, to_t>)
        return value;
    else
    {
        if constexpr (internal::is_supported_variant_type_v<from_t>)
            return converting_variant_conversion<from_t, to_t>::convert(value);
        else
            return static_cast<to_t>(value);
    }
}

} // namespace aeon::common
