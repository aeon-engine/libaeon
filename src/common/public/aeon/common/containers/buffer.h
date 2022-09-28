// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/allocators/ansi_allocator.h>
#include <aeon/common/allocators/concept.h>
#include <cstddef>
#include <algorithm>

namespace aeon::common::containers
{

template <typename T>
struct buffer_default_pair
{
    T *data;
    std::size_t capacity;
};

/*!
 * A simple raw buffer of data. This buffer does not automatically grow; like std::vector.
 * Neither does it call any constructors or destructors on the type. Depending on the given
 * allocator, the heap data is not even initialized with any value by default. Another thing
 * to consider is that there are no checks being done on the allocated memory. If for some
 * reason the allocation fails, you will not receive an exception. It's more likely the
 * program will crash. This class should only be used when performance is preferred over
 * programmer safety.
 *
 * Typically this should only be used for raw data; for example std::byte or char.
 */
template <typename T, allocators::allocator AllocatorT = allocators::ansi_allocator<T>,
          typename StoragePairT = buffer_default_pair<T>>
class buffer
{
public:
    using value_type = T;
    using allocator = AllocatorT;
    using storage_pair = StoragePairT;

    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

    buffer()
    {
        // Do not default initialize the pair; as it may contain other values
        // or state that we shouldn't interfere with.
        pair_.data = nullptr;
        pair_.capacity = 0;
    }

    explicit buffer(const size_type size)
        : buffer{}
    {
        resize(size);
    }

    buffer(const buffer<T, AllocatorT> &other)
    {
        // Do not default initialize the pair; as it may contain other values
        // or state that we shouldn't interfere with.
        pair_.data = nullptr;
        pair_.capacity = 0;

        resize(other.capacity());
        std::copy_n(other.data(), other.capacity(), pair_.data);
    }

    auto operator=(const buffer<T, AllocatorT> &other) -> buffer<T, AllocatorT> &
    {
        reset();

        resize(other.capacity());
        std::copy_n(other.data(), other.capacity(), pair_.data);

        return *this;
    }

    buffer(buffer<T, AllocatorT> &&other) noexcept
    {
        pair_.data = other.pair_.data;
        pair_.capacity = other.pair_.capacity;

        other.pair_.data = nullptr;
        other.pair_.capacity = 0;
    }

    auto operator=(buffer<T, AllocatorT> &&other) noexcept -> buffer<T, AllocatorT> &
    {
        reset();

        pair_.data = other.pair_.data;
        pair_.capacity = other.pair_.capacity;
        other.pair_.data = nullptr;
        other.pair_.capacity = 0;

        return *this;
    }

    ~buffer()
    {
        reset();
    }

    [[nodiscard]] auto begin() noexcept -> pointer
    {
        return pair_.data;
    }

    [[nodiscard]] auto end() noexcept -> pointer
    {
        return pair_.data + pair_.capacity;
    }

    [[nodiscard]] auto begin() const noexcept -> pointer
    {
        return pair_.data;
    }

    [[nodiscard]] auto end() const noexcept -> pointer
    {
        return pair_.data + pair_.capacity;
    }

    [[nodiscard]] auto cbegin() const noexcept -> pointer
    {
        return pair_.data;
    }

    [[nodiscard]] auto cend() const noexcept -> pointer
    {
        return pair_.data + pair_.capacity;
    }

    [[nodiscard]] auto capacity() const noexcept -> size_type
    {
        return pair_.capacity;
    }

    [[nodiscard]] auto data() noexcept -> pointer
    {
        return pair_.data;
    }

    [[nodiscard]] auto data() const noexcept -> const_pointer
    {
        return pair_.data;
    }

    void resize(const size_type size)
    {
        pair_.data = allocator::reallocate(pair_.data, size);
        pair_.capacity = size;
    }

    void reset()
    {
        // Note that data is not checked for nullptr here. It is up
        // to the allocator to handle this case.
        allocator::deallocate(pair_.data, pair_.capacity);
        pair_.data = nullptr;
        pair_.capacity = 0;
    }

    [[nodiscard]] auto empty() const noexcept
    {
        return pair_.capacity == 0u;
    }

    [[nodiscard]] auto at(const size_type pos) noexcept -> reference
    {
        return pair_.data[pos];
    }

    [[nodiscard]] auto at(const size_type pos) const noexcept -> const_reference
    {
        return pair_.data[pos];
    }

    auto operator[](const size_type pos) noexcept -> reference
    {
        return at(pos);
    }

    auto operator[](const size_type pos) const noexcept -> const_reference
    {
        return at(pos);
    }

private:
    storage_pair pair_;
};

} // namespace aeon::common::containers
