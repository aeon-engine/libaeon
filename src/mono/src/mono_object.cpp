// Copyright (c) 2012-2019 Robin Degen

#include <aeon/mono/mono_object.h>

namespace aeon::mono
{

mono_object::mono_object() noexcept
    : object_{nullptr}
{
}

mono_object::mono_object(MonoObject *object) noexcept
    : object_{object}
{
}

mono_object::~mono_object() = default;

[[nodiscard]] auto mono_object::get_mono_object() const noexcept -> MonoObject *
{
    return object_;
}

} // namespace aeon::mono
