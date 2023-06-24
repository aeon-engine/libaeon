// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

namespace aeon::common::allocators
{

template <typename T>
concept allocator = requires {
    T::allocate(0u);
    T::allocate_at_least(0u);
    T::reallocate(nullptr, 0u);
    T::deallocate(nullptr, 0u);
};

} // namespace aeon::common::allocators
