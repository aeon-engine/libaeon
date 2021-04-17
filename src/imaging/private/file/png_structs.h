// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <png.h>

namespace aeon::imaging::file::png::detail
{

class [[nodiscard]] png_structs
{
public:
    png_structs();

    png_structs(const png_structs &) = delete;
    auto operator=(const png_structs &) -> png_structs & = delete;

    png_structs(png_structs &&) = delete;
    auto operator=(png_structs &&) -> png_structs & = delete;

    [[nodiscard]] auto png_ptr() const;
    [[nodiscard]] auto info_ptr() const;
    [[nodiscard]] auto end_info() const;

protected:
    ~png_structs();

    auto create_info_struct() const -> png_infop;

    png_structp png_ptr_;
    png_infop info_ptr_;
    png_infop end_info_;
};

inline png_structs::png_structs()
    : png_ptr_(nullptr)
    , info_ptr_(nullptr)
    , end_info_(nullptr)
{
}

inline png_structs::~png_structs()
{
    png_destroy_read_struct(&png_ptr_, &info_ptr_, &end_info_);
    png_ptr_ = nullptr;
    info_ptr_ = nullptr;
    end_info_ = nullptr;
}

[[nodiscard]] inline auto png_structs::png_ptr() const
{
    return png_ptr_;
}

[[nodiscard]] inline auto png_structs::info_ptr() const
{
    return info_ptr_;
}

[[nodiscard]] inline auto png_structs::end_info() const
{
    return end_info_;
}

[[nodiscard]] inline auto png_structs::create_info_struct() const -> png_infop
{
    return png_create_info_struct(png_ptr_);
}

} // namespace aeon::imaging::file::png::detail
