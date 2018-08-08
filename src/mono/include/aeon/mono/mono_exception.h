/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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

    const auto &exception_typename() const noexcept
    {
        return exception_typename_;
    }

    const auto &message() const noexcept
    {
        return message_;
    }

    const auto &stacktrace() const noexcept
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

    static auto __get_exception_info(MonoException *ex) noexcept -> exception_info;
    static auto __get_string_property(const char *property_name, MonoClass *cls, MonoObject *obj) noexcept -> char *;

    std::string exception_typename_;
    std::string message_;
    std::string stacktrace_;
};

} // namespace aeon::mono
