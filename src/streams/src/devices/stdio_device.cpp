// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/streams/devices/stdio_device.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <aeon/common/term_colors.h>
#include <iostream>
#endif

namespace aeon::streams
{

stdio_device::stdio_device() noexcept
#if (AEON_PLATFORM_OS_WINDOWS)
    : std_handle_{GetStdHandle(STD_OUTPUT_HANDLE)}
    , default_colors_(0)
#endif
{
#if (AEON_PLATFORM_OS_WINDOWS)
    CONSOLE_SCREEN_BUFFER_INFO info{};
    GetConsoleScreenBufferInfo(std_handle_, &info);
    default_colors_ = info.wAttributes;
#endif
}

void stdio_device::set_color(const color c, const weight w) const noexcept
{
#if (AEON_PLATFORM_OS_WINDOWS)
    int intensity = 0;
    if (w == weight::bold)
        intensity = FOREGROUND_INTENSITY;

    switch (c)
    {
        case color::black:
            SetConsoleTextAttribute(std_handle_, 0);
            break;
        case color::red:
            SetConsoleTextAttribute(std_handle_, static_cast<WORD>(FOREGROUND_RED | intensity));
            break;
        case color::green:
            SetConsoleTextAttribute(std_handle_, static_cast<WORD>(FOREGROUND_GREEN | intensity));
            break;
        case color::yellow:
            SetConsoleTextAttribute(std_handle_, static_cast<WORD>(FOREGROUND_RED | FOREGROUND_GREEN | intensity));
            break;
        case color::blue:
            SetConsoleTextAttribute(std_handle_, static_cast<WORD>(FOREGROUND_BLUE | intensity));
            break;
        case color::magenta:
            SetConsoleTextAttribute(std_handle_, static_cast<WORD>(FOREGROUND_RED | FOREGROUND_BLUE | intensity));
            break;
        case color::cyan:
            SetConsoleTextAttribute(std_handle_, static_cast<WORD>(FOREGROUND_GREEN | FOREGROUND_BLUE | intensity));
            break;
        case color::white:
            SetConsoleTextAttribute(std_handle_,
                                    static_cast<WORD>(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | intensity));
            break;
    }
#else
    reset_color();

    if (w == weight::bold)
    {
        std::cout << AEON_TERM_COLOR_BOLD;
    }

    switch (c)
    {
        case color::black:
            std::cout << AEON_TERM_COLOR_BLACK;
            break;
        case color::red:
            std::cout << AEON_TERM_COLOR_RED;
            break;
        case color::green:
            std::cout << AEON_TERM_COLOR_GREEN;
            break;
        case color::yellow:
            std::cout << AEON_TERM_COLOR_YELLOW;
            break;
        case color::blue:
            std::cout << AEON_TERM_COLOR_BLUE;
            break;
        case color::magenta:
            std::cout << AEON_TERM_COLOR_MAGENTA;
            break;
        case color::cyan:
            std::cout << AEON_TERM_COLOR_CYAN;
            break;
        case color::white:
            std::cout << AEON_TERM_COLOR_WHITE;
            break;
    }
#endif
}

void stdio_device::reset_color() const noexcept
{
#if (AEON_PLATFORM_OS_WINDOWS)
    SetConsoleTextAttribute(std_handle_, default_colors_);
#else
    std::cout << AEON_TERM_COLOR_RESET;
#endif
}

} // namespace aeon::streams
