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
    reset_color();

#if (AEON_PLATFORM_OS_WINDOWS)
    // TODO Implement for windows.
#else
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
    // TODO Implement for windows.
#else
    std::cout << AEON_TERM_COLOR_RESET;
#endif
}

} // namespace streams
} // namespace aeon
