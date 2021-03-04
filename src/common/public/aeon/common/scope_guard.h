// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/preprocessor.h>
#include <aeon/common/assert.h>
#include <functional>
#include <exception>

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

    scope_guard_base(const scope_guard_base<function_type_t> &) noexcept = delete;
    auto operator=(const scope_guard_base<function_type_t> &) noexcept -> scope_guard_base<function_type_t> & = delete;

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

    scope_guard_impl(const scope_guard_impl &) = delete;
    auto operator=(const scope_guard_impl &) noexcept -> scope_guard_impl & = delete;

    scope_guard_impl(scope_guard_impl &&) = default;
    auto operator=(scope_guard_impl &&) noexcept -> scope_guard_impl & = default;

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
