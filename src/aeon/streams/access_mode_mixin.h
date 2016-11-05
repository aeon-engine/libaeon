/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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
namespace streams
{

/*!
 * The available access modes for the class that uses the access_mode_mixin.
 * This allows an implementation to for it's access permissions.
 *
 * This is implemented as an anonymous enum within a class, since enum classes
 * do not support bit flags at this moment.
 */
class access_mode
{
public:
    enum : int
    {
        none = 0x00,       /**< No access */
        read = 0x01,       /**< Read-Only */
        write = 0x02,      /**< Write-Only */
        read_write = 0x03, /**< Read-Write (Full access) */
        truncate = 0x04,   /**< Truncate */
    };
};

class access_mode_mixin
{
public:
    access_mode_mixin()
        : access_mode_(access_mode::none)
    {
    }

    access_mode_mixin(int access)
        : access_mode_(access)
    {
    }

    virtual ~access_mode_mixin() = default;

    access_mode_mixin(access_mode_mixin &&o) noexcept = default;
    access_mode_mixin &operator=(access_mode_mixin &&other) noexcept = default;

    virtual int get_access_mode() const
    {
        return access_mode_;
    }

    virtual bool is_readable() const
    {
        return (access_mode_ & access_mode::read) != 0;
    }

    virtual bool is_writable() const
    {
        return (access_mode_ & access_mode::write) != 0;
    }

    virtual bool is_truncated() const
    {
        return (access_mode_ & access_mode::truncate) != 0;
    }

protected:
    void set_access_mode(int access)
    {
        access_mode_ = access;
    }

    /*!
     * Bitflags representing the access mode of this stream.
     * May be read and or write.
     * \sa access_mode
     */
    int access_mode_;
};

} // namespace streams
} // namespace aeon
