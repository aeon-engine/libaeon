// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/exceptions.h>

namespace aeon::imaging::convert
{

class convert_exception : public imaging_exception
{
};

[[nodiscard]] auto to_rgb_copy(const image_view &img) -> image;
[[nodiscard]] auto to_bgr_copy(const image_view &img) -> image;
[[nodiscard]] auto to_rgba_copy(const image_view &img) -> image;
[[nodiscard]] auto to_bgra_copy(const image_view &img) -> image;

} // namespace aeon::imaging::convert
