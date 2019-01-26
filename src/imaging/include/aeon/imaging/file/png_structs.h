// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <png.h>

namespace aeon::imaging::file::png::detail
{

class png_structs
{
public:
    png_structs();
    ~png_structs();

    png_structs(const png_structs &) = delete;
    auto operator=(const png_structs &) -> png_structs & = delete;

    png_structs(png_structs &&o) = default;
    auto operator=(png_structs &&other) -> png_structs & = default;

    auto png_ptr() const;
    auto info_ptr() const;
    auto end_info() const;

protected:
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

inline auto png_structs::png_ptr() const
{
    return png_ptr_;
}

inline auto png_structs::info_ptr() const
{
    return info_ptr_;
}

inline auto png_structs::end_info() const
{
    return end_info_;
}

inline auto png_structs::create_info_struct() const -> png_infop
{
    return png_create_info_struct(png_ptr_);
}

} // namespace aeon::imaging::file::png::detail
