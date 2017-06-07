/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_string.h>
#include <aeon/mono/mono_exception.h>
#include <mono/jit/jit.h>
#include <utility>

namespace aeon
{
namespace mono
{

template <typename T>
struct convert_mono_type
{
    using mono_type_name = T;

    static auto convert(mono_assembly &, T &&t)
    {
        return std::forward<T>(t);
    }
};

template <>
struct convert_mono_type<std::string>
{
    using mono_type_name = MonoString *;

    static auto convert(mono_assembly &assembly, const std::string &str)
    {
        return assembly.new_string(str).get_mono_string();
    }
};

template <typename return_type_t>
class mono_method_thunk_base;

template <typename return_type_t, typename... args_t>
class mono_method_thunk_base<return_type_t(args_t...)>
{
public:
    using signature = return_type_t (*)(typename convert_mono_type<args_t>::mono_type_name..., MonoException **ex);

    explicit mono_method_thunk_base(mono_assembly &assembly, MonoMethod *method)
        : assembly_(assembly)
        , method_(reinterpret_cast<signature>(mono_method_get_unmanaged_thunk(method)))
    {
    }

    ~mono_method_thunk_base() = default;

protected:
    mono_assembly &assembly_;
    signature method_;
};

template <typename return_type_t>
class mono_method_thunk;

template <typename... args_t>
class mono_method_thunk<void(args_t...)> : public mono_method_thunk_base<void(args_t...)>
{
public:
    explicit mono_method_thunk(mono_assembly &assembly, MonoMethod *method)
        : mono_method_thunk_base(assembly, method)
    {
    }

    ~mono_method_thunk() = default;

    void operator()(args_t &&... args)
    {
        MonoException *ex = nullptr;
        method_(convert_mono_type<args_t>::convert(assembly_, std::forward<args_t>(args))..., &ex);

        if (ex)
            throw mono_thunk_exception(ex);
    }
};

template <typename return_type_t, typename... args_t>
class mono_method_thunk<return_type_t(args_t...)> : public mono_method_thunk_base<return_type_t(args_t...)>
{
public:
    explicit mono_method_thunk(mono_assembly &assembly, MonoMethod *method)
        : mono_method_thunk_base(assembly, method)
    {
    }

    ~mono_method_thunk() = default;

    return_type_t operator()(args_t &&... args)
    {
        MonoException *ex = nullptr;
        auto result = method_(convert_mono_type<args_t>::convert(assembly_, std::forward<args_t>(args))..., &ex);

        if (ex)
            throw mono_thunk_exception(ex);

        return result;
    }
};

} // namespace mono
} // namespace aeon
