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

#include <aeon/hdf5/hdf5_object.h>

namespace aeon::hdf5
{

namespace detail
{

auto h5otype_to_object_type(const H5O_type_t type)
{
    switch (type)
    {
        case H5O_TYPE_GROUP:
            return hdf5_object_type::group;
        case H5O_TYPE_DATASET:
            return hdf5_object_type::dataset;
        case H5O_TYPE_NAMED_DATATYPE:
            return hdf5_object_type::named_datatype;
        case H5O_TYPE_NTYPES:
        case H5O_TYPE_UNKNOWN:
        default:
            return hdf5_object_type::invalid;
    }
}

} // namespace detail

hdf5_object::hdf5_object(const std::string &name, const H5O_info_t *info)
    : name_(name)
    , type_(hdf5_object_type::invalid)
    , last_access_time_(std::chrono::system_clock::from_time_t(info->atime))
    , modification_time_(std::chrono::system_clock::from_time_t(info->mtime))
    , metadata_modification_time_(std::chrono::system_clock::from_time_t(info->ctime))
    , created_time_(std::chrono::system_clock::from_time_t(info->btime))
{
    type_ = detail::h5otype_to_object_type(info->type);
}

auto hdf5_object::get_name() const -> std::string
{
    return name_;
}

auto hdf5_object::get_type() const -> hdf5_object_type
{
    return type_;
}

auto hdf5_object::get_last_access_time() const -> std::chrono::system_clock::time_point
{
    return last_access_time_;
}

auto hdf5_object::get_modification_time() const -> std::chrono::system_clock::time_point
{
    return modification_time_;
}

auto hdf5_object::get_metadata_modification_time() const -> std::chrono::system_clock::time_point
{
    return metadata_modification_time_;
}

auto hdf5_object::get_created_time() const -> std::chrono::system_clock::time_point
{
    return created_time_;
}

} // namespace aeon::hdf5
