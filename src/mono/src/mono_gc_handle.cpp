// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/mono/mono_gc_handle.h>
#include <aeon/mono/mono_object.h>
#include <cassert>

namespace aeon::mono
{

mono_gc_handle::mono_gc_handle(mono_object &obj) noexcept
    : mono_gc_handle{obj.get_mono_object()}
{
}

mono_gc_handle::mono_gc_handle(MonoObject *obj) noexcept
    : handle_{0}
    , object_{obj}
{
}

mono_gc_handle::~mono_gc_handle() = default;

void mono_gc_handle::lock() noexcept
{
    assert(handle_ == 0);
    handle_ = mono_gchandle_new(object_, 1);
}

void mono_gc_handle::unlock() noexcept
{
    assert(handle_ != 0);
    mono_gchandle_free(handle_);
    handle_ = 0;
}

} // namespace aeon::mono
