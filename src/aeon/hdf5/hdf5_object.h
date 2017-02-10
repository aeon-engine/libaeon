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

#include <hdf5.h>
#include <chrono>

namespace aeon
{
namespace hdf5
{

enum class hdf5_object_type
{
    group,
    dataset,
    named_datatype,
    invalid
};

class hdf5_object
{
    friend class hdf5_iterate;

public:
    hdf5_object() = default;
    explicit hdf5_object(const std::string &name, const H5O_info_t *info);
    ~hdf5_object() = default;

    auto get_name() const;

    auto get_type() const;

    auto get_last_access_time() const;

    auto get_modification_time() const;

    auto get_metadata_modification_time() const;

    auto get_created_time() const;

private:
    std::string name_;
    hdf5_object_type type_;
    std::chrono::system_clock::time_point last_access_time_;
    std::chrono::system_clock::time_point modification_time_;
    std::chrono::system_clock::time_point metadata_modification_time_;
    std::chrono::system_clock::time_point created_time_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_object_impl.h>
