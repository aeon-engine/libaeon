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
#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

class hdf5_scoped_create_group : public utility::noncopyable
{
public:
    explicit hdf5_scoped_create_group(const hid_t file, const std::string &name);
    ~hdf5_scoped_create_group();

    hdf5_scoped_create_group(hdf5_scoped_create_group &&other);
    hdf5_scoped_create_group &operator=(hdf5_scoped_create_group &&other);

private:
    hid_t handle_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_scoped_create_group_impl.h>
