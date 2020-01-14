// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/common/platform.h>
#include <exception>
#include <string>

#if (defined(AEON_PLATFORM_OS_WINDOWS))
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace aeon::serial
{

class serial_port_exception : public std::exception
{
};

#if (defined(AEON_PLATFORM_OS_WINDOWS))
using serial_port_handle = HANDLE;
#elif (defined(AEON_PLATFORM_OS_LINUX))
using serial_port_handle = int;
#endif

enum class stop_bits
{
    one,
    one_and_half,
    two
};

enum class parity
{
    none,
    odd,
    even,
    mark,
    space
};

class serial_port
{
public:
    explicit serial_port(const char *device, const int baud, const int byte_size = 8,
                         const stop_bits stop_bits = stop_bits::one, const parity parity = parity::none);
    ~serial_port();

    serial_port(const serial_port &) = delete;
    auto operator=(const serial_port &) -> serial_port & = delete;

    serial_port(serial_port &&) noexcept = delete;
    auto operator=(serial_port &&) noexcept -> serial_port & = delete;

    void disconnect();

    auto read(char *data, const std::size_t len) const -> std::size_t;
    [[nodiscard]] auto read(const std::size_t len) const -> std::string;

    auto write(const char *data, const std::size_t len) const -> std::size_t;
    void write(const std::string &data) const;

private:
    serial_port_handle handle_;
};

} // namespace aeon::serial
