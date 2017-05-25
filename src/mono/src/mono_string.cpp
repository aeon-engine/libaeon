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

#include <aeon/mono/mono_string.h>

namespace aeon
{
namespace mono
{

mono_string::mono_string(MonoString *mono_string)
    : mono_object(mono_object_get_domain(reinterpret_cast<MonoObject *>(mono_string)))
    , object_(mono_string)
    , string_()
{
    // TODO: This could be probably optimized by doing no additional
    // allocation though mono_string_chars and mono_string_length.
    auto raw_utf8_str = mono_string_to_utf8(mono_string);
    string_ = raw_utf8_str;
    mono_free(raw_utf8_str);
}

mono_string::mono_string(MonoDomain *domain, const std::string &str)
    : mono_object(domain)
    , object_(nullptr)
    , string_(str)
{
    object_ = mono_string_new(domain, str.c_str());
}

mono_string::~mono_string() = default;

mono_string::mono_string(mono_string &&o) = default;

auto mono_string::operator=(mono_string &&o) -> mono_string & = default;

auto mono_string::operator=(const std::string &str) -> mono_string &
{
    string_ = str;
    object_ = mono_string_new(domain_, str.c_str());
    return *this;
}

mono_string::operator std::string() const
{
    return string_;
}

auto mono_string::get_mono_object() const -> MonoObject *
{
    return reinterpret_cast<MonoObject *>(object_);
}

} // namespace mono
} // namespace aeon
