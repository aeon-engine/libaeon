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

#include <aeon/mono/mono_object.h>
#include <aeon/mono/mono_class_field.h>
#include <aeon/common/type_traits.h>
#include <string>
#include <cassert>

namespace aeon
{
namespace mono
{

class mono_method;
class mono_class;
class mono_assembly;

class mono_class_instance : public mono_object
{
public:
    mono_class_instance();
    explicit mono_class_instance(MonoObject *obj);
    explicit mono_class_instance(mono_assembly *assembly, MonoObject *obj);
    explicit mono_class_instance(mono_assembly *assembly, MonoDomain *domain, MonoClass *cls);
    virtual ~mono_class_instance();

    mono_class_instance(mono_class_instance &&o);
    auto operator=(mono_class_instance &&o) -> mono_class_instance &;

    auto get_method(const std::string &name, int argc = 0) -> mono_method;

    template <typename function_signature_t>
    auto get_method_thunk(const std::string &name);

    auto get_class() -> mono_class;

    auto get_mono_class_ptr() -> MonoClass *;

    template <typename T>
    auto get_field_value(mono_class_field &field) const;

    template <typename T>
    void get_field_value(mono_class_field &field, T &val) const;

    template <typename T>
    void set_field_value(mono_class_field &field, T &val) const;

private:
    MonoClass *class_;
    mono_assembly *assembly_;
};

template <typename function_signature_t>
auto mono_class_instance::get_method_thunk(const std::string &name)
{
    constexpr auto arg_count = common::type_traits::function_signature_argument_count<function_signature_t>::value;
    auto func = get_method(name, arg_count);
    return func.template get_thunk<function_signature_t>();
}

template <typename T>
auto mono_class_instance::get_field_value(mono_class_field &field) const
{
    T val;
    get_field_value(field, val);
    return val;
}

template <typename T>
void mono_class_instance::get_field_value(mono_class_field &field, T &val) const
{
    assert(object_);
    assert(field.get_mono_class_field_ptr());
    mono_field_get_value(object_, field.get_mono_class_field_ptr(), reinterpret_cast<void *>(&val));
}

template <typename T>
void mono_class_instance::set_field_value(mono_class_field &field, T &val) const
{
    assert(object_);
    assert(field.get_mono_class_field_ptr());
    mono_field_set_value(object_, field.get_mono_class_field_ptr(), reinterpret_cast<void *>(&val));
}

} // namespace mono
} // namespace aeon
