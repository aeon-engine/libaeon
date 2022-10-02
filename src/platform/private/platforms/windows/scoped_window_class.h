// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace aeon::platform
{

class scoped_window_class final
{
public:
    scoped_window_class();
    ~scoped_window_class();

    scoped_window_class(const scoped_window_class &) = delete;
    auto operator=(const scoped_window_class &) -> scoped_window_class & = delete;

    scoped_window_class(scoped_window_class &&) noexcept = delete;
    auto operator=(scoped_window_class &&) noexcept -> scoped_window_class & = delete;

    [[nodiscard]] auto classname() const noexcept -> const wchar_t *;

private:
    std::wstring classname_;
};

} // namespace aeon::platform
