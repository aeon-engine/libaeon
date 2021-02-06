// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/mat_view.h>

namespace aeon::math
{

/*!
 * Class that represents a matrix of dynamic size
 * Unlike mat3 and mat4, data is laid out in row order
 */
template <typename T>
class mat : public mat_view<T>
{
public:
    using value_type = T;
    using underlying_type = std::byte;
    using dimensions_type = typename mat_view<T>::dimensions_type;
    using size_type = typename mat_view<T>::size_type;
    using stride_type = typename mat_view<T>::stride_type;

    /*!
     * Create an empty matrix.
     */
    mat() noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] dimensions - The width and height of the matrix.
     */
    explicit mat(const size2d<dimensions_type> dimensions) noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     */
    explicit mat(const dimensions_type width, const dimensions_type height) noexcept;

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     */
    explicit mat(const size2d<dimensions_type> dimensions, const std::ptrdiff_t stride) noexcept;

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     */
    explicit mat(const dimensions_type width, const dimensions_type height, const std::ptrdiff_t stride) noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions.
     */
    explicit mat(const size2d<dimensions_type> dimensions, const std::vector<underlying_type> &data);

    /*!
     * Create a matrix with the given dimensions
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions.
     */
    explicit mat(const dimensions_type width, const dimensions_type height, const std::vector<underlying_type> &data);

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions and
     * stride.
     */
    explicit mat(const size2d<dimensions_type> dimensions, const std::ptrdiff_t stride,
                 const std::vector<underlying_type> &data);

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions and
     * stride.
     */
    explicit mat(const dimensions_type width, const dimensions_type height, const std::ptrdiff_t stride,
                 const std::vector<underlying_type> &data);

    /*!
     * Create a matrix with the given dimensions
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] data - Data to be moved into the matrix. The size of the data must match the given dimensions.
     */
    explicit mat(const size2d<dimensions_type> dimensions, std::vector<underlying_type> &&data) noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] data - Data to be moved into the matrix. The size of the data must match the given dimensions.
     */
    explicit mat(const dimensions_type width, const dimensions_type height,
                 std::vector<underlying_type> &&data) noexcept;

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be moved into the matrix. The size of the data must match the given dimensions and
     * stride.
     */
    explicit mat(const size2d<dimensions_type> dimensions, const std::ptrdiff_t stride,
                 std::vector<underlying_type> &&data) noexcept;

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be moved into the matrix. The size of the data must match the given dimensions and
     * stride.
     */
    explicit mat(const dimensions_type width, const dimensions_type height, const std::ptrdiff_t stride,
                 std::vector<underlying_type> &&data) noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions.
     */
    explicit mat(const size2d<dimensions_type> dimensions, const underlying_type *data) noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions.
     */
    explicit mat(const dimensions_type width, const dimensions_type height, const underlying_type *data) noexcept;

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions.
     * stride.
     */
    explicit mat(const size2d<dimensions_type> dimensions, const std::ptrdiff_t stride,
                 const underlying_type *data) noexcept;

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions.
     * stride.
     */
    explicit mat(const dimensions_type width, const dimensions_type height, const std::ptrdiff_t stride,
                 const underlying_type *data) noexcept;

    ~mat() noexcept = default;

    mat(const mat &) = delete;
    auto operator=(const mat &) -> mat & = delete;

    mat(mat &&) noexcept = default;
    auto operator=(mat &&) noexcept -> mat & = default;

    explicit mat(const mat_view<T> &other);
    auto operator=(const mat_view<T> &other) -> mat &;

    /*!
     * Make a copy of the matrix. In order to avoid performance issues, the class is made
     * non-copyable. In order to copy the matrix, a call to clone() must be done explicitly.
     * \return A copy of this image.
     */
    [[nodiscard]] auto clone() const -> mat<T>;

protected:
    void copy_from_pointer(const underlying_type *data);

    std::vector<underlying_type> data_;
};

template <typename T>
inline constexpr auto operator+=(mat<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T> &;

template <typename T>
inline constexpr auto operator-=(mat<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T> &;

template <typename T>
inline constexpr auto operator*=(mat<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T> &;

template <typename T>
inline constexpr auto operator/=(mat<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T> &;

template <typename T>
inline constexpr auto operator+(const mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T>;

template <typename T>
inline constexpr auto operator-(const mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T>;

template <typename T>
inline constexpr auto operator*(const mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T>;

template <typename T>
inline constexpr auto operator/(const mat_view<T> &lhs, const typename mat_view<T>::value_type rhs) -> mat<T>;

} // namespace aeon::math

#include <aeon/math/impl/mat_impl.h>
#include <aeon/math/impl/mat_operators_impl.h>
