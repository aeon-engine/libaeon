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

#include <string>
#include <vector>
#include <hdf5.h>
#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

class hdf5_file;

class hdf5_dataset : utility::noncopyable
{
public:
    hdf5_dataset();
    explicit hdf5_dataset(hdf5_file &file, const std::string &path);
    ~hdf5_dataset();

    hdf5_dataset(hdf5_dataset &&other);
    hdf5_dataset &operator=(hdf5_dataset &&other);

    void write(const std::uint8_t *data, const std::size_t size);
    void write(const std::vector<std::uint8_t> &data);

    void read(std::vector<std::uint8_t> &data);

private:
    hdf5_file *file_;
    hdf5_datatype datatype_;
    hdf5_dataset_properties properties_;
    std::string path_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_dataset_impl.h>
