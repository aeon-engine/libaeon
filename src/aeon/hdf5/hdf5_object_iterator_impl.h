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

inline hdf5_iterate::hdf5_iterate()
    : mode_(iterate_mode::normal)
{
}

inline hdf5_iterate::hdf5_iterate(const hdf5_file &file, const iterate_mode mode)
    : mode_(mode)
{
    auto result = H5Ovisit(file.get_hid(), H5_INDEX_NAME, H5_ITER_NATIVE, __iterate_callback, this);

    if (result < 0)
        throw std::runtime_error("H5Ovisit failed.");
}

inline hdf5_iterate::hdf5_iterate(const hdf5_file &file, const std::string &path, const iterate_mode mode)
    : mode_(mode)
{
    auto result = H5Ovisit_by_name(file.get_hid(), path.c_str(), H5_INDEX_NAME, H5_ITER_NATIVE, __iterate_callback,
                                   this, H5P_DEFAULT);

    if (result < 0)
        throw std::runtime_error("H5Ovisit_by_name failed.");
}

inline hdf5_iterate::hdf5_iterate(hdf5_iterate &&other)
    : mode_(other.mode_)
    , children_(std::move(other.children_))
{
}

inline hdf5_iterate &hdf5_iterate::operator=(hdf5_iterate &&other)
{
    mode_ = other.mode_;
    children_ = std::move(other.children_);
    return *this;
}

inline const auto &hdf5_iterate::get_children() const
{
    return children_;
}

inline herr_t hdf5_iterate::__iterate_callback(hid_t obj, const char *name, const H5O_info_t *info, void *op_data)
{
    auto hdf5_iterate_instance = static_cast<hdf5_iterate *>(op_data);
    return hdf5_iterate_instance->__iterate_callback(name, info);
}

inline herr_t hdf5_iterate::__iterate_callback(const std::string &name, const H5O_info_t *info)
{
    if (name == ".")
        return 0;

    if (mode_ == iterate_mode::normal && name.find_first_of('/') != std::string::npos)
        return 0;

    children_.emplace_back(name, info);
    return 0;
}

inline auto hdf5_iterate::begin() const
{
    return children_.begin();
}

inline auto hdf5_iterate::end() const
{
    return children_.end();
}

inline auto hdf5_iterate::cbegin() const
{
    return children_.cbegin();
}

inline auto hdf5_iterate::cend() const
{
    return children_.cend();
}

} // namespace hdf5
} // namespace aeon
