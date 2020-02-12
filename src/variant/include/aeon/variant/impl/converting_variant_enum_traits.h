// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/variant/converting_variant.h>

namespace aeon::variant::internal
{

template <typename T>
struct converting_variant_enum_traits
{
    static constexpr auto type = converting_variant::type::user;
};

template <>
struct converting_variant_enum_traits<std::int8_t>
{
    static constexpr auto type = converting_variant::type::int8;
};

template <>
struct converting_variant_enum_traits<std::uint8_t>
{
    static constexpr auto type = converting_variant::type::uint8;
};

template <>
struct converting_variant_enum_traits<std::int16_t>
{
    static constexpr auto type = converting_variant::type::int16;
};

template <>
struct converting_variant_enum_traits<std::uint16_t>
{
    static constexpr auto type = converting_variant::type::uint16;
};

template <>
struct converting_variant_enum_traits<std::int32_t>
{
    static constexpr auto type = converting_variant::type::int32;
};

template <>
struct converting_variant_enum_traits<std::uint32_t>
{
    static constexpr auto type = converting_variant::type::uint32;
};

template <>
struct converting_variant_enum_traits<std::int64_t>
{
    static constexpr auto type = converting_variant::type::int64;
};

template <>
struct converting_variant_enum_traits<std::uint64_t>
{
    static constexpr auto type = converting_variant::type::uint64;
};

template <>
struct converting_variant_enum_traits<float>
{
    static constexpr auto type = converting_variant::type::float_t;
};

template <>
struct converting_variant_enum_traits<double>
{
    static constexpr auto type = converting_variant::type::double_t;
};

template <>
struct converting_variant_enum_traits<bool>
{
    static constexpr auto type = converting_variant::type::boolean;
};

template <>
struct converting_variant_enum_traits<std::string>
{
    static constexpr auto type = converting_variant::type::string;
};

template <>
struct converting_variant_enum_traits<chrono::calendar>
{
    static constexpr auto type = converting_variant::type::calendar;
};

template <typename T>
struct converting_variant_object_traits
{
    using type = std::any;
};

template <>
struct converting_variant_object_traits<std::int8_t>
{
    using type = std::int8_t;
};

template <>
struct converting_variant_object_traits<std::uint8_t>
{
    using type = std::uint8_t;
};

template <>
struct converting_variant_object_traits<std::int16_t>
{
    using type = std::int16_t;
};

template <>
struct converting_variant_object_traits<std::uint16_t>
{
    using type = std::uint16_t;
};

template <>
struct converting_variant_object_traits<std::int32_t>
{
    using type = std::int32_t;
};

template <>
struct converting_variant_object_traits<std::uint32_t>
{
    using type = std::uint32_t;
};

template <>
struct converting_variant_object_traits<std::int64_t>
{
    using type = std::int64_t;
};

template <>
struct converting_variant_object_traits<std::uint64_t>
{
    using type = std::uint64_t;
};

template <>
struct converting_variant_object_traits<float>
{
    using type = float;
};

template <>
struct converting_variant_object_traits<double>
{
    using type = double;
};

template <>
struct converting_variant_object_traits<std::string>
{
    using type = std::string;
};

template <>
struct converting_variant_object_traits<chrono::calendar>
{
    using type = chrono::calendar;
};

template <>
struct converting_variant_object_traits<bool>
{
    using type = bool;
};

} // namespace aeon::variant::internal
