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
#include <cstddef>
#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

class dataset;

class hdf5_dataspace : utility::noncopyable
{
public:
    hdf5_dataspace();
    explicit hdf5_dataspace(const hid_t dataset_handle);
    explicit hdf5_dataspace(const std::size_t reserve_size);
    ~hdf5_dataspace();

    hdf5_dataspace(hdf5_dataspace &&other);
    hdf5_dataspace &operator=(hdf5_dataspace &&other);

    auto get_handle() const;

    auto get_size() const;

private:
    hid_t handle_;
    std::size_t size_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_dataspace_impl.h>
