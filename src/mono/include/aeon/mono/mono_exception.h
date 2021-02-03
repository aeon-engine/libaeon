// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/compilers.h>

AEON_IGNORE_VS_WARNING_PUSH(4201)
#include <mono/metadata/reflection.h>
AEON_IGNORE_VS_WARNING_POP()

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
