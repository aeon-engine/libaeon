// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/deprecated.h>
#include <exception>

namespace aeon::common
{

class optional_value_exception : public std::exception
{
};

template <typename T>
AEON_DEPRECATED("Replaced by std::optional.")
class optional
{
public:
    optional()
        : value_{}
        , has_value_{false}
    {
    }

    optional(T val)
        : value_{std::move(val)}
        , has_value_{true}
    {
    }

    optional(optional &&) noexcept = default;
    auto operator=(optional &&) noexcept -> optional & = default;

    optional(const optional &) = default;
    auto operator=(const optional &) -> optional & = default;

    bool has_value() const noexcept
    {
        return has_value_;
    }

    const T &get_value() const
    {
        if (!has_value_)
            throw optional_value_exception();

        return value_;
    }

    void reset() noexcept
    {
        has_value_ = false;
    }

    operator T() const
    {
        if (!has_value_)
            throw optional_value_exception();

        return value_;
    }

    auto &operator=(const T &val)
    {
        value_ = val;
        has_value_ = true;
        return *this;
    }

private:
    T value_;
    bool has_value_;
};

} // namespace aeon::common
