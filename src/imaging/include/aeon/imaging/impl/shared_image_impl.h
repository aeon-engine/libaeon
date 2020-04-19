// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

namespace aeon::imaging
{

template <typename T>
inline shared_image<T>::shared_image()
    : image_view<T>{}
    , data_{}
{
}

template <typename T>
inline shared_image<T>::shared_image(const image_descriptor<T> &descriptor)
    : image_view<T>{descriptor}
    , data_(size(descriptor))
{
    image_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline shared_image<T>::shared_image(const image_descriptor<T> &descriptor, const std::vector<std::byte> &data)
    : image_view<T>{descriptor}
    , data_{data}
{
    image_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline shared_image<T>::shared_image(const image_descriptor<T> &descriptor, std::vector<std::byte> &&data)
    : image_view<T>{descriptor}
    , data_{std::move(data)}
{
    image_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline shared_image<T>::shared_image(const image_descriptor<T> &descriptor,
                                     const common::shared_vector<std::byte> &data)
    : image_view<T>{descriptor}
    , data_{data}
{
    image_view<T>::data_ptr_ = std::data(data_);
}

template <typename T>
inline shared_image<T>::~shared_image() = default;

template <typename T>
[[nodiscard]] inline auto shared_image<T>::raw_data() noexcept -> std::byte *
{
    return std::data(data_);
}

template <typename T>
[[nodiscard]] inline auto shared_image<T>::raw_data() const noexcept -> const std::byte *
{
    return std::data(data_);
}

template <typename T>
[[nodiscard]] inline auto shared_image<T>::shared_data() const noexcept -> common::shared_vector<std::byte>
{
    return data_;
}

template <typename T>
[[nodiscard]] inline auto shared_image<T>::move_to_dynamic_image() -> std::unique_ptr<image_base>
{
    return std::make_unique<shared_image<T>>(image_view<T>::descriptor_, std::move(data_));
}

template <typename T>
[[nodiscard]] inline auto raw_data(shared_image<T> &image) noexcept -> std::byte *
{
    return image.raw_data();
}

template <typename T>
[[nodiscard]] inline auto raw_data(const shared_image<T> &image) noexcept -> const std::byte *
{
    return image.raw_data();
}

} // namespace aeon::imaging
