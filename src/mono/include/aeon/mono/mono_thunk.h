// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/mono/mono_thunk_base.h>
#include <aeon/mono/mono_type_conversion.h>
#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_string.h>
#include <aeon/mono/mono_exception.h>
#include <aeon/common/compilers.h>

AEON_IGNORE_VS_WARNING_PUSH(4201)
#include <mono/jit/jit.h>
AEON_IGNORE_VS_WARNING_POP()

#include <utility>

namespace aeon::mono
{

template <typename return_type_t>
class mono_thunk;

template <typename... args_t>
class mono_thunk<void(args_t...)> : public mono_thunk_base<void(args_t...)>
{
public:
    mono_thunk() noexcept
        : mono_thunk_base<void(args_t...)>()
        , mono_object()
    {
    }

    explicit mono_thunk(const mono_assembly &assembly, MonoMethod *method) noexcept
        : mono_thunk_base<void(args_t...)>(assembly, method)
    {
    }

    ~mono_thunk() = default;

    mono_thunk(const mono_thunk &) = delete;
    auto operator=(const mono_thunk &) -> mono_thunk & = delete;

    mono_thunk(mono_thunk &&o) = delete;
    auto operator=(mono_thunk &&o) -> mono_thunk & = delete;

    void operator()(args_t... args) const
    {
        MonoException *ex = nullptr;
        this->method_(convert_mono_type<args_t>::to_mono(*this->assembly_, std::forward<args_t>(args))..., &ex);

        if (ex)
            throw mono_thunk_exception{ex};
    }
};

template <typename return_type_t, typename... args_t>
class mono_thunk<return_type_t(args_t...)> : public mono_thunk_base<return_type_t(args_t...)>
{
public:
    mono_thunk() noexcept
        : mono_thunk_base<return_type_t(args_t...)>{}
        , mono_object{}
    {
    }

    explicit mono_thunk(const mono_assembly &assembly, MonoMethod *method) noexcept
        : mono_thunk_base<return_type_t(args_t...)>(assembly, method)
    {
    }

    ~mono_thunk() = default;

    mono_thunk(const mono_thunk &) = delete;
    auto operator=(const mono_thunk &) -> mono_thunk & = delete;

    mono_thunk(mono_thunk &&o) = delete;
    auto operator=(mono_thunk &&o) -> mono_thunk & = delete;

    [[nodiscard]] auto operator()(args_t... args) const
    {
        MonoException *ex = nullptr;
        auto result =
            this->method_(convert_mono_type<args_t>::to_mono(*this->assembly_, std::forward<args_t>(args))..., &ex);

        if (ex)
            throw mono_thunk_exception{ex};

        return convert_mono_type<return_type_t>::from_mono(std::move(result));
    }
};

} // namespace aeon::mono
