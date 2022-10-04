// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/platform/window.h>
#include <aeon/platform/window_events.h>
#include <aeon/common/listener_subject.h>

namespace aeon::platform
{

class base_window : public window
{
public:
    base_window() noexcept;
    ~base_window() override;

    base_window(const base_window &) noexcept = delete;
    auto operator=(const base_window &) noexcept -> base_window & = delete;

    base_window(base_window &&) noexcept = delete;
    auto operator=(base_window &&) noexcept -> base_window & = delete;

    void attach_window_listener(window_events &events) override;
    void detach_window_listener(window_events &events) override;
    void detach_all_window_listeners() override;

protected:
    [[nodiscard]] auto &window_listeners() noexcept
    {
        return window_listeners_;
    }

    [[nodiscard]] const auto &window_listeners() const noexcept
    {
        return window_listeners_;
    }

private:
    common::listener_subject<window_events> window_listeners_;
};

} // namespace aeon::platform
