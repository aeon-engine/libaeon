// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/ast/function.h>
#include <aeon/ast/access_specifier.h>
#include <aeon/common/flags.h>
#include <cstdint>

namespace aeon::ast
{

enum class method_flag : std::uint32_t
{
    is_const = 0x01,
    is_defaulted = 0x02,
    is_pure_virtual = 0x04,
    is_static = 0x08,
    is_virtual = 0x10
};

aeon_declare_flag_operators(method_flag);

class ast_method final : public ast_function
{
public:
    explicit ast_method(std::string name, std::string return_type, const access_specifier access,
                        common::flags<method_flag> flags, const ast::linkage_kind linkage_kind,
                        const ast::exception_specification exception_specification,
                        ast_source_location location) noexcept
        : ast_function{ast_entity_type::method_t, std::move(name),    std::move(return_type), linkage_kind,
                       exception_specification,   std::move(location)}
        , access_{access}
        , flags_{flags}
    {
    }

    virtual ~ast_method() = default;

    ast_method(const ast_method &) noexcept = delete;
    auto operator=(const ast_method &) noexcept -> ast_method & = delete;

    ast_method(ast_method &&) noexcept = default;
    auto operator=(ast_method &&) noexcept -> ast_method & = default;

    [[nodiscard]] auto access() const noexcept -> access_specifier
    {
        return access_;
    }

    [[nodiscard]] auto flags() const noexcept -> common::flags<method_flag>
    {
        return flags_;
    }

    [[nodiscard]] auto is_const() const noexcept -> bool
    {
        return flags_.is_set(method_flag::is_const);
    }

    [[nodiscard]] auto is_defaulted() const noexcept -> bool
    {
        return flags_.is_set(method_flag::is_defaulted);
    }

    [[nodiscard]] auto is_pure_virtual() const noexcept -> bool
    {
        return flags_.is_set(method_flag::is_pure_virtual);
    }

    [[nodiscard]] auto is_static() const noexcept -> bool
    {
        return flags_.is_set(method_flag::is_static);
    }

    [[nodiscard]] auto is_virtual() const noexcept -> bool
    {
        return flags_.is_set(method_flag::is_virtual);
    }

private:
    access_specifier access_;
    common::flags<method_flag> flags_;
};

} // namespace aeon::ast
