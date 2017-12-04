/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <aeon/hdf5/hdf5_object_iterator.h>
#include <aeon/hdf5/hdf5_file.h>
#include <stdexcept>

namespace aeon::hdf5
{

hdf5_iterate::hdf5_iterate()
    : mode_(iterate_mode::normal)
{
}

hdf5_iterate::hdf5_iterate(const hdf5_file &file, const iterate_mode mode)
    : mode_(mode)
{
    auto result = H5Ovisit(file.get_hid(), H5_INDEX_NAME, H5_ITER_NATIVE, __iterate_callback, this);

    if (result < 0)
        throw std::runtime_error("H5Ovisit failed.");
}

hdf5_iterate::hdf5_iterate(const hdf5_file &file, const std::string &path, const iterate_mode mode)
    : mode_(mode)
{
    auto result = H5Ovisit_by_name(file.get_hid(), path.c_str(), H5_INDEX_NAME, H5_ITER_NATIVE, __iterate_callback,
                                   this, H5P_DEFAULT);

    if (result < 0)
        throw std::runtime_error("H5Ovisit_by_name failed.");
}

hdf5_iterate::hdf5_iterate(hdf5_iterate &&other)
    : mode_(other.mode_)
    , children_(std::move(other.children_))
{
}

hdf5_iterate &hdf5_iterate::operator=(hdf5_iterate &&other)
{
    mode_ = other.mode_;
    children_ = std::move(other.children_);
    return *this;
}

herr_t hdf5_iterate::__iterate_callback(hid_t obj, const char *name, const H5O_info_t *info, void *op_data)
{
    auto hdf5_iterate_instance = static_cast<hdf5_iterate *>(op_data);
    return hdf5_iterate_instance->__iterate_callback(name, info);
}

herr_t hdf5_iterate::__iterate_callback(const std::string &name, const H5O_info_t *info)
{
    if (name == ".")
        return 0;

    if (mode_ == iterate_mode::normal && name.find_first_of('/') != std::string::npos)
        return 0;

    children_.emplace_back(name, info);
    return 0;
}

} // namespace aeon::hdf5
