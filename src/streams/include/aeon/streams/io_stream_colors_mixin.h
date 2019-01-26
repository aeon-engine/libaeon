// Copyright (c) 2012-2019 Robin Degen

#pragma once

namespace aeon::streams
{

enum class color
{
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
};

enum class weight
{
    normal,
    bold
};

class io_stream_colors_mixin
{
public:
    io_stream_colors_mixin();
    virtual ~io_stream_colors_mixin() = default;

    io_stream_colors_mixin(io_stream_colors_mixin &&) noexcept = default;
    auto operator=(io_stream_colors_mixin &&) noexcept -> io_stream_colors_mixin & = default;

    io_stream_colors_mixin(const io_stream_colors_mixin &) noexcept = default;
    auto operator=(const io_stream_colors_mixin &) noexcept -> io_stream_colors_mixin & = default;

    void set_color(const color c, const weight w = weight::normal) const noexcept;
    void reset_color() const noexcept;

    void enable_colors() noexcept;
    void disable_colors() noexcept;

private:
    bool enabled_;
};

} // namespace aeon::streams
