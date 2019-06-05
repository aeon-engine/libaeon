// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/mono/mono_static_function.h>

namespace aeon::mono
{

mono_static_function::mono_static_function() noexcept
    : method_{nullptr}
    , assembly_{nullptr}
{
}

mono_static_function::mono_static_function(const mono_assembly *assembly, MonoClass *cls, const std::string &name,
                                           int argc) noexcept
    : method_{nullptr}
    , assembly_{assembly}
{
    method_ = mono_class_get_method_from_name(cls, name.c_str(), argc);
}

mono_static_function::~mono_static_function() = default;

mono_static_function::mono_static_function(mono_static_function &&o) noexcept = default;

auto mono_static_function::operator=(mono_static_function &&o) noexcept -> mono_static_function & = default;

} // namespace aeon::mono
