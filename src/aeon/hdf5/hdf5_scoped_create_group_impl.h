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

inline hdf5_scoped_create_group::hdf5_scoped_create_group(const hid_t file, const std::string &name)
    : handle_(-1)
{
    handle_ = H5Gcreate2(file, name.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    if (handle_ < 0)
        throw std::runtime_error("Could not create group '" + name + "'.");
}

inline hdf5_scoped_create_group::~hdf5_scoped_create_group()
{
    if (handle_ >= 0)
        H5Gclose(handle_);
}

inline hdf5_scoped_create_group::hdf5_scoped_create_group(hdf5_scoped_create_group &&other)
    : handle_(other.handle_)
{
    other.handle_ = -1;
}

inline hdf5_scoped_create_group &hdf5_scoped_create_group::operator=(hdf5_scoped_create_group &&other)
{
    handle_ = other.handle_;
    other.handle_ = -1;
    return *this;
}

} // namespace hdf5
} // namespace aeon
