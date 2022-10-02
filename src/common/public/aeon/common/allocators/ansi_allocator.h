// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <cstdlib>

namespace aeon::common::allocators
{

/*!
 * Simple wrapper around the ansi C malloc/realloc/free functions.
 * Note that this allocator will only allocate memory. It will NOT
 * call any constructors. These should only be used for raw data,
 * not for arrays of objects.
 */
template <typename T>
struct ansi_allocator
{
    static auto allocate(const std::size_t n) noexcept
    {
        return static_cast<T *>(malloc(n * sizeof(T)));
    }

    static auto allocate_at_least(const std::size_t n) noexcept
    {
        return allocate(n);
    }

    static auto reallocate(T *ptr, const std::size_t n) noexcept
    {
        return static_cast<T *>(realloc(ptr, n * sizeof(T)));
    }

    static void deallocate(T *ptr, [[maybe_unused]] const std::size_t n) noexcept
    {
        free(ptr);
    }
};

} // namespace aeon::common::allocators
