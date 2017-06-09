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

#include <aeon/mono/mono_method_thunk_signature.h>
#include <aeon/mono/mono_assembly.h>
#include <mono/jit/jit.h>

namespace aeon
{
namespace mono
{

template <typename return_type_t>
class mono_method_thunk_base;

template <typename return_type_t, typename... args_t>
class mono_method_thunk_base<return_type_t(args_t...)>
{
public:
    using signature = typename mono_method_thunk_signature<return_type_t(args_t...)>::type;

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

} // namespace mono
} // namespace aeon
