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

inline hdf5_datatype::hdf5_datatype()
    : handle_(-1)
{
}

inline hdf5_datatype::hdf5_datatype(const hdf5_array_data_type data_type, const hdf5_array_byte_order byte_order)
    : handle_(-1)
{
    assert(data_type == hdf5_array_data_type::uint8);
    assert(byte_order == hdf5_array_byte_order::little_endian);

    handle_ = H5Tcopy(H5T_NATIVE_UINT8);
    auto status = H5Tset_order(handle_, H5T_ORDER_LE);

    if (status < 0)
        throw std::runtime_error("H5Tset_order failed.");
}

inline hdf5_datatype::~hdf5_datatype()
{
    if (handle_ >= 0)
        H5Tclose(handle_);
}

inline hdf5_datatype::hdf5_datatype(hdf5_datatype &&other)
    : handle_(other.handle_)
{
    other.handle_ = -1;
}

inline hdf5_datatype &hdf5_datatype::operator=(hdf5_datatype &&other)
{
    handle_ = other.handle_;
    other.handle_ = -1;
    return *this;
}

inline auto hdf5_datatype::get_handle() const
{
    return handle_;
}

} // namespace hdf5
} // namespace aeon
