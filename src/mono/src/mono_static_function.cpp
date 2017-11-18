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

#include <aeon/mono/mono_static_function.h>
#include <utility>

namespace aeon
{
namespace mono
{

mono_static_function::mono_static_function()
    : method_(nullptr)
    , assembly_(nullptr)
{
}

mono_static_function::mono_static_function(mono_assembly *assembly, MonoClass *cls, const std::string &name, int argc)
    : method_(nullptr)
    , assembly_(assembly)
{
    method_ = mono_class_get_method_from_name(cls, name.c_str(), argc);
}

mono_static_function::~mono_static_function() = default;

mono_static_function::mono_static_function(mono_static_function &&o) = default;

auto mono_static_function::operator=(mono_static_function &&o) -> mono_static_function & = default;

} // namespace mono
} // namespace aeon