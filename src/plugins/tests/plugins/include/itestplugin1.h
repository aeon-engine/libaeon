// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/plugins/plugin.h>
#include <aeon/common/string_view.h>
#include <functional>
#include <vector>

struct test_data
{
    test_data(aeon::common::string a, std::vector<int> b) noexcept
        : a{std::move(a)}
        , b{std::move(b)}
    {
    }

    ~test_data()
    {
        if (deleted_callback)
            deleted_callback();
    }

    test_data(test_data &&) noexcept = delete;
    auto operator=(test_data &&) noexcept -> test_data & = delete;

    test_data(const test_data &) = delete;
    auto operator=(const test_data &) -> test_data & = delete;

    aeon::common::string a;
    std::vector<int> b;
    std::function<void()> deleted_callback;
};

class itestplugin1 : public aeon::plugins::plugin
{
public:
    itestplugin1() = default;

    itestplugin1(itestplugin1 &&) noexcept = delete;
    auto operator=(itestplugin1 &&) noexcept -> itestplugin1 & = delete;

    itestplugin1(const itestplugin1 &) = delete;
    auto operator=(const itestplugin1 &) -> itestplugin1 & = delete;

    ~itestplugin1() override = default;

    [[nodiscard]] virtual auto was_loaded() const noexcept -> bool = 0;

    [[nodiscard]] virtual auto test_func1() const noexcept -> int = 0;
    [[nodiscard]] virtual auto test_func2(const int var) const noexcept -> int = 0;

    virtual void set_unload_callback(const std::function<void()> callback) = 0;

    [[nodiscard]] virtual auto test_dll_heap() const -> std::unique_ptr<test_data> = 0;
};
