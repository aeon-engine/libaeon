// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include "glfw_window.h"
#include "glfw_exception.h"
#include "glfw_init.h"
#include <aeon/platform/native_handles.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif (AEON_PLATFORM_OS_LINUX)
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include <GLFW/glfw3native.h>
#include <iostream>

namespace aeon::platform
{

namespace internal
{

static auto convert_key(const int key) noexcept -> keyboard_key
{
    switch (key)
    {
        case GLFW_KEY_SPACE:
            return keyboard_key::space;
        case GLFW_KEY_APOSTROPHE:
            return keyboard_key::apostrophe;
        case GLFW_KEY_COMMA:
            return keyboard_key::comma;
        case GLFW_KEY_MINUS:
            return keyboard_key::minus;
        case GLFW_KEY_PERIOD:
            return keyboard_key::period;
        case GLFW_KEY_SLASH:
            return keyboard_key::forward_slash;
        case GLFW_KEY_0:
            return keyboard_key::key_0;
        case GLFW_KEY_1:
            return keyboard_key::key_1;
        case GLFW_KEY_2:
            return keyboard_key::key_2;
        case GLFW_KEY_3:
            return keyboard_key::key_3;
        case GLFW_KEY_4:
            return keyboard_key::key_4;
        case GLFW_KEY_5:
            return keyboard_key::key_5;
        case GLFW_KEY_6:
            return keyboard_key::key_6;
        case GLFW_KEY_7:
            return keyboard_key::key_7;
        case GLFW_KEY_8:
            return keyboard_key::key_8;
        case GLFW_KEY_9:
            return keyboard_key::key_9;
        case GLFW_KEY_SEMICOLON:
            return keyboard_key::semicolon;
        case GLFW_KEY_EQUAL:
            return keyboard_key::equal;
        case GLFW_KEY_A:
            return keyboard_key::a;
        case GLFW_KEY_B:
            return keyboard_key::b;
        case GLFW_KEY_C:
            return keyboard_key::c;
        case GLFW_KEY_D:
            return keyboard_key::d;
        case GLFW_KEY_E:
            return keyboard_key::e;
        case GLFW_KEY_F:
            return keyboard_key::f;
        case GLFW_KEY_G:
            return keyboard_key::g;
        case GLFW_KEY_H:
            return keyboard_key::h;
        case GLFW_KEY_I:
            return keyboard_key::i;
        case GLFW_KEY_J:
            return keyboard_key::j;
        case GLFW_KEY_K:
            return keyboard_key::k;
        case GLFW_KEY_L:
            return keyboard_key::l;
        case GLFW_KEY_M:
            return keyboard_key::m;
        case GLFW_KEY_N:
            return keyboard_key::n;
        case GLFW_KEY_O:
            return keyboard_key::o;
        case GLFW_KEY_P:
            return keyboard_key::p;
        case GLFW_KEY_Q:
            return keyboard_key::q;
        case GLFW_KEY_R:
            return keyboard_key::r;
        case GLFW_KEY_S:
            return keyboard_key::s;
        case GLFW_KEY_T:
            return keyboard_key::t;
        case GLFW_KEY_U:
            return keyboard_key::u;
        case GLFW_KEY_V:
            return keyboard_key::v;
        case GLFW_KEY_W:
            return keyboard_key::w;
        case GLFW_KEY_X:
            return keyboard_key::x;
        case GLFW_KEY_Y:
            return keyboard_key::y;
        case GLFW_KEY_Z:
            return keyboard_key::z;
        case GLFW_KEY_LEFT_BRACKET:
            return keyboard_key::left_bracket;
        case GLFW_KEY_BACKSLASH:
            return keyboard_key::backslash;
        case GLFW_KEY_RIGHT_BRACKET:
            return keyboard_key::right_bracket;
        case GLFW_KEY_GRAVE_ACCENT:
            return keyboard_key::grave_accent;
        case GLFW_KEY_WORLD_1:
            return keyboard_key::world_1;
        case GLFW_KEY_WORLD_2:
            return keyboard_key::world_2;
        case GLFW_KEY_ESCAPE:
            return keyboard_key::escape;
        case GLFW_KEY_ENTER:
            return keyboard_key::enter;
        case GLFW_KEY_TAB:
            return keyboard_key::tab;
        case GLFW_KEY_BACKSPACE:
            return keyboard_key::backspace;
        case GLFW_KEY_INSERT:
            return keyboard_key::insert;
        case GLFW_KEY_DELETE:
            return keyboard_key::del;
        case GLFW_KEY_RIGHT:
            return keyboard_key::right;
        case GLFW_KEY_LEFT:
            return keyboard_key::left;
        case GLFW_KEY_DOWN:
            return keyboard_key::down;
        case GLFW_KEY_UP:
            return keyboard_key::up;
        case GLFW_KEY_PAGE_UP:
            return keyboard_key::page_up;
        case GLFW_KEY_PAGE_DOWN:
            return keyboard_key::page_down;
        case GLFW_KEY_HOME:
            return keyboard_key::home;
        case GLFW_KEY_END:
            return keyboard_key::end;
        case GLFW_KEY_CAPS_LOCK:
            return keyboard_key::caps_lock;
        case GLFW_KEY_SCROLL_LOCK:
            return keyboard_key::scroll_lock;
        case GLFW_KEY_NUM_LOCK:
            return keyboard_key::num_lock;
        case GLFW_KEY_PRINT_SCREEN:
            return keyboard_key::print_screen;
        case GLFW_KEY_PAUSE:
            return keyboard_key::pause;
        case GLFW_KEY_F1:
            return keyboard_key::f1;
        case GLFW_KEY_F2:
            return keyboard_key::f2;
        case GLFW_KEY_F3:
            return keyboard_key::f3;
        case GLFW_KEY_F4:
            return keyboard_key::f4;
        case GLFW_KEY_F5:
            return keyboard_key::f5;
        case GLFW_KEY_F6:
            return keyboard_key::f6;
        case GLFW_KEY_F7:
            return keyboard_key::f7;
        case GLFW_KEY_F8:
            return keyboard_key::f8;
        case GLFW_KEY_F9:
            return keyboard_key::f9;
        case GLFW_KEY_F10:
            return keyboard_key::f10;
        case GLFW_KEY_F11:
            return keyboard_key::f11;
        case GLFW_KEY_F12:
            return keyboard_key::f12;
        case GLFW_KEY_F13:
            return keyboard_key::f13;
        case GLFW_KEY_F14:
            return keyboard_key::f14;
        case GLFW_KEY_F15:
            return keyboard_key::f15;
        case GLFW_KEY_F16:
            return keyboard_key::f16;
        case GLFW_KEY_F17:
            return keyboard_key::f17;
        case GLFW_KEY_F18:
            return keyboard_key::f18;
        case GLFW_KEY_F19:
            return keyboard_key::f19;
        case GLFW_KEY_F20:
            return keyboard_key::f20;
        case GLFW_KEY_F21:
            return keyboard_key::f21;
        case GLFW_KEY_F22:
            return keyboard_key::f22;
        case GLFW_KEY_F23:
            return keyboard_key::f23;
        case GLFW_KEY_F24:
            return keyboard_key::f24;
        case GLFW_KEY_F25:
            return keyboard_key::f25;
        case GLFW_KEY_KP_0:
            return keyboard_key::kp_0;
        case GLFW_KEY_KP_1:
            return keyboard_key::kp_1;
        case GLFW_KEY_KP_2:
            return keyboard_key::kp_2;
        case GLFW_KEY_KP_3:
            return keyboard_key::kp_3;
        case GLFW_KEY_KP_4:
            return keyboard_key::kp_4;
        case GLFW_KEY_KP_5:
            return keyboard_key::kp_5;
        case GLFW_KEY_KP_6:
            return keyboard_key::kp_6;
        case GLFW_KEY_KP_7:
            return keyboard_key::kp_7;
        case GLFW_KEY_KP_8:
            return keyboard_key::kp_8;
        case GLFW_KEY_KP_9:
            return keyboard_key::kp_9;
        case GLFW_KEY_KP_DECIMAL:
            return keyboard_key::kp_decimal;
        case GLFW_KEY_KP_DIVIDE:
            return keyboard_key::kp_divide;
        case GLFW_KEY_KP_MULTIPLY:
            return keyboard_key::kp_multiply;
        case GLFW_KEY_KP_SUBTRACT:
            return keyboard_key::kp_subtract;
        case GLFW_KEY_KP_ADD:
            return keyboard_key::kp_add;
        case GLFW_KEY_KP_ENTER:
            return keyboard_key::kp_enter;
        case GLFW_KEY_KP_EQUAL:
            return keyboard_key::kp_equal;
        case GLFW_KEY_LEFT_SHIFT:
            return keyboard_key::left_shift;
        case GLFW_KEY_LEFT_CONTROL:
            return keyboard_key::left_control;
        case GLFW_KEY_LEFT_ALT:
            return keyboard_key::left_alt;
        case GLFW_KEY_LEFT_SUPER:
            return keyboard_key::left_super;
        case GLFW_KEY_RIGHT_SHIFT:
            return keyboard_key::right_shift;
        case GLFW_KEY_RIGHT_CONTROL:
            return keyboard_key::right_control;
        case GLFW_KEY_RIGHT_ALT:
            return keyboard_key::right_alt;
        case GLFW_KEY_RIGHT_SUPER:
            return keyboard_key::right_super;
        case GLFW_KEY_MENU:
            return keyboard_key::menu;
        case GLFW_KEY_UNKNOWN:
        default:
            return keyboard_key::unknown;
    }
}

static auto convert_key_state(const int state) noexcept -> keyboard_key_state
{
    switch (state)
    {
        case GLFW_RELEASE:
            return keyboard_key_state::released;
        case GLFW_PRESS:
            return keyboard_key_state::pressed;
        case GLFW_REPEAT:
            return keyboard_key_state::repeated;
        default:
            std::abort();
    }
}

static auto convert_button(const int button) noexcept -> mouse_button
{
    switch (button)
    {
        case GLFW_MOUSE_BUTTON_1:
            return mouse_button::button1;
        case GLFW_MOUSE_BUTTON_2:
            return mouse_button::button2;
        case GLFW_MOUSE_BUTTON_3:
            return mouse_button::button3;
        case GLFW_MOUSE_BUTTON_4:
            return mouse_button::button4;
        case GLFW_MOUSE_BUTTON_5:
            return mouse_button::button5;
        case GLFW_MOUSE_BUTTON_6:
            return mouse_button::button6;
        case GLFW_MOUSE_BUTTON_7:
            return mouse_button::button7;
        case GLFW_MOUSE_BUTTON_8:
            return mouse_button::button8;
        default:
            return mouse_button::unknown;
    }
}

static auto convert_button_state(const int state) noexcept -> mouse_button_state
{
    if (state == GLFW_PRESS)
        return mouse_button_state::pressed;

    return mouse_button_state::released;
}

} // namespace internal

glfw_window::glfw_window(const window_create_info &info, glfw_context &context)
    : context_{context}
    , window_{}
{
    glfw::initialize();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, info.resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, info.visible ? GLFW_TRUE : GLFW_FALSE);
    window_ = glfwCreateWindow(info.size.width, info.size.height, reinterpret_cast<const char *>(info.title.c_str()),
                               nullptr, nullptr);

    if (!window_)
        throw glfw_platform_exception{u8"Could not create window."};

    glfwSetWindowUserPointer(window_, this);

    if (info.position)
        position(*info.position);

    glfwSetWindowPosCallback(window_,
                             [](GLFWwindow *window, const int xpos, const int ypos)
                             {
                                 const auto w = static_cast<const glfw_window *>(glfwGetWindowUserPointer(window));
                                 w->window_listeners().invoke_each(&window_events::on_window_position_changed,
                                                                   w->context_, math::vector2{xpos, ypos});
                             });

    glfwSetWindowSizeCallback(window_,
                              [](GLFWwindow *window, const int width, const int height)
                              {
                                  const auto w = static_cast<const glfw_window *>(glfwGetWindowUserPointer(window));
                                  w->window_listeners().invoke_each(&window_events::on_window_size_changed, w->context_,
                                                                    math::size2d{width, height});
                              });

    glfwSetWindowFocusCallback(window_,
                               [](GLFWwindow *window, const int focused)
                               {
                                   const auto w = static_cast<const glfw_window *>(glfwGetWindowUserPointer(window));
                                   w->window_listeners().invoke_each(&window_events::on_window_focus_changed,
                                                                     w->context_, focused == GLFW_TRUE);
                               });

    glfwSetWindowIconifyCallback(
        window_,
        [](GLFWwindow *window, const int iconified)
        {
            const auto w = static_cast<const glfw_window *>(glfwGetWindowUserPointer(window));
            const auto state = iconified ? window_iconification_state::minimized : window_iconification_state::normal;
            w->window_listeners().invoke_each(&window_events::on_window_iconification_changed, w->context_, state);
        });

    glfwSetWindowCloseCallback(window_,
                               [](GLFWwindow *window)
                               {
                                   const auto w = static_cast<const glfw_window *>(glfwGetWindowUserPointer(window));
                                   w->window_listeners().invoke_each(&window_events::on_window_closed, w->context_);
                               });

    glfwSetKeyCallback(
        window_,
        [](GLFWwindow *window, const int key, const int scancode, const int action, [[maybe_unused]] const int mods)
        {
            const auto w = static_cast<const glfw_window *>(glfwGetWindowUserPointer(window));
            const auto k = internal::convert_key(key);
            const auto state = internal::convert_key_state(action);
            w->context_.handle_key(k, scancode, state);
        });

    glfwSetCursorPosCallback(window_,
                             [](GLFWwindow *window, const double xpos, const double ypos)
                             {
                                 const auto w = static_cast<const glfw_window *>(glfwGetWindowUserPointer(window));
                                 w->context_.handle_mouse_move({xpos, ypos});
                             });

    glfwSetMouseButtonCallback(
        window_,
        [](GLFWwindow *window, const int button, const int action, [[maybe_unused]] const int mods)
        {
            const auto w = static_cast<const glfw_window *>(glfwGetWindowUserPointer(window));
            const auto mouse_button = internal::convert_button(button);
            const auto mouse_button_state = internal::convert_button_state(action);
            w->context_.handle_mouse_button(mouse_button, mouse_button_state);
        });

    glfwSetScrollCallback(window_,
                          [](GLFWwindow *window, [[maybe_unused]] const double xoffset, const double yoffset)
                          {
                              const auto w = static_cast<const glfw_window *>(glfwGetWindowUserPointer(window));
                              w->context_.handle_mouse_scroll(yoffset);
                          });
}

glfw_window::~glfw_window() = default;

auto glfw_window::position() const noexcept -> math::vector2<std::int32_t>
{
    math::vector2<int> position;
    glfwGetWindowPos(window_, &position.x, &position.y);
    return math::vector2<std::int32_t>{position};
}

void glfw_window::position(const math::vector2<std::int32_t> &pos)
{
    glfwSetWindowPos(window_, pos.x, pos.y);
}

void glfw_window::title(const std::u8string &str)
{
    glfwSetWindowTitle(window_, reinterpret_cast<const char *>(str.c_str()));
}

auto glfw_window::dimensions() const noexcept -> math::size2d<std::int32_t>
{
    math::size2d<int> dimensions;
    glfwGetWindowSize(window_, &dimensions.width, &dimensions.height);
    return math::size2d<std::int32_t>{dimensions};
}

void glfw_window::dimensions(const math::size2d<std::int32_t> &size)
{
    glfwSetWindowSize(window_, size.width, size.height);
}

auto glfw_window::iconification_state() const noexcept -> window_iconification_state
{
    if (glfwGetWindowAttrib(window_, GLFW_ICONIFIED))
        return window_iconification_state::minimized;

    return window_iconification_state::normal;
}

void glfw_window::close()
{
    window_.destroy();
}

auto glfw_window::closed() const noexcept -> bool
{
    return window_.is_closed();
}

auto glfw_window::native_handles() const noexcept -> platform::native_handles
{
    platform::native_handles handles;

#if (AEON_PLATFORM_OS_WINDOWS)
    handles.hwnd = glfwGetWin32Window(window_);
#elif (AEON_PLATFORM_OS_LINUX)
    handles.window = glfwGetX11Window(window_);
    handles.display = glfwGetX11Display();
#endif

    return handles;
}

auto glfw_window::context() const noexcept -> const platform::context &
{
    return context_;
}

} // namespace aeon::platform
