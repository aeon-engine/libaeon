// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

/*!
 * \file
 * \brief Contains the image_view class.
 * An image view provides a way to access and modify image data.
 */

#pragma once

#include <aeon/imaging/pixel_encoding.h>
#include <aeon/math/mat_view.h>

namespace aeon::imaging
{

/*!
 * Base class for images.
 */
class iimage : public math::mat_view
{
public:
    using underlying_type = mat_view::underlying_type;
    using dimensions_type = mat_view::dimensions_type;
    using size_type = mat_view::size_type;
    using stride_type = mat_view::stride_type;

    ~iimage() override = default;

    iimage(const iimage &) = default;
    auto operator=(const iimage &) -> iimage & = default;

    iimage(iimage &&) noexcept = default;
    auto operator=(iimage &&) noexcept -> iimage & = default;

    /*!
     * Set the encoding of the image.
     */
    virtual void encoding(const pixel_encoding encoding) noexcept = 0;

    /*!
     * Get the encoding of the image.
     * \return The encoding of the image.
     */
    [[nodiscard]] virtual auto encoding() const noexcept -> pixel_encoding = 0;

protected:
    iimage()
        : math::mat_view{}
    {
    }

    template <typename... args_t>
    explicit iimage(args_t... args)
        : math::mat_view{std::forward<args_t>(args)...}
    {
    }
};

/*!
 * Get the encoding of the given image.
 * \param[in] image - A dynamic image
 * \return The encoding of the image.
 */
[[nodiscard]] inline auto encoding(const iimage &image) noexcept -> pixel_encoding
{
    return image.encoding();
}

} // namespace aeon::imaging
