// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/streams/devices/device.h>
#include <aeon/streams/tags.h>
#include <aeon/common/platform.h>
#include <cstdio>
#include <iostream>

namespace aeon::streams
{

enum class color
{
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
};

enum class weight
{
    normal,
    bold
};

class stdio_device : public device
{
public:
    struct category : input, output, has_eof, flushable
    {
    };

    explicit stdio_device() noexcept;

    stdio_device(stdio_device &&) noexcept = default;
    auto operator=(stdio_device &&) noexcept -> stdio_device & = default;

    stdio_device(const stdio_device &) noexcept = default;
    auto operator=(const stdio_device &) noexcept -> stdio_device & = default;

    ~stdio_device() = default;

    auto write(const char *data, const std::streamsize size) const noexcept -> std::streamsize;

    auto read(char *data, const std::streamsize size) const noexcept -> std::streamsize;

    [[nodiscard]] auto eof() const noexcept -> bool;

    void flush() const noexcept;

    void set_color(const color c, const weight w = weight::normal) const noexcept;

    void reset_color() const noexcept;

protected:
#if (AEON_PLATFORM_OS_WINDOWS)
    void *std_handle_;
    unsigned short default_colors_;
#endif
};

inline auto stdio_device::write(const char *data, const std::streamsize size) const noexcept -> std::streamsize
{
    return static_cast<std::size_t>(fwrite(data, 1, size, stdout));
}

inline auto stdio_device::read(char *data, const std::streamsize size) const noexcept -> std::streamsize
{
    return static_cast<std::size_t>(fread(data, 1, size, stdin));
}

[[nodiscard]] inline auto stdio_device::eof() const noexcept -> bool
{
    return feof(stdin) != 0;
}

inline void stdio_device::flush() const noexcept
{
    fflush(stdout);
}

} // namespace aeon::streams
