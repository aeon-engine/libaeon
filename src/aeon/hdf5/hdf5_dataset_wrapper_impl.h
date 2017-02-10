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

#include <aeon/hdf5/hdf5_datatype.h>
#include <aeon/hdf5/hdf5_dataspace.h>
#include <aeon/hdf5/hdf5_dataset_properties.h>

namespace aeon
{
namespace hdf5
{

inline hdf5_dataset_wrapper::hdf5_dataset_wrapper()
    : handle_(-1)
{
}

inline hdf5_dataset_wrapper::hdf5_dataset_wrapper(const hdf5_file &file, const std::string &path)
    : handle_(-1)
{
    handle_ = H5Dopen(file.get_hid(), path.c_str(), H5P_DEFAULT);

    if (handle_ < 0)
        throw std::runtime_error("H5Dopen failed.");
}

inline hdf5_dataset_wrapper::hdf5_dataset_wrapper(const hdf5_file &file, const std::string &path,
                                                  const hdf5_datatype &datatype, const hdf5_dataspace &dataspace,
                                                  const hdf5_dataset_properties &properties)
    : handle_(-1)
{
    handle_ = H5Dcreate(file.get_hid(), path.c_str(), datatype.get_handle(), dataspace.get_handle(), H5P_DEFAULT,
                        properties.get_handle(), H5P_DEFAULT);

    if (handle_ < 0)
        throw std::runtime_error("H5Dcreate failed.");
}

inline hdf5_dataset_wrapper::~hdf5_dataset_wrapper()
{
    if (handle_ >= 0)
        H5Dclose(handle_);
}

inline hdf5_dataset_wrapper::hdf5_dataset_wrapper(hdf5_dataset_wrapper &&other)
    : handle_(other.handle_)
{
    other.handle_ = -1;
}

inline hdf5_dataset_wrapper &hdf5_dataset_wrapper::operator=(hdf5_dataset_wrapper &&other)
{
    handle_ = other.handle_;
    other.handle_ = -1;
    return *this;
}

inline auto hdf5_dataset_wrapper::get_handle() const
{
    return handle_;
}

} // namespace hdf5
} // namespace aeon
