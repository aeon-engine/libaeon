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

#include <aeon/common/noncopyable.h>
#include <mono/jit/jit.h>
#include <string>

namespace aeon
{
namespace mono
{

class mono_class;
class mono_class_instance;
class mono_string;

class mono_assembly : public common::noncopyable
{
public:
    mono_assembly();
    explicit mono_assembly(MonoDomain *domain, const std::string &path);
    virtual ~mono_assembly();

    mono_assembly(mono_assembly &&o);
    auto operator=(mono_assembly &&o) -> mono_assembly &;

    auto get_class(const std::string &name) const -> mono_class;
    auto new_class_instance(const mono_class &cls) const -> mono_class_instance;
    auto new_string(const std::string &str) const -> mono_string;

private:
    MonoDomain *domain_;
    MonoAssembly *assembly_;
    MonoImage *image_;
};

} // namespace mono
} // namespace aeon
