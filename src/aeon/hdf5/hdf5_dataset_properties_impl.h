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

namespace aeon
{
namespace hdf5
{

inline hdf5_dataset_properties::hdf5_dataset_properties()
    : handle_(-1)
{
    handle_ = H5Pcreate(H5P_DATASET_CREATE);

    if (handle_ < 0)
        throw std::runtime_error("H5Pcreate failed.");
}

inline hdf5_dataset_properties::~hdf5_dataset_properties()
{
    if (handle_ >= 0)
        H5Pclose(handle_);
}

inline hdf5_dataset_properties::hdf5_dataset_properties(hdf5_dataset_properties &&other)
    : handle_(other.handle_)
{
    other.handle_ = -1;
}

inline hdf5_dataset_properties &hdf5_dataset_properties::operator=(hdf5_dataset_properties &&other)
{
    handle_ = other.handle_;
    other.handle_ = -1;
    return *this;
}

inline void hdf5_dataset_properties::set_filltime(const hdf5_dataset_filltime mode) const
{
    herr_t result = 0;

    switch (mode)
    {
        case hdf5_dataset_filltime::alloc:
            result = H5Pset_fill_time(handle_, H5D_FILL_TIME_ALLOC);
            break;
        case hdf5_dataset_filltime::never:
            result = H5Pset_fill_time(handle_, H5D_FILL_TIME_NEVER);
            break;
        case hdf5_dataset_filltime::ifset:
            result = H5Pset_fill_time(handle_, H5D_FILL_TIME_IFSET);
            break;
        default:
            throw std::runtime_error("Unsupported dataset filltime.");
    }

    if (result < 0)
        throw std::runtime_error("H5Pset_fill_time failed.");
}

inline auto hdf5_dataset_properties::get_handle() const
{
    return handle_;
}

} // namespace hdf5
} // namespace aeon
