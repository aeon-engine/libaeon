// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/serial/serial_port.h>
#include <aeon/common/assert.h>
#include <aeon/common/scope_guard.h>

#if (defined(AEON_PLATFORM_OS_LINUX))
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif

namespace aeon::serial
{

namespace detail
{

#if (defined(AEON_PLATFORM_OS_WINDOWS))

static auto to_windows_parity(const parity parity) noexcept -> BYTE
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

static auto to_windows_stopbits(const stop_bits stop_bits) noexcept -> BYTE
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

#elif (defined(AEON_PLATFORM_OS_LINUX))

static auto to_posix_baud(const int baud) -> speed_t
{
    switch (baud)
    {
        case 50:
            return B50;
        case 75:
            return B75;
        case 110:
            return B110;
        case 134:
            return B134;
        case 150:
            return B150;
        case 200:
            return B200;
        case 300:
            return B300;
        case 600:
            return B600;
        case 1200:
            return B1200;
        case 1800:
            return B1800;
        case 2400:
            return B2400;
        case 4800:
            return B4800;
        case 9600:
            return B9600;
        case 19200:
            return B19200;
        case 38400:
            return B38400;
        case 57600:
            return B57600;
        case 115200:
            return B115200;
        case 230400:
            return B230400;
        case 460800:
            return B460800;
        case 500000:
            return B500000;
        case 576000:
            return B576000;
        case 921600:
            return B921600;
        case 1000000:
            return B1000000;
        case 1152000:
            return B1152000;
        case 1500000:
            return B1500000;
        case 2000000:
            return B2000000;
        case 2500000:
            return B2500000;
        case 3000000:
            return B3000000;
        case 3500000:
            return B3500000;
        case 4000000:
            return B4000000;
        default:
            throw serial_port_exception();
    }

    aeon_assert_fail("Error in parity enum.");
    return 0;
}

static auto to_posix_parity(const parity parity) -> tcflag_t
{
    switch (parity)
    {
        case parity::none:
            return ~PARENB;
        case parity::odd:
            return PARENB | PARODD;
        case parity::even:
            return PARENB | ~PARODD;
        case parity::mark:
        case parity::space:
            throw serial_port_exception();
    }

    aeon_assert_fail("Error in parity enum.");
    return 0;
}

static auto to_posix_stopbits(const stop_bits stop_bits) -> tcflag_t
{
    switch (stop_bits)
    {
        case stop_bits::one:
            return ~CSTOPB;
        case stop_bits::two:
            return CSTOPB;
        case stop_bits::one_and_half:
            throw serial_port_exception();
    }

    aeon_assert_fail("Error in stop_bits enum.");
    return 0;
}

static auto to_posix_byte_size(const int byte_size) -> tcflag_t
{
    switch (byte_size)
    {
        case 5:
            return CS5 | CLOCAL;
        case 6:
            return CS6 | CLOCAL;
        case 7:
            return CS7 | CLOCAL;
        case 8:
            return CS8 | CLOCAL;
        default:
            throw serial_port_exception();
    }

    aeon_assert_fail("Error in stop_bits enum.");
    return 0;
}

static void serial_port_close(const serial_port_handle handle)
{
    close(handle);
}

static auto serial_port_open(const char *device, const int baud, const int byte_size, const stop_bits stop_bits,
                             const parity parity) -> serial_port_handle
{
    const auto fd = open(device, O_RDWR);

    aeon_scope_fail
    {
        serial_port_close(fd);
    };

    struct termios settings;
    tcgetattr(fd, &settings);

    cfsetospeed(&settings, to_posix_baud(baud));
    settings.c_cflag &= to_posix_parity(parity);
    settings.c_cflag &= to_posix_stopbits(stop_bits);
    settings.c_cflag &= ~CSIZE;
    settings.c_cflag |= to_posix_byte_size(byte_size);
    settings.c_lflag = ICANON;
    settings.c_oflag &= ~OPOST;

    tcsetattr(fd, TCSANOW, &settings);
    tcflush(fd, TCOFLUSH);

    cfsetispeed(&settings, to_posix_baud(baud)); /* baud rate */
    tcflush(fd, TCIFLUSH);

    return fd;
}

static auto serial_port_read(const serial_port_handle handle, char *data, const std::size_t len) -> std::size_t
{
    const auto result = read(handle, data, len);

    if (result < 0)
        throw serial_port_exception();

    return static_cast<std::size_t>(result);
}

static auto serial_port_write(const serial_port_handle handle, const char *data, const std::size_t len) -> std::size_t
{
    const auto result = write(handle, data, len);

    if (result < 0)
        throw serial_port_exception();

    return static_cast<std::size_t>(result);
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

[[nodiscard]] auto serial_port::read(const std::size_t len) const -> common::string
{
    common::string value;
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

void serial_port::write(const common::string &data) const
{
    const auto len = write(data.data(), data.size());

    if (len != data.size())
        throw serial_port_exception();
}

} // namespace aeon::serial
