// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::common
{

template <typename T>
class delay
{
public:
    using time_type = T;

    explicit delay(const T timeout)
        : current_time_{}
        , timeout_{timeout}
    {
    }

    ~delay() = default;

    delay(const delay &) noexcept = default;
    auto operator=(const delay &) noexcept -> delay & = default;

    delay(delay &&) noexcept = default;
    auto operator=(delay &&) noexcept -> delay & = default;

    void timeout(const time_type timeout) noexcept
    {
        reset();
        timeout_ = timeout;
    }

    [[nodiscard]] auto timeout() const noexcept -> time_type
    {
        return timeout_;
    }

    void reset() noexcept
    {
        current_time_ = {};
    }

    [[nodiscard]] auto expired(const time_type dt) noexcept -> bool
    {
        current_time_ += dt;

        if (current_time_ >= timeout_)
        {
            current_time_ = 0;
            return true;
        }

        return false;
    }

private:
    time_type current_time_;
    time_type timeout_;
};

} // namespace aeon::common
