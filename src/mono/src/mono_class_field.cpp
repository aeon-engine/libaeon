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

#include <aeon/mono/mono_class_field.h>
#include <aeon/mono/mono_class.h>
#include <cassert>

namespace aeon
{
namespace mono
{

mono_class_field::mono_class_field()
    : field_(nullptr)
{
}

mono_class_field::mono_class_field(mono_class &monoclass, const std::string &name)
    : mono_class_field(monoclass.get_mono_class_ptr(), name)
{
}

mono_class_field::mono_class_field(MonoClass *monoclass, const std::string &name)
    : field_(mono_class_get_field_from_name(monoclass, name.c_str()))
{
    assert(field_);
}

mono_class_field::~mono_class_field() = default;
mono_class_field::mono_class_field(mono_class_field &&o) = default;

auto mono_class_field::operator=(mono_class_field &&o) -> mono_class_field & = default;

auto mono_class_field::get_mono_class_field_ptr() const -> MonoClassField *
{
    return field_;
}

} // namespace mono
} // namespace aeon
