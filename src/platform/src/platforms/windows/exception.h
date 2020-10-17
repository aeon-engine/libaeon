// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/platform/exception.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace aeon::platform
{

class windows_platform_exception final : public platform_exception
{
public:
    explicit windows_platform_exception(std::u8string msg) noexcept
        : platform_exception{std::move(msg)}
        , error_{0}
    {
    }

    explicit windows_platform_exception(const DWORD error, std::u8string msg) noexcept
        : platform_exception{std::move(msg)}
        , error_{error}
    {
    }

    ~windows_platform_exception() = default;

    windows_platform_exception(const windows_platform_exception &) = default;
    auto operator=(const windows_platform_exception &) -> windows_platform_exception & = default;

    windows_platform_exception(windows_platform_exception &&) noexcept = default;
    auto operator=(windows_platform_exception &&) noexcept -> windows_platform_exception & = default;

    [[nodiscard]] auto error() const noexcept
    {
        return error_;
    }

private:
    DWORD error_;
};

} // namespace aeon::platform
