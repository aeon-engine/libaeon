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

class stream_name_mixin
{
public:
    stream_name_mixin()
        : name_(AEON_STREAM_DEFAULT_NAME)
        , has_name_(false)
    {
    }

    explicit stream_name_mixin(const std::string &name)
        : name_(name)
        , has_name_(true)
    {
    }

    virtual ~stream_name_mixin() = default;

    stream_name_mixin(stream_name_mixin &&o) noexcept = default;
    stream_name_mixin &operator=(stream_name_mixin &&other) noexcept = default;

    std::string get_name() const
    {
        return name_;
    }

    void set_name(const std::string &name)
    {
        name_ = name;
    }

    bool has_name() const
    {
        return has_name_;
    }

private:
    std::string name_;
    bool has_name_;
};

} // namespace streams
} // namespace aeon
