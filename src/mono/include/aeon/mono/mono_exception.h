/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <stdexcept>
#include <string>

namespace aeon
{
namespace mono
{

class mono_exception : public std::runtime_error
{
public:
    mono_exception()
        : std::runtime_error("Mono Exception.")
    {
    }

    explicit mono_exception(std::string what)
        : std::runtime_error(what.c_str())
    {
    }
};

class mono_thunk_exception : public mono_exception
{
public:
    explicit mono_thunk_exception(const std::string &exception_typename, const std::string &message,
                                  const std::string &stacktrace)
        : mono_exception(exception_typename + "(" + message + ")")
        , exception_typename_(exception_typename)
        , message_(message)
        , stacktrace_(stacktrace)
    {
    }

    auto exception_typename() const
    {
        return exception_typename_;
    }

    auto message() const
    {
        return message_;
    }

    auto stacktrace() const
    {
        return stacktrace_;
    }

private:
    std::string exception_typename_;
    std::string message_;
    std::string stacktrace_;
};

} // namespace mono
} // namespace aeon
