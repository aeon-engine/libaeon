// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

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

private:
    std::string_view name_;
    std::string_view type_;
    std::ptrdiff_t offset_;
};

} // namespace aeon::reflection
