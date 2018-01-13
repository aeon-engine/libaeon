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

#include <aeon/common/noncopyable.h>
#include <mono/jit/jit.h>
#include <cstdint>

namespace aeon
{
namespace mono
{

class mono_object;

class mono_gc_handle
{
public:
    explicit mono_gc_handle(mono_object &obj);
    explicit mono_gc_handle(MonoObject *obj);
    virtual ~mono_gc_handle();

    void lock();
    void unlock();

private:
    std::uint32_t handle_;
    MonoObject *object_;
};

class mono_scoped_gc_handle : public common::noncopyable
{
public:
    explicit mono_scoped_gc_handle(mono_gc_handle &handle)
        : handle_(handle)
    {
        handle_.lock();
    }

    ~mono_scoped_gc_handle()
    {
        handle_.unlock();
    }

    auto &get_handle() const
    {
        return handle_;
    }

private:
    mono_gc_handle &handle_;
};

} // namespace mono
} // namespace aeon
