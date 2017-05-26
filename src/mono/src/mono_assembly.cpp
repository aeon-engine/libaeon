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

#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_exception.h>
#include <aeon/mono/mono_class.h>
#include <aeon/mono/mono_class_instance.h>
#include <aeon/mono/mono_string.h>
#include <mono/metadata/assembly.h>

namespace aeon
{
namespace mono
{

mono_assembly::mono_assembly()
    : domain_(nullptr)
    , assembly_(nullptr)
    , image_(nullptr)
{
}

mono_assembly::mono_assembly(MonoDomain *domain, const std::string &path)
    : domain_(domain)
    , assembly_(nullptr)
    , image_(nullptr)
{
    assembly_ = mono_domain_assembly_open(domain, path.c_str());

    if (!assembly_)
        throw mono_exception();

    image_ = mono_assembly_get_image(assembly_);
}

mono_assembly::~mono_assembly() = default;

mono_assembly::mono_assembly(mono_assembly &&o) = default;

auto mono_assembly::operator=(mono_assembly &&o) -> mono_assembly & = default;

auto mono_assembly::get_class(const std::string &name) const -> mono_class
{
    return mono_class(image_, name);
}

auto mono_assembly::new_class_instance(const mono_class &cls) const -> mono_class_instance
{
    return mono_class_instance(domain_, cls.get_mono_class_ptr());
}

auto mono_assembly::new_string(const std::string &str) const -> mono_string
{
    return mono_string(domain_, str);
}

} // namespace mono
} // namespace aeon
