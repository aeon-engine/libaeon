/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/mono/mono_exception.h>
#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_string.h>
#include <string>

namespace aeon
{
namespace mono
{

template <typename T>
struct convert_mono_type
{
    using mono_type_name = T;

    static auto to_mono(mono_assembly &, T &&t) -> T
    {
        return std::forward<T>(t);
    }

    static auto from_mono(T &&t) -> T
    {
        return std::forward<T>(t);
    }
};

template <>
struct convert_mono_type<std::string>
{
    using mono_type_name = MonoString *;

    static auto to_mono(mono_assembly &assembly, const std::string &str) -> MonoString *
    {
        return assembly.new_string(str).get_mono_string();
    }

    static auto from_mono(MonoString *mono_str) -> std::string
    {
        return mono_string(mono_str).str();
    }
};

} // namespace mono
} // namespace aeon
