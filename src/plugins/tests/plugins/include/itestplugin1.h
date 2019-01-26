// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/plugins/plugin.h>
#include <functional>
#include <string>
#include <vector>
#include <string_view>

struct test_data
{
    test_data(const std::string_view &a, const std::vector<int> &b)
        : a(a)
        , b(b)
    {
    }

    ~test_data()
    {
        if (deleted_callback)
            deleted_callback();
    }

    std::string a;
    std::vector<int> b;
    std::function<void()> deleted_callback;
};

class itestplugin1 : public aeon::plugins::plugin
{
public:
    virtual ~itestplugin1() = default;

    virtual auto was_loaded() const noexcept -> bool = 0;

    virtual auto test_func1() const noexcept -> int = 0;
    virtual auto test_func2(const int var) const noexcept -> int = 0;

    virtual void set_unload_callback(const std::function<void()> callback) = 0;

    virtual auto test_dll_heap() const -> std::unique_ptr<test_data> = 0;
};
