// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/common/platform.h>
#include <chrono>

namespace aeon::common
{

class timer
{
public:
    using clock_type = std::chrono::high_resolution_clock;

    timer() noexcept
    {
        reset();
    }

    ~timer() = default;

    timer(timer &&) = delete;
    auto operator=(timer &&) -> timer & = delete;

    timer(const timer &) = delete;
    auto operator=(const timer &) -> timer & = delete;

    void reset() noexcept
    {
        start_time_ = clock_type::now();
    }

    template <typename T = float>
    [[nodiscard]] auto get_time_difference() const noexcept
    {
        const auto now = clock_type::now();
        const std::chrono::duration<T> elapsed_seconds = now - start_time_;
        return elapsed_seconds.count();
    }

private:
    std::chrono::time_point<clock_type> start_time_;
};

} // namespace aeon::common
