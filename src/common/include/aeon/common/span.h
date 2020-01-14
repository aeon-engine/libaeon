// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/common/assert.h>
#include <type_traits>
#include <cstddef>
#include <iterator>
#include <array>

namespace aeon::common
{

template <typename T>
class span
{
public:
    using element_type = T;
    using value_type = std::remove_cv_t<T>;
    using index_type = std::ptrdiff_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator = pointer;
    using const_iterator = const pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    explicit constexpr span() noexcept;

    explicit constexpr span(pointer ptr, const index_type count) noexcept;

    explicit constexpr span(pointer first, pointer last) noexcept;

    template <std::size_t N>
    explicit constexpr span(std::array<value_type, N> &array) noexcept;

    template <std::size_t N>
    explicit constexpr span(const std::array<value_type, N> &array) noexcept;

    template <typename container_t>
    explicit constexpr span(container_t &cont);

    template <typename container_t>
    explicit constexpr span(const container_t &cont);

    ~span() = default;

    span(const span &) noexcept = default;
    auto operator=(const span &) noexcept -> span & = default;

    span(span &&) noexcept = default;
    auto operator=(span &&) noexcept -> span & = default;

    [[nodiscard]] constexpr auto data() const noexcept -> pointer;

    [[nodiscard]] constexpr auto size() const noexcept -> index_type;

    [[nodiscard]] constexpr auto empty() const noexcept -> bool;

    [[nodiscard]] constexpr auto operator[](const index_type i) const noexcept -> reference;

    [[nodiscard]] constexpr auto operator()(const index_type i) const noexcept -> reference;

    [[nodiscard]] constexpr auto at(const index_type i) const -> reference;

    [[nodiscard]] constexpr auto begin() const noexcept -> iterator;

    [[nodiscard]] constexpr auto end() const noexcept -> iterator;

    [[nodiscard]] constexpr auto front() const noexcept -> reference;

    [[nodiscard]] constexpr auto back() const noexcept -> reference;

private:
    pointer data_;
    index_type size_;
};

template <typename T>
inline constexpr span<T>::span() noexcept
    : data_{nullptr}
    , size_{0}
{
}

template <typename T>
inline constexpr span<T>::span(pointer ptr, const index_type count) noexcept
    : data_{ptr}
    , size_{count}
{
}

template <typename T>
inline constexpr span<T>::span(pointer first, pointer last) noexcept
    : data_{first}
    , size_{std::distance(first, last)}
{
}

template <typename T>
template <std::size_t N>
inline constexpr span<T>::span(std::array<value_type, N> &array) noexcept
    : data_{array.data()}
    , size_{static_cast<index_type>(array.size())}
{
}

template <typename T>
template <std::size_t N>
inline constexpr span<T>::span(const std::array<value_type, N> &array) noexcept
    : data_{array.data()}
    , size_{static_cast<index_type>(array.size())}
{
}

template <typename T>
template <typename container_t>
inline constexpr span<T>::span(container_t &cont)
    : data_{std::data(cont)}
    , size_{static_cast<index_type>(std::size(cont))}
{
}

template <typename T>
template <typename container_t>
inline constexpr span<T>::span(const container_t &cont)
    : data_{std::data(cont)}
    , size_{static_cast<index_type>(std::size(cont))}
{
}

template <typename T>
[[nodiscard]] inline constexpr auto span<T>::data() const noexcept -> pointer
{
    return data_;
}

template <typename T>
[[nodiscard]] inline constexpr auto span<T>::size() const noexcept -> index_type
{
    return size_;
}

template <typename T>
[[nodiscard]] inline constexpr auto span<T>::empty() const noexcept -> bool
{
    return size() == 0;
}

template <typename T>
[[nodiscard]] inline constexpr auto span<T>::operator[](const index_type i) const noexcept -> reference
{
    aeon_assert(i >= 0, "Out of range.");
    aeon_assert(i < size(), "Out of range.");
    return *(data() + i);
}

template <typename T>
[[nodiscard]] inline constexpr auto span<T>::operator()(const index_type i) const noexcept -> reference
{
    aeon_assert(i >= 0, "Out of range.");
    aeon_assert(i < size(), "Out of range.");
    return *(data() + i);
}

template <typename T>
[[nodiscard]] inline constexpr auto span<T>::at(const index_type i) const -> reference
{
    if (i < 0 || i > size())
        throw std::out_of_range{"Out of range."};

    return *(data() + i);
}

template <typename T>
[[nodiscard]] inline constexpr auto span<T>::begin() const noexcept -> iterator
{
    return data();
}

template <typename T>
[[nodiscard]] inline constexpr auto span<T>::end() const noexcept -> iterator
{
    return data() + size();
}

template <typename T>
[[nodiscard]] inline constexpr auto span<T>::front() const noexcept -> reference
{
    aeon_assert(!empty(), "Span empty.");
    return *data();
}

template <typename T>
[[nodiscard]] inline constexpr auto span<T>::back() const noexcept -> reference
{
    aeon_assert(!empty(), "Span empty.");
    return *(data() + size() - 1);
}

template <typename T, size_t N>
span(std::array<T, N> &)->span<T>;

template <typename T, size_t N>
span(const std::array<T, N> &)->span<const T>;

template <typename container_t>
span(container_t &)->span<typename container_t::value_type>;

template <typename container_t>
span(const container_t &)->span<const typename container_t::value_type>;

} // namespace aeon::common
