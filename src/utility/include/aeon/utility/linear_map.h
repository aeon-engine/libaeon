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
#include <vector>

namespace aeon::utility
{

template <typename key_type, typename value_type>
class linear_map
{
public:
    using pair_type = std::pair<key_type, value_type>;
    using map_type = std::vector<pair_type>;

    linear_map() = default;
    ~linear_map() = default;

    linear_map(const linear_map &) = default;
    auto operator=(const linear_map &) -> linear_map & = default;
    linear_map(linear_map &&) noexcept = default;
    auto operator=(linear_map &&) noexcept -> linear_map & = default;

    auto insert(const key_type &key, const value_type &value)
    {
        return insert(std::make_pair(key, value));
    }

    auto insert(pair_type pair)
    {
        auto itr = __find_key(pair.first);

        if (itr == map_.end())
            return map_.insert(map_.end(), pair);

        itr->second = pair.second;
        return itr;
    }

    auto insert_ex(const key_type &key, const value_type &value)
    {
        return insert_ex(std::make_pair(key, value));
    }

    auto insert_ex(pair_type pair)
    {
        auto itr = __find_key(pair.first);

        if (itr == map_.end())
            return map_.insert(map_.end(), pair);

        return map_.end();
    }

    auto &at(const key_type &key)
    {
        auto itr = __find_key(key);
        if (itr == map_.end())
            throw std::out_of_range("aeon linear_map key out of range.");

        return itr->second;
    }

    auto &operator[](const key_type &key)
    {
        auto itr = __find_key(key);

        if (itr == map_.end())
            itr = insert(key, value_type());

        return itr->second;
    }

    auto find(const key_type &key)
    {
        return __find_key(key);
    }

    auto begin() noexcept
    {
        return map_.begin();
    }

    auto end() noexcept
    {
        return map_.end();
    }

    auto begin() const noexcept
    {
        return map_.cbegin();
    }

    auto end() const noexcept
    {
        return map_.cend();
    }

    auto erase(const key_type &key)
    {
        auto itr = __find_key(key);

        if (itr != map_.end())
            return erase(itr);

        return itr;
    }

    void erase_if(std::function<bool(const pair_type &)> pred)
    {
        for (auto obj = map_.begin(); obj != map_.end();)
        {
            if (pred(*obj))
            {
                obj = map_.erase(obj);
            }
            else
            {
                ++obj;
            }
        }
    }

    auto erase(typename map_type::iterator itr)
    {
        return map_.erase(itr);
    }

    auto empty() const
    {
        return map_.empty();
    }

    void clear()
    {
        map_.clear();
    }

    auto size() const noexcept
    {
        return map_.size();
    }

private:
    auto __find_key(const key_type &key)
    {
        return std::find_if(map_.begin(), map_.end(), [key](const pair_type &s) { return s.first == key; });
    }

    map_type map_;
};

} // namespace aeon::utility
