// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/flags.h>

namespace aeon::streams
{

/*!
 * The available access modes for the class that uses the access_mode_mixin.
 * This allows an implementation to for it's access permissions.
 */
enum class access_mode
{
    none = 0x00,       /**< No access */
    read = 0x01,       /**< Read-Only */
    write = 0x02,      /**< Write-Only */
    read_write = 0x03, /**< Read-Write (Full access) */
    truncate = 0x04,   /**< Truncate */
};

aeon_declare_flag_operators(access_mode)

    class access_mode_mixin
{
public:
    access_mode_mixin()
        : access_mode_{access_mode::none}
    {
    }

    explicit access_mode_mixin(const common::flags<access_mode> access)
        : access_mode_{access}
    {
    }

    virtual ~access_mode_mixin() = default;

    access_mode_mixin(access_mode_mixin &&) = default;
    auto operator=(access_mode_mixin &&) -> access_mode_mixin & = default;

    access_mode_mixin(const access_mode_mixin &) = default;
    auto operator=(const access_mode_mixin &) -> access_mode_mixin & = default;

    virtual auto get_access_mode() const noexcept -> common::flags<access_mode>
    {
        return access_mode_;
    }

    virtual auto is_readable() const noexcept -> bool
    {
        return access_mode_.is_set(access_mode::read);
    }

    virtual auto is_writable() const noexcept -> bool
    {
        return access_mode_.is_set(access_mode::write);
    }

    virtual auto is_truncated() const noexcept -> bool
    {
        return access_mode_.is_set(access_mode::truncate);
    }

protected:
    void set_access_mode(const common::flags<access_mode> access) noexcept
    {
        access_mode_ = access;
    }

    /*!
     * Bitflags representing the access mode of this stream.
     * May be read and or write.
     * \sa access_mode
     */
    common::flags<access_mode> access_mode_;
};

} // namespace aeon::streams
