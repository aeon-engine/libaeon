// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <memory_resource>
#include <functional>
#include <memory>

namespace aeon::common::pmr
{

template <typename T>
using unique_ptr = std::unique_ptr<T, std::function<void(T *)>>;

template <typename T, typename... args_t>
[[nodiscard]] auto make_unique(std::pmr::memory_resource *allocator, args_t &&...args)
{
    return unique_ptr<T>(
        new (allocator->allocate(sizeof(T), alignof(T))) T(std::forward<args_t>(args)...),
        [allocator, size = sizeof(T), align = alignof(T)](T *ptr) { allocator->deallocate(ptr, size, align); });
}

} // namespace aeon::common::pmr
