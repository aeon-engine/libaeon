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

class itestplugin1
{
public:
    virtual ~itestplugin1() = default;

    virtual auto was_loaded() const noexcept -> bool = 0;

    virtual auto test_func1() const noexcept -> int = 0;
    virtual auto test_func2(const int var) const noexcept -> int = 0;

    virtual void set_unload_callback(const std::function<void()> callback) = 0;

    virtual auto test_dll_heap() const -> std::unique_ptr<test_data> = 0;
};
