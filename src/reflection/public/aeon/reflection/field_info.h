// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/reflection/reflection_object.h>
#include <string_view>
#include <cstddef>

namespace aeon::reflection
{

class field_info final
{
public:
    field_info(const std::string_view name, const std::string_view type, const std::ptrdiff_t offset)
        : name_{name}
        , type_{type}
        , offset_{offset}
    {
    }

    ~field_info() = default;

    field_info(const field_info &) noexcept = default;
    auto operator=(const field_info &) noexcept -> field_info & = default;

    field_info(field_info &&) noexcept = default;
    auto operator=(field_info &&) noexcept -> field_info & = default;

    [[nodiscard]] auto name() const noexcept
    {
        return name_;
    }

    [[nodiscard]] auto type() const noexcept
    {
        return type_;
    }

    [[nodiscard]] auto offset() const noexcept
    {
        return offset_;
    }

    template <typename U, reflection_object_implementation T>
    [[nodiscard]] auto get(const T &instance) const noexcept -> const U &
    {
        return *(reinterpret_cast<const U *>(reinterpret_cast<const std::uint8_t *>(&instance) + offset_));
    }

    template <typename U, reflection_object_implementation T>
    void set(T &instance, const U &value) const
    {
        *(reinterpret_cast<U *>(reinterpret_cast<std::uint8_t *>(&instance) + offset_)) = value;
    }

private:
    std::string_view name_;
    std::string_view type_;
    std::ptrdiff_t offset_;
};

} // namespace aeon::reflection
