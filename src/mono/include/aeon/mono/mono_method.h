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

#include <aeon/mono/mono_method_thunk.h>
#include <mono/jit/jit.h>
#include <string>
#include <vector>

namespace aeon
{
namespace mono
{

class mono_object;
class mono_assembly;

class mono_method
{
public:
    mono_method();
    explicit mono_method(mono_assembly *assembly, MonoClass *cls, MonoObject *object, const std::string &name,
                         int argc);

    ~mono_method();

    mono_method(const mono_method &) = delete;
    auto operator=(const mono_method &) -> mono_method & = delete;

    mono_method(mono_method &&o);
    auto operator=(mono_method &&o) -> mono_method &;

    template <typename function_signature_t>
    auto get_thunk();

private:
    MonoMethod *method_;
    MonoObject *object_;
    mono_assembly *assembly_;
};

template <typename function_signature_t>
auto mono_method::get_thunk()
{
    return mono_method_thunk<function_signature_t>(*assembly_, object_, method_);
}

} // namespace mono
} // namespace aeon
