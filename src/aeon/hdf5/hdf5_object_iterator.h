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

#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

enum class iterate_mode
{
    normal,
    recursive
};

class hdf5_file;

class hdf5_iterate : public utility::noncopyable
{
public:
    hdf5_iterate();

    explicit hdf5_iterate(const hdf5_file &file, const iterate_mode mode = iterate_mode::normal);

    explicit hdf5_iterate(const hdf5_file &file, const std::string &path,
                          const iterate_mode mode = iterate_mode::normal);

    ~hdf5_iterate() = default;

    hdf5_iterate(hdf5_iterate &&other);
    hdf5_iterate &operator=(hdf5_iterate &&other);

    const auto &get_children() const;

    auto begin() const;
    auto end() const;

    auto cbegin() const;
    auto cend() const;

private:
    static herr_t __iterate_callback(hid_t obj, const char *name, const H5O_info_t *info, void *op_data);

    herr_t __iterate_callback(const std::string &name, const H5O_info_t *info);

    iterate_mode mode_;
    std::vector<hdf5_object> children_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_object_iterator_impl.h>
