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

#include <aeon/common/anonymous_variable.h>
#include <aeon/common/assert.h>
#include <functional>

namespace aeon::common
{

namespace detail
{

template <typename function_type_t>
class scope_guard_base
{
public:
    void dismiss() noexcept
    {
        dismissed_ = true;
    }

    template <typename T>
    static void execute(T &func) noexcept
    {
        try
        {
            func();
        }
        catch (...)
        {
            aeon_assert_fail("A scope guard callback should not throw.");
            std::terminate();
        }
    }

    explicit scope_guard_base(function_type_t &&func) noexcept
        : dismissed_{false}
        , function_{std::forward<function_type_t>(func)}
    {
    }

    scope_guard_base(scope_guard_base &&other) noexcept
        : function_{std::move(other.function_)}
    {
        dismissed_ = other.dismissed_;
        other.dismissed_ = true;
    }

    ~scope_guard_base() noexcept
    {
        if (dismissed_)
            return;

        execute(function_);
    }

private:
    bool dismissed_;
    function_type_t function_;
};

template <typename function_type_t, bool execute_on_exception>
class scope_guard_impl
{
public:
    explicit scope_guard_impl(const function_type_t &fn)
        : function_(fn)
    {
    }

    explicit scope_guard_impl(function_type_t &&fn)
        : function_(std::move(fn))
    {
    }

    scope_guard_impl(const scope_guard_impl &other) = delete;
    scope_guard_impl(scope_guard_impl &&other) = default;

    ~scope_guard_impl() noexcept(execute_on_exception)
    {
        if (execute_on_exception == (exception_count_ < std::uncaught_exceptions()))
        {
            if (execute_on_exception)
            {
                scope_guard_base<function_type_t>::execute(function_);
            }
            else
            {
                function_();
            }
        }
    }

private:
    function_type_t function_;
    int exception_count_{std::uncaught_exceptions()};
};

class scope_guard_on_fail
{
};

template <typename function_type_t>
scope_guard_impl<typename std::decay<function_type_t>::type, true> operator+(scope_guard_on_fail,
                                                                             function_type_t &&func)
{
    return scope_guard_impl<typename std::decay<function_type_t>::type, true>(std::forward<function_type_t>(func));
}

} // namespace detail

} // namespace aeon::common

#define aeon_scope_fail                                                                                                \
    auto aeon_anonymous_variable(__aeon_scope_fail) = ::aeon::common::detail::scope_guard_on_fail() + [&]() noexcept
