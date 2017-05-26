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

#include <aeon/mono/mono_class_instance.h>
#include <aeon/mono/mono_gchandle.h>
#include <aeon/mono/mono_method.h>

namespace aeon
{
namespace mono
{

mono_class_instance::mono_class_instance(MonoObject *obj)
    : mono_object(obj)
{
}

mono_class_instance::mono_class_instance(MonoDomain *domain, MonoClass *cls)
    : mono_object(mono_object_new(domain, cls))
    , class_(cls)
{
    mono_runtime_object_init(object_);
}

mono_class_instance::~mono_class_instance() = default;

mono_class_instance::mono_class_instance(mono_class_instance &&o) = default;

auto mono_class_instance::operator=(mono_class_instance &&o) -> mono_class_instance & = default;

auto mono_class_instance::get_method(const std::string &name, int argc /*= 0*/) const -> mono_method
{
    return mono_method(class_, object_, name, argc);
}

} // namespace mono
} // namespace aeon
