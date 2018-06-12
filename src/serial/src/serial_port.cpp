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

#include <aeon/serial/serial_port.h>
#include <aeon/common/assert.h>
#include <aeon/common/scope_guard.h>

namespace aeon::serial
{

namespace detail
{

auto to_windows_parity(const parity parity) noexcept -> BYTE
{
    switch (parity)
    {
        case parity::none:
            return 0;
        case parity::odd:
            return 1;
        case parity::even:
            return 2;
        case parity::mark:
            return 3;
        case parity::space:
            return 4;
    }

    aeon_assert_fail("Error in parity enum.");
    return 0;
}

auto to_windows_stopbits(const stop_bits stop_bits) noexcept -> BYTE
{
    switch (stop_bits)
    {
        case stop_bits::one:
            return 0;
        case stop_bits::one_and_half:
            return 1;
        case stop_bits::two:
            return 2;
    }

    aeon_assert_fail("Error in stop_bits enum.");
    return 0;
}

#if (defined(AEON_PLATFORM_OS_WINDOWS))

static void serial_port_close(const serial_port_handle handle)
{
    CloseHandle(handle);
}

static auto serial_port_open(const char *device, const int baud, const int byte_size, const stop_bits stop_bits,
                             const parity parity) -> serial_port_handle
{
    const auto handle = CreateFile(device, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);

    if (handle == nullptr)
        throw serial_port_exception();

    aeon_scope_fail
    {
        serial_port_close(handle);
    };

    DCB config{};
    config.DCBlength = sizeof(DCB);

    if (!GetCommState(handle, &config))
        throw serial_port_exception();

    config.BaudRate = baud;
    config.fParity = detail::to_windows_parity(parity);
    config.StopBits = detail::to_windows_stopbits(stop_bits);
    config.ByteSize = static_cast<BYTE>(byte_size);
    config.fRtsControl = RTS_CONTROL_ENABLE; // TODO
    config.fDtrControl = DTR_CONTROL_ENABLE;

    if (!SetCommState(handle, &config))
        throw serial_port_exception();

    COMMTIMEOUTS timeouts{};

    timeouts.ReadIntervalTimeout = 2000;
    timeouts.ReadTotalTimeoutMultiplier = 2000;
    timeouts.ReadTotalTimeoutConstant = 2000;
    timeouts.WriteTotalTimeoutMultiplier = 2000;
    timeouts.WriteTotalTimeoutConstant = 2000;

    if (!SetCommTimeouts(handle, &timeouts))
        throw serial_port_exception();

    return handle;
}

static auto serial_port_read(const serial_port_handle handle, char *data, const std::size_t len) -> std::size_t
{
    DWORD actual_len = {};

    if (!ReadFile(handle, data, static_cast<DWORD>(len), &actual_len, nullptr))
        throw serial_port_exception();

    return static_cast<std::size_t>(actual_len);
}

static auto serial_port_write(const serial_port_handle handle, const char *data, const std::size_t len) -> std::size_t
{
    DWORD actual_len = {};

    if (!WriteFile(handle, data, static_cast<DWORD>(len), &actual_len, nullptr))
        throw serial_port_exception();

    return static_cast<std::size_t>(actual_len);
}

#endif

} // namespace detail

serial_port::serial_port(const char *device, const int baud, const int byte_size, const stop_bits stop_bits,
                         const parity parity)
    : handle_{detail::serial_port_open(device, baud, byte_size, stop_bits, parity)}
{
}

serial_port::~serial_port()
{
    disconnect();
}

void serial_port::disconnect()
{
    if (!handle_)
        return;

    detail::serial_port_close(handle_);

    handle_ = {};
}

auto serial_port::read(char *data, const std::size_t len) const -> std::size_t
{
    if (!handle_)
        throw serial_port_exception();

    return detail::serial_port_read(handle_, data, len);
}

auto serial_port::read(const std::size_t len) const -> std::string
{
    std::string value;
    value.resize(len);

    const auto actual_len = read(value.data(), len);
    value.resize(actual_len);

    return value;
}

auto serial_port::write(const char *data, const std::size_t len) const -> std::size_t
{
    if (!handle_)
        throw serial_port_exception();

    return detail::serial_port_write(handle_, data, len);
}

void serial_port::write(const std::string &data) const
{
    const auto len = write(data.data(), data.size());

    if (len != data.size())
        throw serial_port_exception();
}

} // namespace aeon::serial
