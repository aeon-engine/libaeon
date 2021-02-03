// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/platform/modifier_keys_state.h>
#include <aeon/platform/platform_export.h>
#include <memory>

namespace aeon::platform
{

struct window_create_info;
class window;
class input_events;

class context
{
public:
    context() noexcept = default;
    virtual ~context() = default;

    context(const context &) noexcept = delete;
    auto operator=(const context &) noexcept -> context & = delete;

    context(context &&) noexcept = delete;
    auto operator=(context &&) noexcept -> context & = delete;

    [[nodiscard]] virtual auto create_window(const window_create_info &info) -> std::unique_ptr<window> = 0;
    virtual void poll_events() noexcept = 0;

    virtual void attach_input_listener(input_events &events) = 0;
    virtual void detach_input_listener(input_events &events) = 0;
    virtual void detach_all_input_listeners() = 0;

    [[nodiscard]] virtual auto modifier_keys_state() const noexcept -> modifier_keys_state = 0;
};

AEON_PLATFORM_EXPORT [[nodiscard]] auto create_context() -> std::unique_ptr<context>;

} // namespace aeon::platform
