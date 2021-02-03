// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/mono/mono_class_instance.h>
#include <aeon/mono/mono_method.h>
#include <aeon/mono/mono_class.h>
#include <cassert>

namespace aeon::mono
{

mono_class_instance::mono_class_instance() noexcept
    : mono_object{}
    , class_{nullptr}
    , assembly_{nullptr}
{
}

mono_class_instance::mono_class_instance(MonoObject *obj) noexcept
    : mono_class_instance{nullptr, obj}
{
}

mono_class_instance::mono_class_instance(const mono_assembly *assembly, MonoObject *obj) noexcept
    : mono_object{obj}
    , class_{nullptr}
    , assembly_{assembly}
{
}

mono_class_instance::mono_class_instance(const mono_assembly *assembly, MonoDomain *domain, MonoClass *cls) noexcept
    : mono_object{mono_object_new(domain, cls)}
    , class_{cls}
    , assembly_{assembly}
{
    mono_runtime_object_init(object_);
}

mono_class_instance::~mono_class_instance() = default;

mono_class_instance::mono_class_instance(mono_class_instance &&) noexcept = default;
auto mono_class_instance::operator=(mono_class_instance &&) noexcept -> mono_class_instance & = default;

[[nodiscard]] auto mono_class_instance::get_method(const std::string &name, int argc /*= 0*/) const -> mono_method
{
    assert(assembly_);
    assert(object_);
    return mono_method{assembly_, get_mono_class_ptr(), object_, name, argc};
}

[[nodiscard]] auto mono_class_instance::get_class() const -> mono_class
{
    return mono_class{assembly_, get_mono_class_ptr()};
}

[[nodiscard]] auto mono_class_instance::get_mono_class_ptr() const -> MonoClass *
{
    assert(object_);

    if (!class_)
        class_ = mono_object_get_class(object_);

    return class_;
}

} // namespace aeon::mono
