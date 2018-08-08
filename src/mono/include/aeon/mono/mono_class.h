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

#include <aeon/mono/mono_static_function.h>
#include <aeon/common/type_traits.h>
#include <mono/jit/jit.h>
#include <string>

namespace aeon::mono
{

class mono_assembly;
class mono_class_field;

class mono_class
{
public:
    mono_class() noexcept;
    explicit mono_class(const mono_assembly *assembly, MonoClass *cls) noexcept;
    explicit mono_class(const mono_assembly *assembly, MonoImage *image, const std::string &name);
    explicit mono_class(const mono_assembly *assembly, MonoImage *image, const std::string &name_space,
                        const std::string &name);
    virtual ~mono_class();

    mono_class(const mono_class &) = delete;
    auto operator=(const mono_class &) -> mono_class & = delete;

    mono_class(mono_class &&o) noexcept;
    auto operator=(mono_class &&o) noexcept -> mono_class &;

    auto get_static_function(const std::string &name, int argc = 0) const -> mono_static_function;

    template <typename function_signature_t>
    auto get_static_function_thunk(const std::string &name);

    auto get_mono_class_ptr() const noexcept -> MonoClass *;

    auto get_field(const std::string &name) const -> mono_class_field;

private:
    MonoClass *class_;
    const mono_assembly *assembly_;
};

template <typename function_signature_t>
auto mono_class::get_static_function_thunk(const std::string &name)
{
    constexpr auto arg_count = common::type_traits::function_signature_argument_count<function_signature_t>::value;
    auto func = get_static_function(name, arg_count);
    return func.template get_thunk<function_signature_t>();
}

} // namespace aeon::mono
