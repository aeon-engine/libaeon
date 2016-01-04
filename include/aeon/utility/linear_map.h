/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace utility
{

template <typename key_type, typename value_type>
class linear_map
{
public:
    using pair_type = std::pair<key_type, value_type>;
    using map_type = std::vector<pair_type>;

    linear_map()
    {
    }

    ~linear_map()
    {
    }

    typename map_type::iterator insert(const key_type &key, const value_type &value)
    {
        return insert(std::make_pair(key, value));
    }

    typename map_type::iterator insert(pair_type pair)
    {
        auto itr = __find_key(pair.first);

        if (itr == map_.end())
            return map_.insert(map_.end(), pair);

        itr->second = pair.second;
        return itr;
    }

    typename map_type::iterator insert_ex(const key_type &key, const value_type &value)
    {
        return insert_ex(std::make_pair(key, value));
    }

    typename map_type::iterator insert_ex(pair_type pair)
    {
        auto itr = __find_key(pair.first);

        if (itr == map_.end())
            return map_.insert(map_.end(), pair);

        return map_.end();
    }

    value_type &at(const key_type &key)
    {
        auto itr = __find_key(key);
        if (itr == map_.end())
            throw std::out_of_range("aeon linear_map key out of range.");

        return itr->second;
    }

    value_type &operator[](const key_type &key)
    {
        auto itr = __find_key(key);

        if (itr == map_.end())
            itr = insert(key, value_type());

        return itr->second;
    }

    typename map_type::iterator find(const key_type &key)
    {
        return __find_key(key);
    }

    typename map_type::iterator begin() noexcept
    {
        return map_.begin();
    }

    typename map_type::iterator end() noexcept
    {
        return map_.end();
    }

    typename map_type::const_iterator begin() const noexcept
    {
        return map_.cbegin();
    }

    typename map_type::const_iterator end() const noexcept
    {
        return map_.cend();
    }

    typename map_type::iterator erase(const key_type &key)
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

    typename map_type::iterator erase(typename map_type::iterator itr)
    {
        return map_.erase(itr);
    }

    bool empty() const
    {
        return map_.empty();
    }

    void clear()
    {
        map_.clear();
    }

    std::size_t size() const noexcept
    {
        return map_.size();
    }

private:
    typename map_type::iterator __find_key(const key_type &key)
    {
        typename map_type::iterator itr = std::find_if(map_.begin(), map_.end(), [key](const pair_type &s)
                                                       {
                                                           return s.first == key;
                                                       });

        return itr;
    }

    map_type map_;
};

} // namespace utility
} // namespace aeon
