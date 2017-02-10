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
#include <string>
#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

class hdf5_datatype;
class hdf5_file;
class hdf5_dataspace;
class hdf5_dataset_properties;

class hdf5_dataset_wrapper : utility::noncopyable
{
public:
    hdf5_dataset_wrapper();
    explicit hdf5_dataset_wrapper(const hdf5_file &file, const std::string &path);
    explicit hdf5_dataset_wrapper(const hdf5_file &file, const std::string &path, const hdf5_datatype &datatype,
                                  const hdf5_dataspace &dataspace, const hdf5_dataset_properties &properties);
    ~hdf5_dataset_wrapper();

    hdf5_dataset_wrapper(hdf5_dataset_wrapper &&other);
    hdf5_dataset_wrapper &operator=(hdf5_dataset_wrapper &&other);

    auto get_handle() const;

private:
    hid_t handle_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_dataset_wrapper_impl.h>
