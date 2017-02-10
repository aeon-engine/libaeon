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
#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

enum class hdf5_dataset_filltime
{
    alloc,
    never,
    ifset
};

class hdf5_dataset_properties : utility::noncopyable
{
public:
    explicit hdf5_dataset_properties();
    ~hdf5_dataset_properties();

    hdf5_dataset_properties(hdf5_dataset_properties &&other);
    hdf5_dataset_properties &operator=(hdf5_dataset_properties &&other);

    void set_filltime(const hdf5_dataset_filltime mode) const;

    auto get_handle() const;

private:
    hid_t handle_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_dataset_properties_impl.h>
