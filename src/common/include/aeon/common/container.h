// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/common/literals.h>
#include <vector>
#include <memory>
#include <array>
#include <algorithm>

namespace aeon::common::container
{

template <class container_t>
class back_emplace_iterator
{
public:
    using container_type = container_t;

    explicit back_emplace_iterator(container_type &x)
        : container_{&x}
    {
    }

    template <typename T>
    back_emplace_iterator<container_type> &operator=(T &&args)
    {
        container_->emplace_back(std::forward<T>(args));
        return *this;
    }

    back_emplace_iterator &operator*()
    {
        return *this;
    }

    back_emplace_iterator &operator++()
    {
        return *this;
    }

    back_emplace_iterator &operator++(int)
    {
        return *this;
    }

private:
    container_type *container_;
};

template <typename T>
[[nodiscard]] inline auto back_emplacer(T &container)
{
    return back_emplace_iterator{container};
}

template <typename T>
[[nodiscard]] inline auto unique_ptr_to_raw_ptr(const std::vector<std::unique_ptr<T>> &c)
{
    std::vector<T *> c_ptr;
    c_ptr.reserve(std::size(c));

    for (auto &i : c)
    {
        c_ptr.push_back(i.get());
    }

    return c_ptr;
}

template <typename U, typename T>
[[nodiscard]] inline auto unique_ptr_to_raw_ptr(const std::vector<std::unique_ptr<T>> &c)
{
    std::vector<U *> c_ptr;
    c_ptr.reserve(std::size(c));

    for (auto &i : c)
    {
        c_ptr.push_back(i.get());
    }

    return c_ptr;
}

template <typename container_t, typename unary_predicate_t>
void erase_if(container_t &items, const unary_predicate_t &predicate)
{
    for (auto itr = std::begin(items); itr != std::end(items);)
    {
        if (predicate(*itr))
            itr = items.erase(itr);
        else
            ++itr;
    }
}

template <typename T, std::size_t N>
[[nodiscard]] inline constexpr auto make_array(T &&value)
{
    std::array<T, N> arr;
    arr.fill(std::forward<T>(value));
    return arr;
}

template <typename... T>
[[nodiscard]] inline constexpr auto make_array2(T &&... values)
    -> std::array<typename std::decay<typename std::common_type<T...>::type>::type, sizeof...(T)>
{
    return std::array<typename std::decay<typename std::common_type<T...>::type>::type, sizeof...(T)>{
        std::forward<T>(values)...};
}

template <typename input_itr_t, typename unary_predicate_t>
[[nodiscard]] inline auto count_until(input_itr_t first, input_itr_t last, unary_predicate_t p) noexcept
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
[[nodiscard]] inline auto find_in_map_by_value(const map_type_t &map, const value_type_t &value) noexcept
{
    return std::find_if(map.begin(), map.end(), [&value](const auto &pair) { return pair.second == value; });
}

/*!
 * Execute a predicate for every two adjacent items in a collection. Similar to adjacent_find, but does not
 * actually search for something. If the predicate returns false, the loop is aborted.
 * The signature of the predicate should be equivalent to bool(const type1 &left, const type2 &right);
 */
template <typename forward_itr_t, typename pred_t>
inline void adjacent_execute(forward_itr_t first, forward_itr_t last, pred_t p)
{
    if (first == last)
        return;

    auto next = first;
    ++next;

    for (; next != last; ++next, ++first)
    {
        if (!p(*first, *next))
            return;
    }
}

template <typename iterator_t, typename value_t>
inline auto contains(iterator_t first, iterator_t last, const value_t &value) -> bool
{
    if (first == last)
        return false;

    for (; first != last; ++first)
    {
        if (*first == value)
            return true;
    }

    return false;
}

} // namespace aeon::common::container
