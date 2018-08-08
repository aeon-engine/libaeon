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

#include <aeon/mono/mono_object.h>
#include <mono/jit/jit.h>
#include <string>

namespace aeon
{
namespace mono
{

class mono_string : public mono_object
{
public:
    explicit mono_string(MonoString *mono_string);
    explicit mono_string(MonoDomain *domain, const std::string &str);
    virtual ~mono_string();

    mono_string(const mono_string &) = delete;
    auto operator=(const mono_string &) -> mono_string & = delete;

    mono_string(mono_string &&o);
    auto operator=(mono_string &&o) -> mono_string &;

    auto operator=(const std::string &str) -> mono_string &;

    auto str() const -> std::string;

    auto get_mono_string() const -> MonoString *;

private:
    MonoDomain *domain_;
};

} // namespace mono
} // namespace aeon
