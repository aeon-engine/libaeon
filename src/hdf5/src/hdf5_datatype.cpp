/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/hdf5/hdf5_datatype.h>
#include <cassert>
#include <stdexcept>

namespace aeon::hdf5
{

hdf5_datatype::hdf5_datatype()
    : handle_(-1)
{
}

hdf5_datatype::hdf5_datatype(const hdf5_array_data_type data_type, const hdf5_array_byte_order byte_order)
    : handle_(-1)
{
    assert(data_type == hdf5_array_data_type::uint8);
    assert(byte_order == hdf5_array_byte_order::little_endian);

    handle_ = H5Tcopy(H5T_NATIVE_UINT8);
    auto status = H5Tset_order(handle_, H5T_ORDER_LE);

    if (status < 0)
        throw std::runtime_error("H5Tset_order failed.");
}

hdf5_datatype::~hdf5_datatype()
{
    if (handle_ >= 0)
        H5Tclose(handle_);
}

hdf5_datatype::hdf5_datatype(hdf5_datatype &&other)
    : handle_(other.handle_)
{
    other.handle_ = -1;
}

hdf5_datatype &hdf5_datatype::operator=(hdf5_datatype &&other)
{
    handle_ = other.handle_;
    other.handle_ = -1;
    return *this;
}

auto hdf5_datatype::get_handle() const -> hid_t
{
    return handle_;
}

} // namespace aeon::hdf5
