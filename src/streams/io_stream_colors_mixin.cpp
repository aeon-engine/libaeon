#include <aeon/streams.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

namespace aeon
{
namespace streams
{

void io_stream_colors_mixin::set_color(color c, weight w /*= weight::normal*/)
{
#if (AEON_PLATFORM_OS_WINDOWS)
    // TODO Implement for windows.
    static HANDLE std_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    int intensity = 0;
    if (w == weight::bold)
        intensity = FOREGROUND_INTENSITY;

    switch (c)
    {
    case color::black:
        SetConsoleTextAttribute(std_handle, 0);
        break;
    case color::red:
        SetConsoleTextAttribute(std_handle, FOREGROUND_RED | intensity);
        break;
    case color::green:
        SetConsoleTextAttribute(std_handle, FOREGROUND_GREEN | intensity);
        break;
    case color::yellow:
        SetConsoleTextAttribute(std_handle, FOREGROUND_RED | FOREGROUND_GREEN | intensity);
        break;
    case color::blue:
        SetConsoleTextAttribute(std_handle, FOREGROUND_BLUE | intensity);
        break;
    case color::magenta:
        SetConsoleTextAttribute(std_handle, FOREGROUND_RED | FOREGROUND_BLUE | intensity);
        break;
    case color::cyan:
        SetConsoleTextAttribute(std_handle, FOREGROUND_GREEN | FOREGROUND_BLUE | intensity);
        break;
    case color::white:
        SetConsoleTextAttribute(std_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | intensity);
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

void io_stream_colors_mixin::reset_color()
{
#if (AEON_PLATFORM_OS_WINDOWS)
    static HANDLE std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(std_handle, 0);
#else
    std::cout << AEON_TERM_COLOR_RESET;
#endif
}

} // namespace streams
} // namespace aeon
