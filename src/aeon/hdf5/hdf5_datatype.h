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

enum class hdf5_array_data_type
{
    uint8
};

enum class hdf5_array_byte_order
{
    little_endian
};

class hdf5_datatype : utility::noncopyable
{
public:
    hdf5_datatype();
    explicit hdf5_datatype(const hdf5_array_data_type data_type, const hdf5_array_byte_order byte_order);
    ~hdf5_datatype();

    hdf5_datatype(hdf5_datatype &&other);
    hdf5_datatype &operator=(hdf5_datatype &&other);

    auto get_handle() const;

private:
    hid_t handle_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_datatype_impl.h>
