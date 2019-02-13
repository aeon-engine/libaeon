// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/utility/linear_map.h>
#include <aeon/utility/uuid.h>
#include <aeon/common/assert.h>
#include <variant>
#include <vector>
#include <string>
#include <cstddef>
#include <cstdint>

namespace aeon::ptree
{

class property_tree;
using array = std::vector<property_tree>;
using object = utility::linear_map<std::string, property_tree>;

class property_tree
{
public:
    property_tree()
        : value_{}
    {
    }

    property_tree(std::nullptr_t)
        : value_{}
    {
    }

    property_tree(const int value)
        : value_{static_cast<std::int64_t>(value)}
    {
    }

    property_tree(const std::int64_t value)
        : value_{value}
    {
    }

    property_tree(const double value)
        : value_{value}
    {
    }

    property_tree(const array &value)
        : value_{value}
    {
    }

    property_tree(const bool value)
        : value_{value}
    {
    }

    property_tree(array &&value)
        : value_{std::move(value)}
    {
    }

    property_tree(const object &value)
        : value_{value}
    {
    }

    property_tree(object &&value)
        : value_{std::move(value)}
    {
    }

    property_tree(const char *const value)
        : value_{std::string{value}}
    {
    }

    property_tree(const std::string &value)
        : value_{value}
    {
    }

    property_tree(std::string &&value)
        : value_{std::move(value)}
    {
    }

    property_tree(const utility::uuid &uuid)
        : value_{uuid}
    {
    }

    property_tree(utility::uuid &&uuid)
        : value_{std::move(uuid)}
    {
    }

    virtual ~property_tree() noexcept = default;

    property_tree(const property_tree &) = default;
    auto operator=(const property_tree &) -> property_tree & = default;

    property_tree(property_tree &&) noexcept = default;
    auto operator=(property_tree &&) noexcept -> property_tree & = default;

    template <typename T>
    auto is_type() const noexcept
    {
        return std::holds_alternative<T>(value_);
    }

    auto is_array() const noexcept
    {
        return is_type<array>();
    }

    auto is_object() const noexcept
    {
        return is_type<object>();
    }

    auto is_string() const noexcept
    {
        return is_type<std::string>();
    }

    auto is_uuid() const noexcept
    {
        return is_type<utility::uuid>();
    }

    auto is_integer() const noexcept
    {
        return is_type<std::int64_t>();
    }

    auto is_double() const noexcept
    {
        return is_type<double>();
    }

    auto is_bool() const noexcept
    {
        return is_type<bool>();
    }

    const auto &value() const noexcept
    {
        return value_;
    }

    const auto &array_value() const
    {
        aeon_assert(is_array(), "Value is not an array.");
        return std::get<array>(value());
    }

    const auto &object_value() const
    {
        aeon_assert(is_object(), "Value is not an object.");
        return std::get<object>(value());
    }

    const auto &uuid_value() const
    {
        aeon_assert(is_uuid(), "Value is not a uuid.");
        return std::get<utility::uuid>(value());
    }

    const auto &string_value() const
    {
        aeon_assert(is_string(), "Value is not a string.");
        return std::get<std::string>(value());
    }

    auto integer_value() const
    {
        aeon_assert(is_integer(), "Value is not an integer.");
        return std::get<std::int64_t>(value());
    }

    auto double_value() const
    {
        aeon_assert(is_double(), "Value is not a double.");
        return std::get<double>(value());
    }

    auto bool_value() const
    {
        aeon_assert(is_bool(), "Value is not a bool.");
        return std::get<bool>(value());
    }

private:
    std::variant<std::monostate, array, object, utility::uuid, std::string, std::int64_t, double, bool> value_;
};

} // namespace aeon::ptree
