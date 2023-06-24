// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/reflection/reflection_info.h>

namespace aeon::reflection
{

reflection_info::reflection_info() noexcept = default;

reflection_info::~reflection_info() = default;

auto reflection_info::get_field_type(const char *const name) const -> common::string_view
{
    const auto &field_info = get_field_info();
    for (const auto &field : field_info)
    {
        if (field.name() == name)
            return field.type();
    }

    throw reflection_exception{};
}

} // namespace aeon::reflection
