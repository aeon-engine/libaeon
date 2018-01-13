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

#include <aeon/mono/mono_method.h>
#include <aeon/mono/mono_object.h>

#include <utility>

namespace aeon
{
namespace mono
{

mono_method::mono_method()
    : method_(nullptr)
    , object_(nullptr)
    , assembly_(nullptr)
{
}

mono_method::mono_method(mono_assembly *assembly, MonoClass *cls, MonoObject *object, const std::string &name, int argc)
    : method_(nullptr)
    , object_(object)
    , assembly_(assembly)
{
    method_ = mono_class_get_method_from_name(cls, name.c_str(), argc);
}

mono_method::~mono_method() = default;

mono_method::mono_method(mono_method &&o) = default;

auto mono_method::operator=(mono_method &&o) -> mono_method & = default;

} // namespace mono
} // namespace aeon
