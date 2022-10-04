// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/platform/window.h>
#include <aeon/platform/window_create_info.h>
#include <aeon/platform/window_events.h>
#include <aeon/platform/input_events.h>
#include <aeon/math/vector2_stream.h>
#include <aeon/math/size2d_stream.h>
#include <aeon/platform/context.h>
#include <iostream>

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

    void on_window_iconification_changed([[maybe_unused]] const platform::context &context,
                                         [[maybe_unused]] const platform::window_iconification_state state) noexcept
    {
        std::cout << "Iconify event: "
                  << (state == platform::window_iconification_state::normal ? "Normal" : "Minimized") << std::endl;
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

    void on_key([[maybe_unused]] const platform::context &context, const platform::keyboard_key key,
                const std::uint32_t scan_code, const platform::keyboard_key_state state) final
    {
        switch (state)
        {
            case platform::keyboard_key_state::released:
                std::cout << "[key released] keycode: " << static_cast<int>(key) << " scan code: " << scan_code << '\n';
                break;
            case platform::keyboard_key_state::pressed:
                std::cout << "[key pressed] keycode: " << static_cast<int>(key) << " scan code: " << scan_code << '\n';
                break;
            case platform::keyboard_key_state::repeated:
                std::cout << "[key repeated] keycode: " << static_cast<int>(key) << " scan code: " << scan_code << '\n';
                break;
        }
    }

    void on_mouse_move([[maybe_unused]] const platform::context &context,
                       [[maybe_unused]] const math::vector2<double> position) final
    {
        std::cout << "Mouse Move: " << position << '\n';
    }

    void on_mouse_button([[maybe_unused]] const platform::context &context, const platform::mouse_button button,
                         const platform::mouse_button_state state) final
    {
        switch (state)
        {
            case platform::mouse_button_state::released:
                std::cout << "[mouse released]: " << static_cast<int>(button) << '\n';
                break;
            case platform::mouse_button_state::pressed:
                std::cout << "[mouse pressed]: " << static_cast<int>(button) << '\n';
                break;
        }
    }

    void on_mouse_scroll([[maybe_unused]] const platform::context &context, [[maybe_unused]] const double delta) final
    {
        std::cout << "Scroll: " << delta << '\n';
    }
};

int main()
{
    platform::window_create_info info;
    info.title = u8"I like Π, and らき☆すた, Raki☆Suta";

    const auto context = platform::create_context();
    test_input_events input_events;
    context->attach_input_listener(input_events);

    test_window_events window_events;

    const auto window = context->create_window(info);
    window->attach_window_listener(window_events);

    [[maybe_unused]] auto count = 0;
    while (!window->closed())
    {
        context->poll_events();
    }

    return 0;
}
