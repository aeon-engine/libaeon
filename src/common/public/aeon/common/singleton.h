// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::common
{

/*!
 * Base class for thread-safe singletons.
 */
template <class type>
class singleton
{
public:
    [[nodiscard]] static auto get_singleton() -> type &
    {
        static type instance;
        return instance;
    }

    [[nodiscard]] static auto get_singleton_ptr() -> type *
    {
        return &get_singleton();
    }
};

} // namespace aeon::common
