// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <stdexcept>

namespace aeon::common
{

/*!
 * Base class for thread-safe singletons.
 */
template <class type>
class singleton
{
public:
    static auto get_singleton() -> type &
    {
        static type instance;
        return instance;
    }

    static auto get_singleton_ptr() -> type *
    {
        return &get_singleton();
    }
};

} // namespace aeon::common
