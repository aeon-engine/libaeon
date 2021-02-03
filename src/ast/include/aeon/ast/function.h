// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/ast/entity.h>
#include <vector>
#include <string>

namespace aeon::ast
{

enum class exception_specification
{
    none,
    unknown,
    dynamic_none, // throw()
    dynamic,      // throw(a, b)
    msany,        // throw(...)
    basic_noexcept,
    computed_noexcept
};

class ast_function_parameter final
{
public:
    explicit ast_function_parameter(std::string name, std::string type) noexcept
        : name_{std::move(name)}
        , type_{std::move(type)}
    {
    }

    ~ast_function_parameter() = default;

    ast_function_parameter(const ast_function_parameter &) noexcept = delete;
    auto operator=(const ast_function_parameter &) noexcept -> ast_function_parameter & = delete;

    ast_function_parameter(ast_function_parameter &&) noexcept = default;
    auto operator=(ast_function_parameter &&) noexcept -> ast_function_parameter & = default;

    [[nodiscard]] const auto &name() const noexcept
    {
        return name_;
    }

    [[nodiscard]] const auto &type() const noexcept
    {
        return type_;
    }

private:
    std::string name_;
    std::string type_;
};

class ast_function : public ast_entity
{
public:
    explicit ast_function(std::string name, std::string return_type, const ast::linkage_kind linkage_kind,
                          const ast::exception_specification exception_specification,
                          ast_source_location location) noexcept
        : ast_function{ast_entity_type::function_t, std::move(name),    std::move(return_type), linkage_kind,
                       exception_specification,     std::move(location)}
    {
    }

    virtual ~ast_function() = default;

    ast_function(const ast_function &) noexcept = delete;
    auto operator=(const ast_function &) noexcept -> ast_function & = delete;

    ast_function(ast_function &&) noexcept = default;
    auto operator=(ast_function &&) noexcept -> ast_function & = default;

    void add_parameter(std::string name, std::string type)
    {
        add_parameter(ast_function_parameter{std::move(name), std::move(type)});
    }

    void add_parameter(ast_function_parameter parameter)
    {
        parameters_.push_back(std::move(parameter));
    }

    [[nodiscard]] const auto &parameters() const noexcept
    {
        return parameters_;
    }

    [[nodiscard]] auto parameter_count() const noexcept
    {
        return std::size(parameters_);
    }

    [[nodiscard]] auto has_parameters() const noexcept
    {
        return !std::empty(parameters_);
    }

    [[nodiscard]] const auto &return_type() const noexcept
    {
        return return_type_;
    }

    [[nodiscard]] auto exception_specification() const noexcept
    {
        return exception_specification_;
    }

protected:
    explicit ast_function(const ast_entity_type type, std::string name, const ast::linkage_kind linkage_kind,
                          const ast::exception_specification exception_specification,
                          ast_source_location location) noexcept
        : ast_function{type, std::move(name), {}, linkage_kind, exception_specification, std::move(location)}
    {
    }

    explicit ast_function(const ast_entity_type type, std::string name, std::string return_type,
                          const ast::linkage_kind linkage_kind,
                          const ast::exception_specification exception_specification,
                          ast_source_location location) noexcept
        : ast_entity{type, std::move(name), linkage_kind, std::move(location)}
        , parameters_{}
        , return_type_{std::move(return_type)}
        , exception_specification_{exception_specification}
    {
    }

private:
    std::vector<ast_function_parameter> parameters_;
    std::string return_type_;
    ast::exception_specification exception_specification_;
};

} // namespace aeon::ast
