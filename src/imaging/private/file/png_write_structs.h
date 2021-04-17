// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include "png_structs.h"

namespace aeon::imaging::file::png::detail
{

class [[nodiscard]] png_write_structs final : public png_structs
{
public:
    png_write_structs();
    ~png_write_structs();

    png_write_structs(const png_write_structs &) = delete;
    auto operator=(const png_write_structs &) -> png_write_structs & = delete;

    png_write_structs(png_write_structs &&) = delete;
    auto operator=(png_write_structs &&) -> png_write_structs & = delete;
};

inline png_write_structs::png_write_structs()
{
    png_ptr_ = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    info_ptr_ = create_info_struct();
}

inline png_write_structs::~png_write_structs()
{
    png_destroy_write_struct(&png_ptr_, &info_ptr_);
}

} // namespace aeon::imaging::file::png::detail
