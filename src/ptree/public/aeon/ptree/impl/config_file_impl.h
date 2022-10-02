// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <type_traits>
#include <stdexcept>

namespace aeon::ptree
{

namespace internal
{

inline auto get_header_object(const property_tree &pt, const std::u8string &header) noexcept
    -> std::optional<const object *>
{
    if (!pt.is_object())
        return std::nullopt;

    const auto &root_object = pt.object_value();
    const auto result = root_object.find(header);

    if (result == std::end(root_object))
        return std::nullopt;

    const auto &header_pt = result->second;

    if (!header_pt.is_object())
        return std::nullopt;

    return &header_pt.object_value();
}

inline auto get_entry(const property_tree &pt, const std::u8string &header, const std::u8string &key) noexcept
    -> std::optional<const ptree::property_tree *>
{
    const auto header_obj_ptr = get_header_object(pt, header);

    if (!header_obj_ptr)
        return std::nullopt;

    const auto &header_obj = *header_obj_ptr.value();
    const auto key_result = header_obj.find(key);

    if (key_result == std::end(header_obj))
        return std::nullopt;

    return &key_result->second;
}

} // namespace internal

inline config_file::config_file(property_tree &pt)
    : pt_{&pt}
{
}

inline auto config_file::has_header(const std::u8string &header) const noexcept -> bool
{
    return pt_->contains(header);
}

inline auto config_file::has_entry(const std::u8string &header, const std::u8string &key) const noexcept -> bool
{
    const auto header_object_ptr = internal::get_header_object(*pt_, header);

    if (!header_object_ptr)
        return false;

    return header_object_ptr.value()->contains(key);
}

template <config_file_value T>
inline auto config_file::get(const std::u8string &header, const std::u8string &key) const noexcept -> std::optional<T>
{
    const auto key_object_ptr = internal::get_entry(*pt_, header, key);

    if (!key_object_ptr)
        return std::nullopt;

    const auto &key_object = *key_object_ptr.value();

    if constexpr (std::is_same_v<T, bool>) // put up top since a bool is integral.
    {
        if (!key_object.is_bool())
            return std::nullopt;

        return key_object.bool_value();
    }
    else if constexpr (std::is_integral_v<T>)
    {
        if (!key_object.is_integer())
            return std::nullopt;

        return static_cast<T>(key_object.integer_value());
    }
    else if constexpr (std::is_floating_point_v<T>)
    {
        if (key_object.is_integer())
            return static_cast<T>(key_object.integer_value());

        if (!key_object.is_double())
            return std::nullopt;

        return static_cast<T>(key_object.double_value());
    }
    else if constexpr (std::is_same_v<T, std::u8string>)
    {
        if (!key_object.is_string())
            return std::nullopt;

        return key_object.string_value();
    }
    else if constexpr (std::is_same_v<T, common::uuid>)
    {
        if (!key_object.is_uuid())
            return std::nullopt;

        return key_object.uuid_value();
    }
    else
    {
        std::abort(); // This is a bug.
    }
}

template <config_file_value T>
inline auto config_file::get(const std::u8string &header, const std::u8string &key, const T &default_val) -> T
{
    const auto result = get<T>(header, key);

    if (!result)
    {
        set(header, key, default_val);
        return default_val;
    }

    return *result;
}

template <config_file_value T>
inline auto config_file::get_or_except(const std::u8string &header, const std::u8string &key) const -> T
{
    auto result = get<T>(header, key);

    if (!result)
        throw std::invalid_argument{"Config file header and/or key not found."};

    return result.value();
}

template <config_file_value T>
inline void config_file::set(const std::u8string &header, const std::u8string &key, const T &val)
{
    if (pt_->is_null())
        *pt_ = object{};

    if (!pt_->is_object())
        throw config_file_exception();

    auto &root_object = pt_->object_value();
    auto &header_pt = root_object[header];

    if (header_pt.is_null())
        header_pt = object{};

    if (!header_pt.is_object())
        throw config_file_exception();

    auto &header_object = header_pt.object_value();
    header_object[key] = val;
}

} // namespace aeon::ptree

#include <aeon/ptree/impl/config_file_impl.h>
