// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <stdexcept>
#include <string>

namespace aeon::gl
{

class gl_exception : public std::exception
{
public:
    explicit gl_exception(std::u8string msg) noexcept
        : msg_{std::move(msg)}
    {
    }

    ~gl_exception() = default;

    gl_exception(const gl_exception &) = default;
    auto operator=(const gl_exception &) -> gl_exception & = default;

    gl_exception(gl_exception &&) noexcept = default;
    auto operator=(gl_exception &&) noexcept -> gl_exception & = default;

    [[nodiscard]] const auto &message() const noexcept
    {
        return msg_;
    }

private:
    std::u8string msg_;
};

} // namespace aeon::gl
