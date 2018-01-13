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

#pragma once

#include <aeon/common/noncopyable.h>
#include <hdf5.h>
#include <cstddef>
#include <string>

namespace aeon::hdf5
{

class hdf5_datatype;
class hdf5_file;
class hdf5_dataspace;
class hdf5_dataset_properties;

class hdf5_dataset_wrapper : common::noncopyable
{
public:
    hdf5_dataset_wrapper();
    explicit hdf5_dataset_wrapper(const hdf5_file &file, const std::string &path);
    explicit hdf5_dataset_wrapper(const hdf5_file &file, const std::string &path, const hdf5_datatype &datatype,
                                  const hdf5_dataspace &dataspace, const hdf5_dataset_properties &properties);
    ~hdf5_dataset_wrapper();

    hdf5_dataset_wrapper(hdf5_dataset_wrapper &&other);
    hdf5_dataset_wrapper &operator=(hdf5_dataset_wrapper &&other);

    auto get_handle() const -> hid_t;

private:
    hid_t handle_;
};

} // namespace aeon::hdf5
