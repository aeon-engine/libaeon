// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/file/png_structs.h>

namespace aeon::imaging::file::png::detail
{

class [[nodiscard]] png_read_structs final : public png_structs
{
public:
    png_read_structs();
    ~png_read_structs();

    png_read_structs(const png_read_structs &) = delete;
    auto operator=(const png_read_structs &)->png_read_structs & = delete;

    png_read_structs(png_read_structs &&) = delete;
    auto operator=(png_read_structs &&)->png_read_structs & = delete;
};

inline png_read_structs::png_read_structs()
{
    png_ptr_ = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    info_ptr_ = create_info_struct();
    end_info_ = create_info_struct();
}

inline png_read_structs::~png_read_structs()
{
    png_destroy_read_struct(&png_ptr_, &info_ptr_, &end_info_);
}

} // namespace aeon::imaging::file::png::detail
