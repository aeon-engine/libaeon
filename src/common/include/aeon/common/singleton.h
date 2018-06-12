/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/common/noncopyable.h>

#include <stdexcept>

#define aeon_utility_initialize_singleton(type)                                                                        \
    template <>                                                                                                        \
    type *aeon::common::singleton<type>::instance_ = nullptr

namespace aeon::common
{

/*!
 * Base class for singletons.
 * This class does not own the instance; so you must
 * take care of deleting the instance when it's no
 * longer needed to prevent leaks.
 */
template <class type>
class singleton
{
public:
    singleton()
    {
        if (instance_)
            throw std::runtime_error("Singleton could not be created. Already exists.");

        instance_ = static_cast<type *>(this);

        if (!instance_)
            throw std::runtime_error("Singleton could not be created.");
    }

    ~singleton() noexcept
    {
        instance_ = nullptr;
    }

    singleton(const singleton<type> &) noexcept = default;
    auto operator=(const singleton<type> &) noexcept -> singleton<type> & = default;
    singleton(singleton<type> &&) noexcept = default;
    auto operator=(singleton<type> &&) noexcept -> singleton<type> & = default;

    static auto *create()
    {
        return new type;
    }

    static void dispose()
    {
        delete instance_;
    }

    static auto &get_singleton()
    {
        if (!instance_)
            throw std::runtime_error("Singleton instance is null.");

        return *instance_;
    }

    static auto get_singleton_ptr() noexcept
    {
        return instance_;
    }

protected:
    static type *instance_;
};

} // namespace aeon::common
