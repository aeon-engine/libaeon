// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <mono/metadata/reflection.h>
#include <stdexcept>
#include <string>

namespace aeon::mono
{

class mono_exception : public std::runtime_error
{
public:
    mono_exception();
    explicit mono_exception(const std::string &what);
};

class mono_thunk_exception : public mono_exception
{
public:
    explicit mono_thunk_exception(MonoException *ex);

    [[nodiscard]] const auto &exception_typename() const noexcept
    {
        return exception_typename_;
    }

    [[nodiscard]] const auto &message() const noexcept
    {
        return message_;
    }

    [[nodiscard]] const auto &stacktrace() const noexcept
    {
        return stacktrace_;
    }

private:
    struct exception_info
    {
        std::string exception_typename;
        std::string message;
        std::string stacktrace;
    };

    explicit mono_thunk_exception(const exception_info &info);

    [[nodiscard]] static auto __get_exception_info(MonoException *ex) noexcept -> exception_info;
    [[nodiscard]] static auto __get_string_property(const char *property_name, MonoClass *cls, MonoObject *obj) noexcept
        -> char *;

    std::string exception_typename_;
    std::string message_;
    std::string stacktrace_;
};

} // namespace aeon::mono
