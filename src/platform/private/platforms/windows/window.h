// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/platform/window.h>
#include "scoped_window_class.h"
#include "scoped_window_handle.h"

namespace aeon::platform
{

class context_win32;
struct window_create_info;
class window_events;

class window_win32 final : public window
{
public:
    explicit window_win32(const window_create_info &info, context_win32 &context);
    ~window_win32() final;

    window_win32(const window_win32 &) noexcept = delete;
    auto operator=(const window_win32 &) noexcept -> window_win32 & = delete;

    window_win32(window_win32 &&) noexcept = delete;
    auto operator=(window_win32 &&) noexcept -> window_win32 & = delete;

    [[nodiscard]] auto position() const noexcept -> math::vector2<std::int32_t> final;
    void position(const math::vector2<std::int32_t> &pos) final;

    void title(const std::u8string &str) final;

    [[nodiscard]] auto dimensions() const noexcept -> math::size2d<std::int32_t> final;
    void dimensions(const math::size2d<std::int32_t> &size) final;

    [[nodiscard]] auto client_dimensions() const noexcept -> math::size2d<std::int32_t> final;

    void close() final;

    [[nodiscard]] auto closed() const noexcept -> bool final;

    [[nodiscard]] auto events() const noexcept
    {
        return events_;
    }

    [[nodiscard]] auto native_handles() const noexcept -> platform::native_handles final;

    [[nodiscard]] auto context() const noexcept -> const platform::context & final;

    void on_position_changed(const math::vector2<std::int32_t> &position) const noexcept;
    void on_size_changed(const math::size2d<std::int32_t> &size) const noexcept;
    void on_closing() noexcept;
    void on_focus_change(const bool focus) const noexcept;

private:
    context_win32 &context_;
    scoped_window_class class_;
    scoped_window_handle handle_;
    window_events *events_;
    std::uint32_t closing_ : 1;
};

} // namespace aeon::platform
