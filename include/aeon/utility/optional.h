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
namespace utility
{

class optional_value_exception : public std::exception
{
};

template <typename T>
class optional
{
public:
    optional()
        : value_()
        , has_value_(false)
    {
    }

    optional(const T &val)
        : value_(val)
        , has_value_(true)
    {
    }

    bool has_value() const
    {
        return has_value_;
    }

    const T &get_value() const
    {
        if (!has_value_)
            throw optional_value_exception();

        return value_;
    }

    void reset()
    {
        has_value_ = false;
    }

    operator T() const
    {
        if (!has_value_)
            throw optional_value_exception();

        return value_;
    }

private:
    T value_;
    bool has_value_;
};

} // namespace utility
} // namespace aeon
