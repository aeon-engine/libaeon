/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

#include <array>

namespace aeon
{
namespace hdf5
{

inline hdf5_dataspace::hdf5_dataspace()
    : handle_(-1)
    , size_(0)
{
}

inline hdf5_dataspace::hdf5_dataspace(const hid_t dataset_handle)
    : handle_(-1)
    , size_(0)
{
    handle_ = H5Dget_space(dataset_handle);

    if (handle_ < 0)
        throw std::runtime_error("H5Dget_space failed.");

    auto dimensions = H5Sget_simple_extent_ndims(handle_);

    if (dimensions != 1)
        throw std::runtime_error("Only 1D arrays are currently supported.");

    hsize_t array_size;
    H5Sget_simple_extent_dims(handle_, &array_size, nullptr);

    size_ = array_size;
}

inline hdf5_dataspace::hdf5_dataspace(const std::size_t reserve_size)
    : handle_(-1)
    , size_(reserve_size)
{
    handle_ = H5Screate(H5S_SIMPLE);

    if (handle_ < 0)
        throw std::runtime_error("H5Screate failed.");

    std::array<hsize_t, 1> dimensions = {reserve_size};

    if (H5Sset_extent_simple(handle_, 1, dimensions.data(), nullptr) < 0)
        throw std::runtime_error("H5Sset_extent_simple failed.");
}

inline hdf5_dataspace::~hdf5_dataspace()
{
    if (handle_ >= 0)
        H5Sclose(handle_);
}

inline hdf5_dataspace::hdf5_dataspace(hdf5_dataspace &&other)
    : handle_(other.handle_)
    , size_(other.size_)
{
    other.handle_ = -1;
}

inline hdf5_dataspace &hdf5_dataspace::operator=(hdf5_dataspace &&other)
{
    handle_ = other.handle_;
    size_ = other.size_;
    other.handle_ = -1;
    return *this;
}

inline auto hdf5_dataspace::get_handle() const
{
    return handle_;
}

inline auto hdf5_dataspace::get_size() const
{
    return size_;
}

} // namespace hdf5
} // namespace aeon
