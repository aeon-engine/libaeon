// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

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

    [[nodiscard]] auto get_time_difference() const noexcept -> double
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
