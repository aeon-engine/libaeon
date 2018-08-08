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

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <mono/jit/jit.h>
#include <cstdint>

namespace aeon::mono
{

class mono_object;

class mono_gc_handle
{
public:
    explicit mono_gc_handle(mono_object &obj) noexcept;
    explicit mono_gc_handle(MonoObject *obj) noexcept;
    ~mono_gc_handle();

    mono_gc_handle(const mono_gc_handle &) = default;
    auto operator=(const mono_gc_handle &) -> mono_gc_handle & = default;

    mono_gc_handle(mono_gc_handle &&o) = default;
    auto operator=(mono_gc_handle &&o) -> mono_gc_handle & = default;

    void lock() noexcept;
    void unlock() noexcept;

private:
    std::uint32_t handle_;
    MonoObject *object_;
};

class mono_scoped_gc_handle
{
public:
    explicit mono_scoped_gc_handle(mono_gc_handle &handle) noexcept
        : handle_(handle)
    {
        handle_.lock();
    }

    ~mono_scoped_gc_handle()
    {
        handle_.unlock();
    }

    auto &get_handle() const noexcept
    {
        return handle_;
    }

    mono_scoped_gc_handle(const mono_scoped_gc_handle &) = delete;
    auto operator=(const mono_scoped_gc_handle &) -> mono_scoped_gc_handle & = delete;

    mono_scoped_gc_handle(mono_scoped_gc_handle &&o) = delete;
    auto operator=(mono_scoped_gc_handle &&o) -> mono_scoped_gc_handle & = delete;

private:
    mono_gc_handle &handle_;
};

} // namespace aeon::mono
