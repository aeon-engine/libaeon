// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <type_traits>
#include <iterator>
#include <vector>

namespace aeon::common
{

/*!
 * Since std::vector does not have a virtual destructor, it can not be inherited from.
 * This class provides an interface very similar to that of vector but contains a virtual
 * destructor to make sure data gets deleted properly.
 */
template <typename T>
class collection
{
public:
    using value_type = typename std::vector<T>::value_type;
    using allocator_type = typename std::vector<T>::allocator_type;
    using size_type = typename std::vector<T>::size_type;
    using difference_type = typename std::vector<T>::difference_type;
    using reference = typename std::vector<T>::reference;
    using const_reference = typename std::vector<T>::const_reference;
    using pointer = typename std::vector<T>::pointer;
    using const_pointer = typename std::vector<T>::const_pointer;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using reverse_iterator = typename std::vector<T>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

    explicit collection() noexcept;

    explicit collection(std::vector<T> vec) noexcept;

    virtual ~collection() = default;

    collection(const collection &) = default;
    auto operator=(const collection &) -> collection & = default;

    collection(collection &&) noexcept = default;
    auto operator=(collection &&) noexcept -> collection & = default;

    [[nodiscard]] auto data() noexcept -> pointer;

    [[nodiscard]] auto data() const noexcept -> const_pointer;

    [[nodiscard]] auto size() const noexcept -> size_type;

    [[nodiscard]] auto max_size() const noexcept -> size_type;

    [[nodiscard]] auto capacity() const noexcept -> size_type;

    [[nodiscard]] auto empty() const noexcept -> bool;

    void reserve(const size_type new_cap);

    void shrink_to_fit();

    void clear() noexcept;

    [[nodiscard]] auto operator[](const size_type i) -> reference;

    [[nodiscard]] auto operator[](const size_type i) const -> const_reference;

    [[nodiscard]] auto at(const size_type i) -> reference;

    [[nodiscard]] auto at(const size_type i) const -> const_reference;

    [[nodiscard]] auto begin() noexcept -> iterator;

    [[nodiscard]] auto begin() const noexcept -> const_iterator;

    [[nodiscard]] auto cbegin() const noexcept -> const_iterator;

    [[nodiscard]] auto end() noexcept -> iterator;

    [[nodiscard]] auto end() const noexcept -> const_iterator;

    [[nodiscard]] auto cend() const noexcept -> const_iterator;

    [[nodiscard]] auto rbegin() noexcept -> iterator;

    [[nodiscard]] auto rbegin() const noexcept -> const_iterator;

    [[nodiscard]] auto crbegin() const noexcept -> const_iterator;

    [[nodiscard]] auto rend() noexcept -> iterator;

    [[nodiscard]] auto rend() const noexcept -> const_iterator;

    [[nodiscard]] auto crend() const noexcept -> const_iterator;

    [[nodiscard]] auto front() noexcept -> reference;

    [[nodiscard]] auto front() const noexcept -> const_reference;

    [[nodiscard]] auto back() noexcept -> reference;

    [[nodiscard]] auto back() const noexcept -> const_reference;

    auto insert(const_iterator pos, const T &value) -> iterator;

    auto insert(const_iterator pos, T &&value) -> iterator;

    auto insert(const_iterator pos, size_type count, const T &value) -> iterator;

    template <class input_iterator_t>
    auto insert(const_iterator pos, input_iterator_t first, input_iterator_t last) -> iterator;

    auto insert(const_iterator pos, std::initializer_list<T> ilist) -> iterator;

    template <class... args_t>
    auto emplace(const_iterator pos, args_t &&...args) -> iterator;

    auto erase(const_iterator pos) -> iterator;

    auto erase(const_iterator first, const_iterator last) -> iterator;

    void push_back(const T &value);

    void push_back(T &&value);

    template <class... args_t>
    auto emplace_back(args_t &&...args) -> reference;

    void pop_back();

    void resize(const size_type count);

    void resize(const size_type count, const value_type &value);

    void
        swap(collection<T> &other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_swap::value ||
                                            std::allocator_traits<allocator_type>::is_always_equal::value);

protected:
    std::vector<T> data_;
};

template <typename T>
inline collection<T>::collection() noexcept
    : data_{}
{
}

template <typename T>
inline collection<T>::collection(std::vector<T> vec) noexcept
    : data_{std::move(vec)}
{
}

template <typename T>
inline auto collection<T>::data() noexcept -> pointer
{
    return std::data(data_);
}

template <typename T>
inline auto collection<T>::data() const noexcept -> const_pointer
{
    return std::data(data_);
}

template <typename T>
inline auto collection<T>::size() const noexcept -> size_type
{
    return std::size(data_);
}

template <typename T>
inline auto collection<T>::max_size() const noexcept -> size_type
{
    return data_.max_size();
}

template <typename T>
inline auto collection<T>::capacity() const noexcept -> size_type
{
    return data_.capacity();
}

template <typename T>
inline auto collection<T>::empty() const noexcept -> bool
{
    return std::empty(data_);
}

template <typename T>
inline void collection<T>::reserve(const size_type new_cap)
{
    data_.reserve(new_cap);
}

template <typename T>
inline void collection<T>::shrink_to_fit()
{
    data_.shrink_to_fit();
}

template <typename T>
inline void collection<T>::clear() noexcept
{
    data_.clear();
}

template <typename T>
inline auto collection<T>::operator[](const size_type i) -> reference
{
    return data_[i];
}

template <typename T>
inline auto collection<T>::operator[](const size_type i) const -> const_reference
{
    return data_[i];
}

template <typename T>
inline auto collection<T>::at(const size_type i) -> reference
{
    return data_.at(i);
}

template <typename T>
inline auto collection<T>::at(const size_type i) const -> const_reference
{
    return data_.at(i);
}

template <typename T>
inline auto collection<T>::begin() noexcept -> iterator
{
    return std::begin(data_);
}

template <typename T>
inline auto collection<T>::begin() const noexcept -> const_iterator
{
    return std::begin(data_);
}

template <typename T>
inline auto collection<T>::cbegin() const noexcept -> const_iterator
{
    return std::cbegin(data_);
}

template <typename T>
inline auto collection<T>::end() noexcept -> iterator
{
    return std::end(data_);
}

template <typename T>
inline auto collection<T>::end() const noexcept -> const_iterator
{
    return std::end(data_);
}

template <typename T>
inline auto collection<T>::cend() const noexcept -> const_iterator
{
    return std::cend(data_);
}

template <typename T>
inline auto collection<T>::rbegin() noexcept -> iterator
{
    return std::rbegin(data_);
}

template <typename T>
inline auto collection<T>::rbegin() const noexcept -> const_iterator
{
    return std::rbegin(data_);
}

template <typename T>
inline auto collection<T>::crbegin() const noexcept -> const_iterator
{
    return std::crbegin(data_);
}

template <typename T>
inline auto collection<T>::rend() noexcept -> iterator
{
    return std::rend(data_);
}

template <typename T>
inline auto collection<T>::rend() const noexcept -> const_iterator
{
    return std::rend(data_);
}

template <typename T>
inline auto collection<T>::crend() const noexcept -> const_iterator
{
    return std::crend(data_);
}

template <typename T>
inline auto collection<T>::front() noexcept -> reference
{
    return data_.front();
}

template <typename T>
inline auto collection<T>::front() const noexcept -> const_reference
{
    return data_.front();
}

template <typename T>
inline auto collection<T>::back() noexcept -> reference
{
    return data_.back();
}

template <typename T>
inline auto collection<T>::back() const noexcept -> const_reference
{
    return data_.back();
}

template <typename T>
inline auto collection<T>::insert(const_iterator pos, const T &value) -> iterator
{
    return data_.insert(pos, value);
}

template <typename T>
inline auto collection<T>::insert(const_iterator pos, T &&value) -> iterator
{
    return data_.insert(pos, std::move(value));
}

template <typename T>
inline auto collection<T>::insert(const_iterator pos, size_type count, const T &value) -> iterator
{
    return data_.insert(pos, count, value);
}

template <typename T>
template <class input_iterator_t>
inline auto collection<T>::insert(const_iterator pos, input_iterator_t first, input_iterator_t last) -> iterator
{
    return data_.insert(pos, first, last);
}

template <typename T>
inline auto collection<T>::insert(const_iterator pos, std::initializer_list<T> ilist) -> iterator
{
    return data_.insert(pos, std::move(ilist));
}

template <typename T>
template <class... args_t>
inline auto collection<T>::emplace(const_iterator pos, args_t &&...args) -> iterator
{
    return data_.insert(pos, std::forward<args_t>(args)...);
}

template <typename T>
inline auto collection<T>::erase(const_iterator pos) -> iterator
{
    return data_.erase(pos);
}

template <typename T>
inline auto collection<T>::erase(const_iterator first, const_iterator last) -> iterator
{
    return data_.erase(first, last);
}

template <typename T>
inline void collection<T>::push_back(const T &value)
{
    data_.push_back(value);
}

template <typename T>
inline void collection<T>::push_back(T &&value)
{
    data_.push_back(std::move(value));
}

template <typename T>
template <class... args_t>
inline auto collection<T>::emplace_back(args_t &&...args) -> reference
{
    return data_.emplace_back(std::forward<args_t>(args)...);
}

template <typename T>
inline void collection<T>::pop_back()
{
    data_.pop_back();
}

template <typename T>
inline void collection<T>::resize(const size_type count)
{
    data_.resize(count);
}

template <typename T>
inline void collection<T>::resize(const size_type count, const value_type &value)
{
    data_.resize(count, value);
}

template <typename T>
inline void collection<T>::swap(collection<T> &other) noexcept(
    std::allocator_traits<allocator_type>::propagate_on_container_swap::value ||
    std::allocator_traits<allocator_type>::is_always_equal::value)
{
    data_.swap(other.data_);
}

} // namespace aeon::common
