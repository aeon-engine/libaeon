// Copyright (c) 2012-2019 Robin Degen

#include <aeon/mono/mono_class.h>
#include <aeon/mono/mono_method.h>
#include <aeon/mono/mono_exception.h>
#include <aeon/mono/mono_class_field.h>
#include <cassert>

namespace aeon::mono
{

mono_class::mono_class() noexcept
    : class_{nullptr}
    , assembly_{nullptr}
{
}

mono_class::mono_class(const mono_assembly *assembly, MonoClass *cls) noexcept
    : class_{cls}
    , assembly_{assembly}
{
}

mono_class::mono_class(const mono_assembly *assembly, MonoImage *image, const std::string &name)
    : mono_class{assembly, image, "", name}
{
}

mono_class::mono_class(const mono_assembly *assembly, MonoImage *image, const std::string &name_space,
                       const std::string &name)
    : class_{nullptr}
    , assembly_{assembly}
{
    class_ = mono_class_from_name(image, name_space.c_str(), name.c_str());

    if (!class_)
        throw mono_exception{};
}

mono_class::~mono_class() = default;
mono_class::mono_class(mono_class &&o) noexcept = default;

auto mono_class::operator=(mono_class &&o) noexcept -> mono_class & = default;

[[nodiscard]] auto mono_class::get_static_function(const std::string &name, int argc /*= 0*/) const
    -> mono_static_function
{
    assert(class_);
    assert(assembly_);
    return mono_static_function{assembly_, class_, name, argc};
}

[[nodiscard]] auto mono_class::get_mono_class_ptr() const noexcept -> MonoClass *
{
    assert(class_);
    return class_;
}

[[nodiscard]] auto mono_class::get_field(const std::string &name) const -> mono_class_field
{
    return mono_class_field{get_mono_class_ptr(), name};
}

} // namespace aeon::mono
