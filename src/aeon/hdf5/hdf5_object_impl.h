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

inline hdf5_object::hdf5_object(const std::string &name, const H5O_info_t *info)
    : name_(name)
    , type_(hdf5_object_type::invalid)
    , last_access_time_(std::chrono::system_clock::from_time_t(info->atime))
    , modification_time_(std::chrono::system_clock::from_time_t(info->mtime))
    , metadata_modification_time_(std::chrono::system_clock::from_time_t(info->ctime))
    , created_time_(std::chrono::system_clock::from_time_t(info->btime))
{
    switch (info->type)
    {
        case H5O_TYPE_GROUP:
            type_ = hdf5_object_type::group;
            break;
        case H5O_TYPE_DATASET:
            type_ = hdf5_object_type::dataset;
            break;
        case H5O_TYPE_NAMED_DATATYPE:
            type_ = hdf5_object_type::named_datatype;
            break;
        case H5O_TYPE_NTYPES:
        case H5O_TYPE_UNKNOWN:
        default:
            type_ = hdf5_object_type::invalid;
    }
}

inline auto hdf5_object::get_name() const
{
    return name_;
}

inline auto hdf5_object::get_type() const
{
    return type_;
}

inline auto hdf5_object::get_last_access_time() const
{
    return last_access_time_;
}

inline auto hdf5_object::get_modification_time() const
{
    return modification_time_;
}

inline auto hdf5_object::get_metadata_modification_time() const
{
    return metadata_modification_time_;
}

inline auto hdf5_object::get_created_time() const
{
    return created_time_;
}

} // namespace hdf5
} // namespace aeon
