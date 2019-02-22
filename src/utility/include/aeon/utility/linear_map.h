// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <initializer_list>

namespace aeon::utility
{

template <typename key_type, typename value_type>
class linear_map final
{
public:
    using pair_type = std::pair<key_type, value_type>;
    using map_type = std::vector<pair_type>;
    using iterator = typename map_type::iterator;

    linear_map() = default;

    linear_map(std::initializer_list<pair_type> init)
        : map_{}
    {
        for (auto &&val : init)
        {
            insert(std::move(val));
        }
    }

    ~linear_map() = default;

    linear_map(const linear_map &) = default;
    auto operator=(const linear_map &) -> linear_map & = default;
    linear_map(linear_map &&) noexcept = default;
    auto operator=(linear_map &&) noexcept -> linear_map & = default;

    auto insert(key_type key, value_type value) -> iterator
    {
        return insert({key, value});
    }

    auto emplace(key_type &&key, value_type &&value) -> iterator
    {
        return emplace({std::move(key), std::move(value)});
    }

    auto insert(pair_type pair) -> iterator
    {
        auto itr = find(pair.first);

        if (itr == std::end(map_))
            return map_.insert(std::end(map_), std::move(pair));

        itr->second = std::move(pair.second);
        return itr;
    }

    auto emplace(pair_type &&pair) -> iterator
    {
        auto itr = find(pair.first);

        if (itr == std::end(map_))
            return map_.insert(std::end(map_), std::move(pair));

        itr->second = std::move(pair.second);
        return itr;
    }

    void push_back(const key_type &key, const value_type &value)
    {
        push_back({key, value});
    }

    void push_back(const pair_type &pair)
    {
        map_.push_back(std::move(pair));
    }

    auto &at(const key_type &key)
    {
        auto itr = find(key);
        if (itr == std::end(map_))
            throw std::out_of_range{"aeon linear_map key out of range."};

        return itr->second;
    }

    const auto &at(const key_type &key) const
    {
        auto itr = find(key);
        if (itr == std::end(map_))
            throw std::out_of_range{"aeon linear_map key out of range."};

        return itr->second;
    }

    auto &operator[](const key_type &key)
    {
        auto itr = find(key);

        if (itr == std::end(map_))
            itr = insert(key, value_type{});

        return itr->second;
    }

    auto &operator[](key_type &&key)
    {
        auto itr = find(key);

        if (itr == std::end(map_))
            itr = emplace(std::move(key), value_type{});

        return itr->second;
    }

    auto find(const key_type &key) noexcept
    {
        return std::find_if(std::begin(map_), std::end(map_), [key](const auto &s) { return s.first == key; });
    }

    auto find(const key_type &key) const noexcept
    {
        return std::find_if(std::begin(map_), std::end(map_), [key](const auto &s) { return s.first == key; });
    }

    auto begin() noexcept
    {
        return std::begin(map_);
    }

    auto end() noexcept
    {
        return std::end(map_);
    }

    auto begin() const noexcept
    {
        return std::begin(map_);
    }

    auto end() const noexcept
    {
        return std::end(map_);
    }

    auto erase(const key_type &key)
    {
        auto itr = find(key);

        if (itr != std::end(map_))
            return erase(itr);

        return itr;
    }

    void erase_if(std::function<bool(const pair_type &)> pred)
    {
        for (auto obj = std::begin(map_); obj != std::end(map_);)
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
        return std::empty(map_);
    }

    void clear()
    {
        map_.clear();
    }

    auto size() const noexcept
    {
        return std::size(map_);
    }

    void reserve(const std::size_t size)
    {
        map_.reserve(size);
    }

    auto operator==(const linear_map<key_type, value_type> &other) const noexcept -> bool
    {
        if (size() != std::size(other))
            return false;

        for (const auto &[key, val] : map_)
        {
            const auto result = other.find(key);

            if (result == std::end(other))
                return false;

            if (result->second != val)
                return false;
        }

        return true;
    }

    auto operator!=(const linear_map<key_type, value_type> &other) const noexcept -> bool
    {
        return !(*this == other);
    }

private:
    map_type map_;
};

} // namespace aeon::utility
