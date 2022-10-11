// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/string_view.h>
#include <iostream>
#include <cassert>
#include <type_traits>
#include <exception>

namespace aeon::common
{

enum class expect_action
{
    none,
    assert,
    log,
    exception,
    terminate
};

template <expect_action action_t = expect_action::terminate, typename condition_t>
constexpr void expect([[maybe_unused]] condition_t c,
                      [[maybe_unused]] const char *error_message) noexcept(action_t != expect_action::exception)
{
    bool condition_result;
    if constexpr (std::is_same_v<std::decay_t<condition_t>, bool>)
        condition_result = c;
    else
        condition_result = c();

    if constexpr (action_t == expect_action::assert)
    {
        assert(condition_result);
    }
    else if constexpr (action_t == expect_action::log)
    {
        if (!condition_result)
            std::cerr << error_message << '\n';
    }
    else if constexpr (action_t == expect_action::exception)
    {
        if (!condition_result)
            throw std::runtime_error{error_message};
    }
    else if constexpr (action_t == expect_action::terminate)
    {
        if (!condition_result)
            std::terminate();
    }
}

template <expect_action action_t = expect_action::terminate, typename condition_t>
constexpr void expect([[maybe_unused]] condition_t c,
                      [[maybe_unused]] const string_view error_message) noexcept(action_t != expect_action::exception)
{
    expect<action_t>(std::forward<condition_t>(c), std::data(error_message));
}

template <expect_action action_t = expect_action::terminate, typename condition_t>
constexpr void expect([[maybe_unused]] condition_t c) noexcept(action_t != expect_action::exception)
{
    expect<action_t>(std::forward<condition_t>(c), "Expectation failed.");
}

} // namespace aeon::common
