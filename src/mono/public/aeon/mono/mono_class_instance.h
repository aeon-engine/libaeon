// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/mono/mono_object.h>
#include <aeon/mono/mono_class_field.h>
#include <aeon/common/type_traits.h>
#include <string>
#include <cassert>

namespace aeon::mono
{

class mono_method;
class mono_class;
class mono_assembly;

class mono_class_instance : public mono_object
{
public:
    mono_class_instance() noexcept;
    explicit mono_class_instance(MonoObject *obj) noexcept;
    explicit mono_class_instance(const mono_assembly *assembly, MonoObject *obj) noexcept;
    explicit mono_class_instance(const mono_assembly *assembly, MonoDomain *domain, MonoClass *cls) noexcept;
    virtual ~mono_class_instance();

    mono_class_instance(const mono_class_instance &) = delete;
    auto operator=(const mono_class_instance &) -> mono_class_instance & = delete;

    mono_class_instance(mono_class_instance &&) noexcept;
    auto operator=(mono_class_instance &&) noexcept -> mono_class_instance &;

    [[nodiscard]] auto get_method(const std::string &name, int argc = 0) const -> mono_method;

    template <typename function_signature_t>
    [[nodiscard]] auto get_method_thunk(const std::string &name) const;

    [[nodiscard]] auto get_class() const -> mono_class;

    [[nodiscard]] auto get_mono_class_ptr() const -> MonoClass *;

    template <typename T>
    [[nodiscard]] auto get_field_value(mono_class_field &field) const;

    template <typename T>
    void get_field_value(mono_class_field &field, T &val) const;

    template <typename T>
    void set_field_value(mono_class_field &field, T &val) const;

private:
    mutable MonoClass *class_;
    const mono_assembly *assembly_;
};

template <typename function_signature_t>
[[nodiscard]] auto mono_class_instance::get_method_thunk(const std::string &name) const
{
    constexpr auto arg_count = common::type_traits::function_signature_argument_count<function_signature_t>::value;
    auto func = get_method(name, arg_count);
    return func.template get_thunk<function_signature_t>();
}

template <typename T>
[[nodiscard]] auto mono_class_instance::get_field_value(mono_class_field &field) const
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

} // namespace aeon::mono
