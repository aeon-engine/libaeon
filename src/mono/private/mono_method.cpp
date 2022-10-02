// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/mono/mono_method.h>

namespace aeon::mono
{

mono_method::mono_method() noexcept
    : method_{nullptr}
    , object_{nullptr}
    , assembly_{nullptr}
{
}

mono_method::mono_method(const mono_assembly *assembly, MonoClass *cls, MonoObject *object, const std::string &name,
                         int argc) noexcept
    : method_{nullptr}
    , object_{object}
    , assembly_{assembly}
{
    method_ = mono_class_get_method_from_name(cls, name.c_str(), argc);
}

mono_method::~mono_method() = default;

mono_method::mono_method(mono_method &&) noexcept = default;
auto mono_method::operator=(mono_method &&) noexcept -> mono_method & = default;

} // namespace aeon::mono
