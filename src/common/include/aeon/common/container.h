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

#include <aeon/common/literals.h>
#include <vector>
#include <memory>
#include <array>
#include <algorithm>

namespace aeon::common::container
{

template <typename T>
auto unique_ptr_to_raw_ptr(const std::vector<std::unique_ptr<T>> &c)
{
    std::vector<T *> c_ptr;
    c_ptr.reserve(c.size());

    for (auto &i : c)
    {
        c_ptr.push_back(i.get());
    }

    return c_ptr;
}

template <typename U, typename T>
auto unique_ptr_to_raw_ptr(const std::vector<std::unique_ptr<T>> &c)
{
    std::vector<U *> c_ptr;
    c_ptr.reserve(c.size());

    for (auto &i : c)
    {
        c_ptr.push_back(i.get());
    }

    return c_ptr;
}

template <typename container_t, typename unary_predicate_t>
void erase_if(container_t &items, const unary_predicate_t &predicate)
{
    for (auto itr = items.begin(); itr != items.end();)
    {
        if (predicate(*itr))
            itr = items.erase(itr);
        else
            ++itr;
    }
}

template <typename T, std::size_t N>
constexpr auto make_array(T &&value)
{
    std::array<T, N> arr;
    arr.fill(std::forward<T>(value));
    return arr;
}

template <typename... T>
constexpr auto make_array2(T &&... values)
    -> std::array<typename std::decay<typename std::common_type<T...>::type>::type, sizeof...(T)>
{
    return std::array<typename std::decay<typename std::common_type<T...>::type>::type, sizeof...(T)>{
        std::forward<T>(values)...};
}

template <typename input_itr_t, typename unary_predicate_t>
auto count_until(input_itr_t first, input_itr_t last, unary_predicate_t p) noexcept
{
    auto count = 0_size_t;

    for (; first != last; ++first, ++count)
    {
        if (p(*first))
            return count;
    }

    return count;
}

template <typename map_type_t, typename value_type_t>
auto find_in_map_by_value(const map_type_t &map, const value_type_t &value) noexcept
{
    return std::find_if(map.begin(), map.end(), [&value](const auto &pair) { return pair.second == value; });
}

} // namespace aeon::common::container
