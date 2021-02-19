// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <vector>
#include <string>

namespace aeon::gl::generator
{

struct opengl_enum_value final
{
    std::string name;
    std::string value;
};

struct opengl_function_argument final
{
    std::string name;
    std::string type;
};

class opengl_function final
{
public:
    explicit opengl_function(std::string name, std::string return_type)
        : name_{std::move(name)}
        , return_type_{std::move(return_type)}
    {
    }

    ~opengl_function() = default;

    opengl_function(const opengl_function &) = delete;
    auto operator=(const opengl_function &) -> opengl_function & = delete;

    opengl_function(opengl_function &&) noexcept = default;
    auto operator=(opengl_function &&) noexcept -> opengl_function & = default;

    [[nodiscard]] const auto &name() const noexcept
    {
        return name_;
    }

    [[nodiscard]] const auto &return_type() const noexcept
    {
        return return_type_;
    }

    void add_argument(std::string name, std::string type)
    {
        arguments_.emplace_back(std::move(name), std::move(type));
    }

    [[nodiscard]] const auto &arguments() const noexcept
    {
        return arguments_;
    }

private:
    std::string name_;
    std::string return_type_;
    std::vector<opengl_function_argument> arguments_;
};

class opengl_definition final
{
public:
    explicit opengl_definition(std::string definition_name)
        : definition_name_{std::move(definition_name)}
    {
    }

    ~opengl_definition() = default;

    opengl_definition(const opengl_definition &) = delete;
    auto operator=(const opengl_definition &) -> opengl_definition & = delete;

    opengl_definition(opengl_definition &&) noexcept = default;
    auto operator=(opengl_definition &&) noexcept -> opengl_definition & = default;

    [[nodiscard]] const auto &definition_name() const noexcept
    {
        return definition_name_;
    }

    void add_additional_code(std::string header)
    {
        additional_code_.push_back(std::move(header));
    }

    [[nodiscard]] const auto &additional_code() const noexcept
    {
        return additional_code_;
    }

    void add_enum_value(std::string name, std::string value)
    {
        enum_values_.emplace_back(std::move(name), std::move(value));
    }

    [[nodiscard]] const auto &enum_values() const noexcept
    {
        return enum_values_;
    }

    void add_function(opengl_function function)
    {
        functions_.push_back(std::move(function));
    }

    [[nodiscard]] const auto &functions() const noexcept
    {
        return functions_;
    }

private:
    std::string definition_name_;

    /*!
     * The XML contains "types", but these essentially contain entire lines of code and even includes and ifdefs.
     * It would have been nice if it only cleanly contained types and their names, but it's simply a mess.
     * For now they are simply parsed as additional lines of code that are added to the generated header directly.
     */
    std::vector<std::string> additional_code_;
    std::vector<opengl_enum_value> enum_values_;
    std::vector<opengl_function> functions_;
};

} // namespace aeon::gl::generator
