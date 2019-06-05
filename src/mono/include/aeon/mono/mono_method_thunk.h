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
#include <aeon/mono/mono_exception.h>
#include <aeon/mono/mono_object.h>
#include <mono/jit/jit.h>
#include <utility>

namespace aeon::mono
{

template <typename return_type_t>
class mono_method_thunk;

template <typename... args_t>
class mono_method_thunk<void(args_t...)> : public mono_thunk_base<void(MonoObject *, args_t...)>, public mono_object
{
public:
    mono_method_thunk()
        : mono_thunk_base<void(MonoObject *, args_t...)>()
        , mono_object()
    {
    }

    explicit mono_method_thunk(const mono_assembly &assembly, MonoObject *object, MonoMethod *method)
        : mono_thunk_base<void(MonoObject *, args_t...)>(assembly, method)
        , mono_object(object)
    {
    }

    ~mono_method_thunk() = default;

    mono_method_thunk(const mono_method_thunk &) = delete;
    auto operator=(const mono_method_thunk &) -> mono_method_thunk & = delete;

    mono_method_thunk(mono_method_thunk &&) noexcept = default;
    auto operator=(mono_method_thunk &&) noexcept -> mono_method_thunk & = default;

    void operator()(args_t... args)
    {
        MonoException *ex = nullptr;
        this->method_(this->object_,
                      convert_mono_type<args_t>::to_mono(*this->assembly_, std::forward<args_t>(args))..., &ex);

        if (ex)
            throw mono_thunk_exception{ex};
    }
};

template <typename return_type_t, typename... args_t>
class mono_method_thunk<return_type_t(args_t...)> : public mono_thunk_base<return_type_t(MonoObject *, args_t...)>,
                                                    public mono_object
{
public:
    mono_method_thunk()
        : mono_thunk_base<return_type_t(MonoObject *, args_t...)>()
        , mono_object()
    {
    }

    explicit mono_method_thunk(const mono_assembly &assembly, MonoObject *object, MonoMethod *method)
        : mono_thunk_base<return_type_t(MonoObject *, args_t...)>(assembly, method)
        , mono_object(object)
    {
    }

    ~mono_method_thunk() = default;

    mono_method_thunk(const mono_method_thunk &) = delete;
    auto operator=(const mono_method_thunk &) -> mono_method_thunk & = delete;

    mono_method_thunk(mono_method_thunk &&) noexcept = default;
    auto operator=(mono_method_thunk &&) noexcept -> mono_method_thunk & = default;

    [[nodiscard]] auto operator()(args_t... args)
    {
        MonoException *ex = nullptr;
        auto result = this->method_(
            this->object_, convert_mono_type<args_t>::to_mono(*this->assembly_, std::forward<args_t>(args))..., &ex);

        if (ex)
            throw mono_thunk_exception{ex};

        return convert_mono_type<return_type_t>::from_mono(std::move(result));
    }
};

} // namespace aeon::mono
