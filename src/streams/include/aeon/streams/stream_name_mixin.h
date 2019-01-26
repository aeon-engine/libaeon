// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/config.h>
#include <string>

namespace aeon::streams
{

class stream_name_mixin
{
public:
    stream_name_mixin()
        : name_{AEON_STREAM_DEFAULT_NAME}
        , has_name_{false}
    {
    }

    explicit stream_name_mixin(std::string name)
        : name_{std::move(name)}
        , has_name_{true}
    {
    }

    virtual ~stream_name_mixin() = default;

    stream_name_mixin(stream_name_mixin &&) noexcept = default;
    auto operator=(stream_name_mixin &&) noexcept -> stream_name_mixin & = default;

    stream_name_mixin(const stream_name_mixin &) = default;
    auto operator=(const stream_name_mixin &) -> stream_name_mixin & = default;

    const auto &get_name() const noexcept
    {
        return name_;
    }

    void set_name(std::string name)
    {
        name_ = std::move(name);
    }

    auto has_name() const noexcept
    {
        return has_name_;
    }

private:
    std::string name_;
    bool has_name_;
};

} // namespace aeon::streams
