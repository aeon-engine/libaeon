// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/mono/mono_thunk_signature.h>
#include <aeon/mono/mono_assembly.h>
#include <aeon/common/compilers.h>

AEON_IGNORE_VS_WARNING_PUSH(4201)
#include <mono/jit/jit.h>
AEON_IGNORE_VS_WARNING_POP()

namespace aeon::mono
{

template <typename return_type_t>
class mono_thunk_base;

template <typename return_type_t, typename... args_t>
class mono_thunk_base<return_type_t(args_t...)>
{
protected:
    using signature = typename mono_thunk_signature<return_type_t(args_t...)>::type;

    mono_thunk_base() noexcept
        : assembly_{nullptr}
        , method_{nullptr}
    {
    }

    explicit mono_thunk_base(const mono_assembly &assembly, MonoMethod *method) noexcept
        : assembly_{&assembly}
        , method_{reinterpret_cast<signature>(mono_method_get_unmanaged_thunk(method))}
    {
    }

    ~mono_thunk_base() = default;

    mono_thunk_base(const mono_thunk_base &) noexcept = default;
    auto operator=(const mono_thunk_base &) noexcept -> mono_thunk_base & = default;

    mono_thunk_base(mono_thunk_base &&) noexcept = default;
    auto operator=(mono_thunk_base &&) noexcept -> mono_thunk_base & = default;

    const mono_assembly *assembly_;
    signature method_;
};

} // namespace aeon::mono
