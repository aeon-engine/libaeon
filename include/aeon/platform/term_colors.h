/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

/* Color codes for colored console output. Can be used like this:
 * std::cout << AEON_TERM_COLOR_BLUE << "Blue! "
 *     << AEON_TERM_COLOR_RESET << "Normal!" << std::endl;
 */

// TODO: Just checking for windows may not be sufficient.
#if (!AEON_PLATFORM_OS_WINDOWS)
#  define AEON_TERM_COLOR_RESET         "\033[0m"
#  define AEON_TERM_COLOR_BOLD          "\033[1m"
#  define AEON_TERM_COLOR_BLACK         "\033[30m"
#  define AEON_TERM_COLOR_RED           "\033[31m"
#  define AEON_TERM_COLOR_GREEN         "\033[32m"
#  define AEON_TERM_COLOR_YELLOW        "\033[33m"
#  define AEON_TERM_COLOR_BLUE          "\033[34m"
#  define AEON_TERM_COLOR_MAGENTA       "\033[35m"
#  define AEON_TERM_COLOR_CYAN          "\033[36m"
#  define AEON_TERM_COLOR_WHITE         "\033[37m"
#endif // AEON_UTILITY_OS_WINDOWS
