// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <concepts>
#include <utility>

namespace aeon::common
{

template <std::move_constructible T>
class unique_obj final
{
public:
    using element_type = T;

    unique_obj() noexcept = default;
    ~unique_obj() = default;

    unique_obj(unique_obj &&) noexcept = default;
    unique_obj &operator=(unique_obj &&) noexcept = default;

    unique_obj(const unique_obj &) noexcept = delete;
    auto operator=(const unique_obj &) noexcept -> unique_obj & = delete;

    unique_obj(element_type &&element) noexcept
        : value_{std::move(element)}
    {
    }

    auto operator=(element_type &&element) noexcept -> unique_obj &
    {
        value_ = std::move(element);
        return *this;
    }

    [[nodiscard]] auto get() noexcept -> element_type &
    {
        return value_;
    }

    [[nodiscard]] auto get() const noexcept -> const element_type &
    {
        return value_;
    }

    [[nodiscard]] auto operator*() noexcept -> element_type &
    {
        return get();
    }

    [[nodiscard]] auto operator*() const noexcept -> const element_type &
    {
        return get();
    }

    [[nodiscard]] auto operator->() const noexcept -> element_type *
    {
        return &value_;
    }

    [[nodiscard]] auto release() noexcept -> element_type
    {
        return std::move(value_);
    }

private:
    element_type value_;
};

} // namespace aeon::common
