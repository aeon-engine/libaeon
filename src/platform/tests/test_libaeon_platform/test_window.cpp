// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/platform/window.h>
#include <aeon/platform/window_create_info.h>
#include <aeon/platform/window_events.h>
#include <aeon/platform/input_events.h>
#include <aeon/math/vector2_stream.h>
#include <aeon/math/size2d_stream.h>
#include <aeon/platform/context.h>
#include <gtest/gtest.h>

using namespace aeon;

class test_window_events final : public platform::window_events
{
public:
    test_window_events() noexcept = default;
    ~test_window_events() final = default;

    test_window_events(const test_window_events &) noexcept = default;
    auto operator=(const test_window_events &) noexcept -> test_window_events & = default;

    test_window_events(test_window_events &&) noexcept = default;
    auto operator=(test_window_events &&) noexcept -> test_window_events & = default;

    void on_window_position_changed([[maybe_unused]] const platform::context &context,
                                    const math::vector2<std::int32_t> &position) noexcept final
    {
        std::cout << "Move: " << position << std::endl;
    }

    void on_window_size_changed([[maybe_unused]] const platform::context &context,
                                const math::size2d<std::int32_t> &size) noexcept final
    {
        std::cout << "Resize: " << size << std::endl;
    }

    void on_window_focus_changed([[maybe_unused]] const platform::context &context, const bool focus) noexcept final
    {
        std::cout << "Focus: " << focus << std::endl;
    }

    void on_window_closed([[maybe_unused]] const platform::context &context) noexcept final
    {
        std::cout << "Closed.\n";
    }
};

class test_input_events final : public platform::input_events
{
public:
    test_input_events() noexcept = default;
    ~test_input_events() final = default;

    test_input_events(const test_input_events &) noexcept = default;
    auto operator=(const test_input_events &) noexcept -> test_input_events & = default;

    test_input_events(test_input_events &&) noexcept = default;
    auto operator=(test_input_events &&) noexcept -> test_input_events & = default;

    void on_key_down([[maybe_unused]] const platform::context &context, const std::uint32_t key_code,
                     const std::uint32_t character_code, const bool repeated) final
    {
        std::cout << "KEY DOWN: keycode: " << key_code << " charcode: " << character_code << " repeated: " << repeated
                  << '\n';
        std::cout << context.modifier_keys_state().caps_lock_enabled() << ' '
                  << context.modifier_keys_state().num_lock_enabled() << '\n';
    }

    void on_key_up([[maybe_unused]] const platform::context &context, const std::uint32_t key_code,
                   const std::uint32_t character_code, const bool repeated) final
    {
        std::cout << "KEY UP:   keycode: " << key_code << " charcode: " << character_code << " repeated: " << repeated
                  << '\n';
        std::cout << context.modifier_keys_state().caps_lock_enabled() << ' '
                  << context.modifier_keys_state().num_lock_enabled() << '\n';
    }

    void on_mouse_move([[maybe_unused]] const platform::context &context,
                       [[maybe_unused]] const math::vector2<std::int32_t> position) final
    {
        std::cout << "Mouse Move: " << position << '\n';
    }

    void on_mouse_down([[maybe_unused]] const platform::context &context,
                       [[maybe_unused]] const platform::mouse_button button) final
    {
        std::cout << "Mouse Down: " << static_cast<int>(button) << '\n';
    }

    void on_mouse_up([[maybe_unused]] const platform::context &context,
                     [[maybe_unused]] const platform::mouse_button button) final
    {
        std::cout << "Mouse Up: " << static_cast<int>(button) << '\n';
    }

    void on_mouse_scroll([[maybe_unused]] const platform::context &context,
                         [[maybe_unused]] const std::int32_t delta) final
    {
        std::cout << "Scroll: " << delta << '\n';
    }
};

// This isn't an actual unit test. It's used for internal manual testing.
TEST(test_platform, DISABLED_test_create_window)
{
    platform::window_create_info info;
    info.title = u8"I like Π, and らき☆すた, Raki☆Suta";

    const auto context = platform::create_context();
    test_input_events input_events;
    context->attach_input_listener(input_events);

    test_window_events window_events;
    info.events = &window_events;
    const auto window = context->create_window(info);

    [[maybe_unused]] auto count = 0;
    while (!window->closed())
    {
        context->poll_events();
    }
}
