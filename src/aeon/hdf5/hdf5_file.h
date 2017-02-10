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
#include <hdf5.h>
#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

enum hdf5_file_open_mode
{
    create,
    read_only,
    read_write
};

class hdf5_file : public utility::noncopyable
{
public:
    hdf5_file();
    explicit hdf5_file(const std::string &path, const hdf5_file_open_mode mode);
    ~hdf5_file();

    hdf5_file(hdf5_file &&other);
    hdf5_file &operator=(hdf5_file &&other);

    auto exists(const std::string &path) const;

    void remove(const std::string &path) const;

    void create_group(const std::string &path) const;

    auto get_hid() const;

private:
    hid_t file_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_file_impl.h>
