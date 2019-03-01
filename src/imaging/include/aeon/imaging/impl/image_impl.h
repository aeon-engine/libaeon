// Copyright (c) 2012-2019 Robin Degen

#pragma once

namespace aeon::imaging
{

template <typename T>
inline image<T>::image()
    : image_view<T>{}
    , data_{}
{
}

template <typename T>
inline image<T>::image(const image_descriptor<T> &descriptor)
    : image_view<T>{descriptor}
    , data_(size(descriptor))
{
    image_view<T>::data_ptr_ = data_.data();
}

template <typename T>
inline image<T>::image(const image_descriptor<T> &descriptor, const std::vector<std::byte> &data)
    : image_view<T>{descriptor}
    , data_{data}
{
    image_view<T>::data_ptr_ = data_.data();
}

template <typename T>
inline image<T>::image(const image_descriptor<T> &descriptor, std::vector<std::byte> &&data)
    : image_view<T>{descriptor}
    , data_{std::move(data)}
{
    image_view<T>::data_ptr_ = data_.data();
}

template <typename T>
inline image<T>::~image() = default;

template <typename T>
[[nodiscard]] inline auto image<T>::clone() const -> image<T>
{
    return image{image_view<T>::descriptor_, data_};
}

template <typename T>
[[nodiscard]] inline auto image<T>::raw_data() noexcept -> std::byte *
{
    return std::data(data_);
}

template <typename T>
[[nodiscard]] inline auto image<T>::raw_data() const noexcept -> const std::byte *
{
    return std::data(data_);
}

template <typename T>
[[nodiscard]] inline auto image<T>::move_to_dynamic_image() -> std::unique_ptr<image_base>
{
    return std::make_unique<image<T>>(image_view<T>::descriptor_, std::move(data_));
}

template <typename T>
[[nodiscard]] inline auto raw_data(image<T> &image) noexcept -> std::byte *
{
    return image.raw_data();
}

template <typename T>
[[nodiscard]] inline auto raw_data(const image<T> &image) noexcept -> const std::byte *
{
    return image.raw_data();
}

} // namespace aeon::imaging
