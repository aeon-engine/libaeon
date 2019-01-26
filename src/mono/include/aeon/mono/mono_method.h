// Copyright (c) 2012-2019 Robin Degen

#pragma once

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/mono/mono_method_thunk.h>
#include <mono/jit/jit.h>
#include <string>

namespace aeon::mono
{

class mono_object;
class mono_assembly;

class mono_method
{
public:
    mono_method() noexcept;
    explicit mono_method(const mono_assembly *assembly, MonoClass *cls, MonoObject *object, const std::string &name,
                         int argc) noexcept;

    ~mono_method();

    mono_method(const mono_method &) = delete;
    auto operator=(const mono_method &) -> mono_method & = delete;

    mono_method(mono_method &&o) noexcept;
    auto operator=(mono_method &&o) noexcept -> mono_method &;

    template <typename function_signature_t>
    auto get_thunk();

private:
    MonoMethod *method_;
    MonoObject *object_;
    const mono_assembly *assembly_;
};

template <typename function_signature_t>
auto mono_method::get_thunk()
{
    return mono_method_thunk<function_signature_t>(*assembly_, object_, method_);
}

} // namespace aeon::mono
