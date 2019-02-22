// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/utility/linear_map.h>
#include <aeon/utility/uuid.h>
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
    using variant_type =
        std::variant<std::monostate, array, object, utility::uuid, std::string, std::int64_t, double, bool>;

    property_tree();
    property_tree(std::nullptr_t);
    property_tree(const int value);
    property_tree(const std::int64_t value);
    property_tree(const double value);
    property_tree(const array &value);
    property_tree(array &&value);
    property_tree(const object &value);
    property_tree(object &&value);
    property_tree(const bool value);
    property_tree(const char *const value);
    property_tree(const std::string &value);
    property_tree(std::string &&value);
    property_tree(const utility::uuid &uuid);
    property_tree(utility::uuid &&uuid);

    virtual ~property_tree() noexcept = default;

    property_tree(const property_tree &) = default;
    auto operator=(const property_tree &) -> property_tree & = default;

    property_tree(property_tree &&) noexcept = default;
    auto operator=(property_tree &&) noexcept -> property_tree & = default;

    template <typename T>
    auto is_type() const noexcept;

    auto is_null() const noexcept;
    auto is_array() const noexcept;
    auto is_object() const noexcept;
    auto is_string() const noexcept;
    auto is_uuid() const noexcept;
    auto is_integer() const noexcept;
    auto is_double() const noexcept;
    auto is_bool() const noexcept;

    auto value() noexcept -> variant_type &;
    auto value() const noexcept -> const variant_type &;

    auto array_value() -> array &;
    auto array_value() const -> const array &;

    auto object_value() -> object &;
    auto object_value() const -> const object &;

    auto uuid_value() const -> const utility::uuid &;
    auto string_value() const -> const std::string &;
    auto integer_value() const -> std::int64_t;
    auto double_value() const -> double;
    auto bool_value() const -> bool;

    auto at(const object::key_type &key) -> object::value_type &;
    auto at(const object::key_type &key) const -> const object::value_type &;

    auto operator=(const std::nullptr_t) -> property_tree &;
    auto operator=(const int value) -> property_tree &;
    auto operator=(const std::int64_t value) -> property_tree &;
    auto operator=(const double value) -> property_tree &;
    auto operator=(const array &value) -> property_tree &;
    auto operator=(array &&value) -> property_tree &;
    auto operator=(const object &value) -> property_tree &;
    auto operator=(object &&value) -> property_tree &;
    auto operator=(const char *const value) -> property_tree &;
    auto operator=(const std::string &value) -> property_tree &;
    auto operator=(std::string &&value) -> property_tree &;
    auto operator=(const utility::uuid &value) -> property_tree &;
    auto operator=(utility::uuid &&value) -> property_tree &;

    auto operator==(const property_tree &other) const noexcept -> bool;
    auto operator!=(const property_tree &other) const noexcept -> bool;

private:
    variant_type value_;
};

auto operator==(const property_tree &lhs, const std::nullptr_t) noexcept -> bool;
auto operator!=(const property_tree &lhs, const std::nullptr_t) noexcept -> bool;
auto operator==(const std::nullptr_t, const property_tree &rhs) noexcept -> bool;
auto operator!=(const std::nullptr_t, const property_tree &rhs) noexcept -> bool;

auto operator==(const property_tree &lhs, const int rhs) -> bool;
auto operator!=(const property_tree &lhs, const int rhs) -> bool;
auto operator==(const int lhs, const property_tree &rhs) -> bool;
auto operator!=(const int lhs, const property_tree &rhs) -> bool;

auto operator==(const property_tree &lhs, const std::int64_t rhs) -> bool;
auto operator!=(const property_tree &lhs, const std::int64_t rhs) -> bool;
auto operator==(const std::int64_t lhs, const property_tree &rhs) -> bool;
auto operator!=(const std::int64_t lhs, const property_tree &rhs) -> bool;

auto operator==(const property_tree &lhs, const double rhs) -> bool;
auto operator!=(const property_tree &lhs, const double rhs) -> bool;
auto operator==(const double lhs, const property_tree &rhs) -> bool;
auto operator!=(const double lhs, const property_tree &rhs) -> bool;

auto operator==(const property_tree &lhs, const array &rhs) -> bool;
auto operator!=(const property_tree &lhs, const array &rhs) -> bool;
auto operator==(const array &lhs, const property_tree &rhs) -> bool;
auto operator!=(const array &lhs, const property_tree &rhs) -> bool;

auto operator==(const property_tree &lhs, const object &rhs) -> bool;
auto operator!=(const property_tree &lhs, const object &rhs) -> bool;
auto operator==(const object &lhs, const property_tree &rhs) -> bool;
auto operator!=(const object &lhs, const property_tree &rhs) -> bool;

auto operator==(const property_tree &lhs, const char *const rhs) -> bool;
auto operator!=(const property_tree &lhs, const char *const rhs) -> bool;
auto operator==(const char *const lhs, const property_tree &rhs) -> bool;
auto operator!=(const char *const lhs, const property_tree &rhs) -> bool;

auto operator==(const property_tree &lhs, const std::string &rhs) -> bool;
auto operator!=(const property_tree &lhs, const std::string &rhs) -> bool;
auto operator==(const std::string &lhs, const property_tree &rhs) -> bool;
auto operator!=(const std::string &lhs, const property_tree &rhs) -> bool;

auto operator==(const property_tree &lhs, const utility::uuid &rhs) -> bool;
auto operator!=(const property_tree &lhs, const utility::uuid &rhs) -> bool;
auto operator==(const utility::uuid &lhs, const property_tree &rhs) -> bool;
auto operator!=(const utility::uuid &lhs, const property_tree &rhs) -> bool;

} // namespace aeon::ptree

#include <aeon/ptree/impl/ptree_impl.h>
