// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/compilers.h>
#include <memory_resource>
#include <functional>
#include <memory>

namespace aeon::common::pmr
{

namespace internal
{

template <typename T>
struct unique_ptr_pmr_deleter
{
    AEON_FORCE_INLINE void operator()(T *ptr)
    {
        allocator->deallocate(ptr, sizeof(T), alignof(T));
    }

    std::pmr::memory_resource *allocator;
};

} // namespace internal

template <typename T>
using unique_ptr = std::unique_ptr<T, internal::unique_ptr_pmr_deleter<T>>;

template <typename T, typename... args_t>
[[nodiscard]] auto make_unique(std::pmr::memory_resource *allocator, args_t &&...args)
{
    return unique_ptr<T>(new (allocator->allocate(sizeof(T), alignof(T))) T(std::forward<args_t>(args)...),
                         internal::unique_ptr_pmr_deleter<T>{allocator});
}

} // namespace aeon::common::pmr
