/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
    auto read(const std::size_t len) const -> std::string;

    auto write(const char *data, const std::size_t len) const -> std::size_t;
    void write(const std::string &data) const;

private:
    serial_port_handle handle_;
};

} // namespace aeon::serial
