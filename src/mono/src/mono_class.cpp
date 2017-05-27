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

#include <aeon/mono/mono_class.h>
#include <aeon/mono/mono_method.h>
#include <aeon/mono/mono_exception.h>
#include <aeon/mono/mono_class_field.h>

namespace aeon
{
namespace mono
{

mono_class::mono_class(MonoClass *cls)
    : class_(cls)
{
}

mono_class::mono_class(MonoImage *image, const std::string &name)
    : mono_class(image, "", name)
{
}

mono_class::mono_class(MonoImage *image, const std::string &name_space, const std::string &name)
    : class_(nullptr)
{
    class_ = mono_class_from_name(image, name_space.c_str(), name.c_str());

    if (!class_)
        throw mono_exception();
}

mono_class::~mono_class() = default;
mono_class::mono_class(mono_class &&o) = default;

auto mono_class::operator=(mono_class &&o) -> mono_class & = default;

mono_method mono_class::get_method(const std::string &name, int argc /*= 0*/) const
{
    return mono_method(class_, name, argc);
}

MonoClass *mono_class::get_mono_class_ptr() const
{
    return class_;
}

auto mono_class::get_field(const std::string &name) const -> mono_class_field
{
    return mono_class_field(get_mono_class_ptr(), name);
}

} // namespace mono
} // namespace aeon
