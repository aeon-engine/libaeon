// Copyright (c) 2012-2019 Robin Degen

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
