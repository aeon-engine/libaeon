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

#if (defined(AEON_PLATFORM_OS_WINDOWS))
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdexcept>
#else
#include <chrono>
#endif

namespace aeon::common
{

class timer
{
public:
    timer()
    {
#if (defined(AEON_PLATFORM_OS_WINDOWS))
        QueryPerformanceFrequency(&frequency_);
#endif
        reset();
    }

    ~timer() = default;

    timer(timer &&) = delete;
    auto operator=(timer &&) -> timer & = delete;

    timer(const timer &) = delete;
    auto operator=(const timer &) -> timer & = delete;

    void reset() noexcept
    {
#if (defined(AEON_PLATFORM_OS_WINDOWS))
        QueryPerformanceCounter(&start_time_);
#else
        start_time_ = std::chrono::system_clock::now();
#endif
    }

    auto get_time_difference() const noexcept -> double
    {
#if (defined(AEON_PLATFORM_OS_WINDOWS))
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return static_cast<float>(now.QuadPart - start_time_.QuadPart) / frequency_.QuadPart;
#else
        const auto now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - start_time_;
        return elapsed_seconds.count();
#endif
    }

private:
#if (defined(AEON_PLATFORM_OS_WINDOWS))
    LARGE_INTEGER frequency_;
    LARGE_INTEGER start_time_;
#else
    std::chrono::time_point<std::chrono::system_clock> start_time_;
#endif
};

} // namespace aeon::common
