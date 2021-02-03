// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <initializer_list>

namespace aeon::common
{

template <typename key_type_t>
class unordered_flatset final
{
public:
    using key_type = key_type_t;
    using value_type = key_type_t;
    using set_type = std::vector<key_type>;
    using iterator = typename set_type::iterator;

    unordered_flatset() = default;

    unordered_flatset(std::initializer_list<key_type> init)
        : set_{}
    {
        for (auto &&val : init)
        {
            insert(std::move(val));
        }
    }

    ~unordered_flatset() = default;

    unordered_flatset(const unordered_flatset &) = default;
    auto operator=(const unordered_flatset &) -> unordered_flatset & = default;
    unordered_flatset(unordered_flatset &&) noexcept = default;
    auto operator=(unordered_flatset &&) noexcept -> unordered_flatset & = default;

    auto insert(key_type key) -> iterator
    {
        auto itr = find(key);

        if (itr == std::end(set_))
            return set_.insert(std::end(set_), std::move(key));

        *itr = std::move(key);
        return itr;
    }

    auto emplace(key_type &&key) -> iterator
    {
        auto itr = find(key);

        if (itr == std::end(set_))
            return set_.insert(std::end(set_), std::move(key));

        *itr = std::move(key);
        return itr;
    }

    [[nodiscard]] auto contains(const key_type &key) const noexcept -> bool
    {
        return std::find_if(std::begin(set_), std::end(set_), [key](const auto &s) { return s == key; }) !=
               std::end(set_);
    }

    [[nodiscard]] auto find(const key_type &key) noexcept
    {
        return std::find_if(std::begin(set_), std::end(set_), [key](const auto &s) { return s == key; });
    }

    [[nodiscard]] auto find(const key_type &key) const noexcept
    {
        return std::find_if(std::begin(set_), std::end(set_), [key](const auto &s) { return s == key; });
    }

    [[nodiscard]] auto begin() noexcept
    {
        return std::begin(set_);
    }

    [[nodiscard]] auto end() noexcept
    {
        return std::end(set_);
    }

    [[nodiscard]] auto begin() const noexcept
    {
        return std::begin(set_);
    }

    [[nodiscard]] auto end() const noexcept
    {
        return std::end(set_);
    }

    auto erase(const key_type &key)
    {
        auto itr = find(key);

        if (itr != std::end(set_))
            return erase(itr);

        return itr;
    }

    void erase_if(std::function<bool(const key_type &)> pred)
    {
        for (auto obj = std::begin(set_); obj != std::end(set_);)
        {
            if (pred(*obj))
            {
                obj = set_.erase(obj);
            }
            else
            {
                ++obj;
            }
        }
    }

    auto erase(typename set_type::iterator itr)
    {
        return set_.erase(itr);
    }

    [[nodiscard]] auto empty() const
    {
        return std::empty(set_);
    }

    void clear()
    {
        set_.clear();
    }

    [[nodiscard]] auto size() const noexcept
    {
        return std::size(set_);
    }

    void reserve(const std::size_t size)
    {
        set_.reserve(size);
    }

    auto operator==(const unordered_flatset<key_type> &other) const noexcept -> bool
    {
        if (size() != std::size(other))
            return false;

        for (const auto &val : set_)
        {
            const auto result = other.find(val);

            if (result == std::end(other))
                return false;

            if (*result != val)
                return false;
        }

        return true;
    }

    auto operator!=(const unordered_flatset<key_type> &other) const noexcept -> bool
    {
        return !(*this == other);
    }

private:
    set_type set_;
};

} // namespace aeon::common
