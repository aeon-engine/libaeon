// Copyright (c) 2012-2019 Robin Degen

#include <aeon/mono/mono_class_field.h>
#include <aeon/mono/mono_class.h>
#include <cassert>

namespace aeon::mono
{

mono_class_field::mono_class_field() noexcept
    : field_{nullptr}
{
}

mono_class_field::mono_class_field(mono_class &monoclass, const std::string &name) noexcept
    : mono_class_field{monoclass.get_mono_class_ptr(), name}
{
}

mono_class_field::mono_class_field(MonoClass *monoclass, const std::string &name) noexcept
    : field_{mono_class_get_field_from_name(monoclass, name.c_str())}
{
    assert(field_);
}

mono_class_field::~mono_class_field() = default;
mono_class_field::mono_class_field(mono_class_field &&o) noexcept = default;

auto mono_class_field::operator=(mono_class_field &&o) noexcept -> mono_class_field & = default;

auto mono_class_field::get_mono_class_field_ptr() const noexcept -> MonoClassField *
{
    return field_;
}

} // namespace aeon::mono
