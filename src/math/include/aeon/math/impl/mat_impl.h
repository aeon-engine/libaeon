// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::math
{

inline mat::mat() noexcept
    : mat_view{}
    , data_{}
{
}

inline mat::mat(const common::element_type type, const size2d<dimensions_type> dimensions) noexcept
    : mat_view{type, dimensions, nullptr}
    , data_(mat_view::stride_ * math::height(mat_view::dimensions_))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const common::element_type type, const dimensions_type width, const dimensions_type height) noexcept
    : mat_view{type, width, height, nullptr}
    , data_(mat_view::stride_ * math::height(mat_view::dimensions_))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const common::element_type type, const size2d<dimensions_type> dimensions,
                const stride_type stride) noexcept
    : mat_view{type, dimensions, stride, nullptr}
    , data_(mat_view::stride_ * math::height(mat_view::dimensions_))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const common::element_type type, const dimensions_type width, const dimensions_type height,
                const stride_type stride) noexcept
    : mat_view{type, width, height, stride, nullptr}
    , data_(mat_view::stride_ * math::height(mat_view::dimensions_))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const common::element_type type, const size2d<dimensions_type> dimensions,
                std::vector<underlying_type> data) noexcept
    : mat_view{type, dimensions, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const common::element_type type, const dimensions_type width, const dimensions_type height,
                std::vector<underlying_type> data) noexcept
    : mat_view{type, width, height, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const common::element_type type, const size2d<dimensions_type> dimensions, const stride_type stride,
                std::vector<underlying_type> data) noexcept
    : mat_view{type, dimensions, stride, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const common::element_type type, const dimensions_type width, const dimensions_type height,
                const stride_type stride, std::vector<underlying_type> data) noexcept
    : mat_view{type, width, height, stride, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline mat::mat(const common::element_type type, const size2d<dimensions_type> dimensions, const underlying_type *data)
    : mat_view{type, dimensions, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline mat::mat(const common::element_type type, const dimensions_type width, const dimensions_type height,
                const underlying_type *data)
    : mat_view{type, width, height, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline mat::mat(const common::element_type type, const size2d<dimensions_type> dimensions, const stride_type stride,
                const underlying_type *data)
    : mat_view{type, dimensions, stride, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline mat::mat(const common::element_type type, const dimensions_type width, const dimensions_type height,
                const stride_type stride, const underlying_type *data)
    : mat_view{type, width, height, stride, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline mat::mat(const imat &other)
    : mat_view{math::element_type(other), math::dimensions(other), math::stride(other), nullptr}
    , data_{}
{
    copy_from_pointer(std::data(other));
}

inline auto mat::operator=(const imat &other) -> mat &
{
    if (this != &other) [[likely]]
    {
        mat_view::type_ = math::element_type(other);
        mat_view::dimensions_ = math::dimensions(other);
        mat_view::stride_ = math::stride(other);
        copy_from_pointer(std::data(other));
    }

    return *this;
}

[[nodiscard]] inline auto mat::clone() const -> mat
{
    return mat{type_, dimensions_, stride_, data_};
}

inline void mat::copy_from_pointer(const underlying_type *data)
{
    const auto size = mat_view::size();
    data_.resize(size);
    mat_view::data_ptr_ = std::data(data_);
    std::copy_n(data, size, std::begin(data_));
}

} // namespace aeon::math
