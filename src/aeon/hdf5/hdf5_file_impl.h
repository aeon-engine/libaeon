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

#include <aeon/filesystem/filesystem.h>
#include <aeon/hdf5/hdf5_scoped_create_group.h>
#include <aeon/utility/string.h>
#include <string>

namespace aeon
{
namespace hdf5
{

inline hdf5_file::hdf5_file()
    : file_(-1)
{
}

inline hdf5_file::hdf5_file(const std::string &path, const hdf5_file_open_mode mode)
    : file_(-1)
{
    switch (mode)
    {
        case create:
        {
            if (filesystem::exists(path))
                throw std::runtime_error("Can not create HDF5 file. File exists.");

            file_ = H5Fcreate(path.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        }
        break;
        case read_only:
        {
            if (!filesystem::exists(path))
                throw std::runtime_error("Can not open HDF5 file. File doesn't exist.");

            file_ = H5Fopen(path.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
        }
        break;
        case read_write:
        {
            if (!filesystem::exists(path))
                throw std::runtime_error("Can not open HDF5 file. File doesn't exist.");

            file_ = H5Fopen(path.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
        }
        break;
        default:
            assert(true && "Unknown or invalid mode.");
    }

    if (file_ < 0)
        throw std::runtime_error("Error opening hdf5 file.");
}

inline hdf5_file::~hdf5_file()
{
    if (file_ >= 0)
        H5Fclose(file_);
}

inline hdf5_file::hdf5_file(hdf5_file &&other)
    : file_(other.file_)
{
    other.file_ = -1;
}

inline hdf5_file &hdf5_file::operator=(hdf5_file &&other)
{
    file_ = other.file_;
    other.file_ = -1;
    return *this;
}

inline auto hdf5_file::exists(const std::string &path) const
{
    return path == "/" || H5Lexists(file_, path.c_str(), H5P_DEFAULT) > 0;
}

inline void hdf5_file::remove(const std::string &path) const
{
    if (H5Ldelete(file_, path.c_str(), H5P_DEFAULT) < 0)
        throw std::runtime_error("Error deleting dataset. H5Ldelete failed.");
}

inline void hdf5_file::create_group(const std::string &path) const
{
    auto groups = utility::string::split(path, '/');

    if (groups.empty())
        return;

    std::string current_path;

    for (auto &group : groups)
    {
        current_path += "/" + group;
        if (!exists(current_path))
        {
            hdf5_scoped_create_group create_group(file_, current_path);
        }
    }
}

inline auto hdf5_file::get_hid() const
{
    return file_;
}

} // namespace hdf5
} // namespace aeon
