// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/mono/mono_thunk.h>
#include <aeon/common/compilers.h>

AEON_IGNORE_VS_WARNING_PUSH(4201)
#include <mono/jit/jit.h>
AEON_IGNORE_VS_WARNING_POP()

#include <string>

namespace aeon::mono
{

class mono_assembly;

class mono_static_function
{
public:
    mono_static_function() noexcept;
    explicit mono_static_function(const mono_assembly *assembly, MonoClass *cls, const std::string &name,
                                  int argc) noexcept;

    ~mono_static_function();

    mono_static_function(const mono_static_function &) = delete;
    auto operator=(const mono_static_function &) -> mono_static_function & = delete;

    mono_static_function(mono_static_function &&) noexcept;
    auto operator=(mono_static_function &&) noexcept -> mono_static_function &;

    template <typename function_signature_t>
    [[nodiscard]] auto get_thunk() const noexcept;

private:
    MonoMethod *method_;
    const mono_assembly *assembly_;
};

template <typename function_signature_t>
[[nodiscard]] auto mono_static_function::get_thunk() const noexcept
{
    return mono_thunk<function_signature_t>{*assembly_, method_};
}

} // namespace aeon::mono
