// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/platform.h>
#include <aeon/common/flags.h>
#include <cstdlib>

#if (!defined(AEON_PLATFORM_OS_WINDOWS))
static_assert(false, "This header can only be used on windows.");
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace aeon::common::allocators
{

enum class windows_heap_allocator_flags : std::uint64_t
{
    no_serialize = HEAP_NO_SERIALIZE,
    zero_memory = HEAP_ZERO_MEMORY,
    generate_exceptions = HEAP_GENERATE_EXCEPTIONS,
    align_16 = HEAP_CREATE_ALIGN_16
};

aeon_declare_flag_operators(windows_heap_allocator_flags)

/*!
 * Simple base class for the heap allocator that does not contain the type, to avoid creating
 * a different heap for every type.
 */
template <flags<windows_heap_allocator_flags> flags = windows_heap_allocator_flags::no_serialize,
          std::size_t initial_heap_size = 0, std::size_t maximum_heap_size = 0>
struct windows_heap_allocator_base
{
protected:
    static auto get_heap() noexcept -> HANDLE
    {
        static auto heap = HeapCreate(static_cast<DWORD>(flags), initial_heap_size, maximum_heap_size);
        return heap;
    }
};

/*!
 * Wrapper around the windows HeapAlloc, HeapReAlloc and HeapFree functions.
 * By default this will create a thread unsafe heap. This means that an allocation
 * can only be allocated and deleted from the same thread unless manual synchronisation
 * is done. In a well designed implementation this should be the case anyway, as data
 * typically isn't owned by multiple threads at the same time; only read.
 *
 * Note that this allocator will only allocate memory. It will NOT
 * call any constructors. These should only be used for raw data,
 * not for arrays of objects.
 */
template <typename T, flags<windows_heap_allocator_flags> flags = windows_heap_allocator_flags::no_serialize,
          std::size_t initial_heap_size = 0, std::size_t maximum_heap_size = 0>
struct windows_heap_allocator : windows_heap_allocator_base<flags, initial_heap_size, maximum_heap_size>
{
    static auto allocate(const std::size_t n) noexcept
    {
        return static_cast<T *>(
            HeapAlloc(windows_heap_allocator_base<flags, initial_heap_size, maximum_heap_size>::get_heap(),
                      static_cast<DWORD>(flags), n * sizeof(T)));
    }

    static auto allocate_at_least(const std::size_t n) noexcept
    {
        return allocate(n);
    }

    static auto reallocate(T *ptr, const std::size_t n) noexcept
    {
        if (!ptr)
            return allocate(n);

        return static_cast<T *>(
            HeapReAlloc(windows_heap_allocator_base<flags, initial_heap_size, maximum_heap_size>::get_heap(),
                        static_cast<DWORD>(flags), ptr, n * sizeof(T)));
    }

    static void deallocate(T *ptr, [[maybe_unused]] const std::size_t n) noexcept
    {
        HeapFree(windows_heap_allocator_base<flags, initial_heap_size, maximum_heap_size>::get_heap(),
                 static_cast<DWORD>(flags), ptr);
    }
};

} // namespace aeon::common::allocators
