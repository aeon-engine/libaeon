// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline mat<T>::mat() noexcept
    : mat_view<T>{}
    , data_{}
{
}

template <typename T>
inline mat<T>::mat(const size2d<dimensions_type> dimensions) noexcept
    : mat_view<T>{dimensions, nullptr}
    , data_(mat_view<T>::stride_ * height(mat_view<T>::dimensions_))
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const dimensions_type width, const dimensions_type height) noexcept
    : mat_view<T>{width, height, nullptr}
    , data_(mat_view<T>::stride_ * height(mat_view<T>::dimensions_))
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const size2d<dimensions_type> dimensions, const std::ptrdiff_t stride) noexcept
    : mat_view<T>{dimensions, stride, nullptr}
    , data_(mat_view<T>::stride_ * height(mat_view<T>::dimensions_))
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const dimensions_type width, const dimensions_type height, const std::ptrdiff_t stride) noexcept
    : mat_view<T>{width, height, stride, nullptr}
    , data_(mat_view<T>::stride_ * height(mat_view<T>::dimensions_))
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const size2d<dimensions_type> dimensions, const std::vector<underlying_type> &data)
    : mat_view<T>{dimensions, nullptr}
    , data_{data}
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const dimensions_type width, const dimensions_type height, const std::vector<underlying_type> &data)
    : mat_view<T>{width, height, nullptr}
    , data_{data}
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const size2d<dimensions_type> dimensions, const std::ptrdiff_t stride,
                   const std::vector<underlying_type> &data)
    : mat_view<T>{dimensions, stride, nullptr}
    , data_{data}
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const dimensions_type width, const dimensions_type height, const std::ptrdiff_t stride,
                   const std::vector<underlying_type> &data)
    : mat_view<T>{width, height, stride, nullptr}
    , data_{data}
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const size2d<dimensions_type> dimensions, std::vector<underlying_type> &&data) noexcept
    : mat_view<T>{dimensions, nullptr}
    , data_{std::move(data)}
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const dimensions_type width, const dimensions_type height,
                   std::vector<underlying_type> &&data) noexcept
    : mat_view<T>{width, height, nullptr}
    , data_{std::move(data)}
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const size2d<dimensions_type> dimensions, const std::ptrdiff_t stride,
                   std::vector<underlying_type> &&data) noexcept
    : mat_view<T>{dimensions, stride, nullptr}
    , data_{std::move(data)}
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const dimensions_type width, const dimensions_type height, const std::ptrdiff_t stride,
                   std::vector<underlying_type> &&data) noexcept
    : mat_view<T>{width, height, stride, nullptr}
    , data_{std::move(data)}
{
    mat_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline mat<T>::mat(const size2d<dimensions_type> dimensions, const underlying_type *data) noexcept
    : mat_view<T>{dimensions, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

template <typename T>
inline mat<T>::mat(const dimensions_type width, const dimensions_type height, const underlying_type *data) noexcept
    : mat_view<T>{width, height, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

template <typename T>
inline mat<T>::mat(const size2d<dimensions_type> dimensions, const std::ptrdiff_t stride,
                   const underlying_type *data) noexcept
    : mat_view<T>{dimensions, stride, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

template <typename T>
inline mat<T>::mat(const dimensions_type width, const dimensions_type height, const std::ptrdiff_t stride,
                   const underlying_type *data) noexcept
    : mat_view<T>{width, height, stride, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

template <typename T>
inline mat<T>::mat(const mat_view<T> &other)
    : mat_view<T>{dimensions(other), stride(other), nullptr}
    , data_{}
{
    copy_from_pointer(std::data(other));
}

template <typename T>
inline auto mat<T>::operator=(const mat_view<T> &other) -> mat &
{
    if (this != &other) [[likely]]
    {
        mat_view<T>::dimensions_ = dimensions(other);
        mat_view<T>::stride_ = stride(other);
        copy_from_pointer(std::data(other));
    }

    return *this;
}

template <typename T>
[[nodiscard]] inline auto mat<T>::clone() const -> mat<T>
{
    return mat{dimensions, stride, data_};
}

template <typename T>
void mat<T>::copy_from_pointer(const underlying_type *data)
{
    const auto size = mat_view<T>::size();
    data_.resize(size);
    mat_view<T>::data_ptr_ = std::data(data_);
    std::copy_n(data, size, std::begin(data_));
}

} // namespace aeon::math
