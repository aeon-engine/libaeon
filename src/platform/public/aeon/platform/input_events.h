// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <cstdint>

namespace aeon::platform
{

class context;

enum class mouse_button
{
    left,
    right,
    middle,
    button4,
    button5,
    unknown
};

class input_events
{
public:
    input_events() noexcept = default;
    virtual ~input_events() = default;

    input_events(const input_events &) noexcept = default;
    auto operator=(const input_events &) noexcept -> input_events & = default;

    input_events(input_events &&) noexcept = default;
    auto operator=(input_events &&) noexcept -> input_events & = default;

    virtual void on_key_down([[maybe_unused]] const context &context, [[maybe_unused]] const std::uint32_t key_code,
                             [[maybe_unused]] const std::uint32_t character_code, [[maybe_unused]] const bool repeated)
    {
    }

    virtual void on_key_up([[maybe_unused]] const context &context, [[maybe_unused]] const std::uint32_t key_code,
                           [[maybe_unused]] const std::uint32_t character_code, [[maybe_unused]] const bool repeated)
    {
    }

    virtual void on_mouse_move([[maybe_unused]] const context &context,
                               [[maybe_unused]] const math::vector2<std::int32_t> position)
    {
    }

    virtual void on_mouse_down([[maybe_unused]] const context &context, [[maybe_unused]] const mouse_button button)
    {
    }

    virtual void on_mouse_up([[maybe_unused]] const context &context, [[maybe_unused]] const mouse_button button)
    {
    }

    virtual void on_mouse_scroll([[maybe_unused]] const context &context, [[maybe_unused]] const std::int32_t delta)
    {
    }
};

} // namespace aeon::platform
