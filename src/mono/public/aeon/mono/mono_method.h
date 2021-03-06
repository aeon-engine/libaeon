// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/mono/mono_method_thunk.h>
#include <aeon/common/compilers.h>

AEON_IGNORE_VS_WARNING_PUSH(4201)
#include <mono/jit/jit.h>
AEON_IGNORE_VS_WARNING_POP()

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
    [[nodiscard]] auto operator=(const mono_method &) -> mono_method & = delete;

    mono_method(mono_method &&) noexcept;
    [[nodiscard]] auto operator=(mono_method &&) noexcept -> mono_method &;

    template <typename function_signature_t>
    [[nodiscard]] auto get_thunk();

private:
    MonoMethod *method_;
    MonoObject *object_;
    const mono_assembly *assembly_;
};

template <typename function_signature_t>
[[nodiscard]] auto mono_method::get_thunk()
{
    return mono_method_thunk<function_signature_t>(*assembly_, object_, method_);
}

} // namespace aeon::mono
