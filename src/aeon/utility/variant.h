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

class variant
{
public:
    enum class variant_type
    {
        variant_nil,
        variant_int,
        variant_float,
        variant_bool,
        variant_string
    };

    variant()
        : int_value_(0)
        , float_value_(0.0f)
        , bool_value_(false)
        , string_value_("")
        , type_(variant_type::variant_nil)
    {
    }

    variant(const int &value)
        : int_value_(value)
        , float_value_(static_cast<float>(value))
        , bool_value_(value >= 0)
        , string_value_(std::to_string(value))
        , type_(variant_type::variant_int)
    {
    }

    variant(const float &value)
        : int_value_(static_cast<int>(value))
        , float_value_(value)
        , bool_value_(value >= 0.0f)
        , string_value_(std::to_string(value))
        , type_(variant_type::variant_float)
    {
    }

    variant(const bool &value)
        : int_value_(value == false ? 0 : 1)
        , float_value_(value == false ? 0.0f : 1.0f)
        , bool_value_(value)
        , string_value_(value == false ? "false" : "true")
        , type_(variant_type::variant_bool)
    {
    }

    variant(const std::string &value)
        : int_value_(0)
        , float_value_(0)
        , bool_value_(false)
        , string_value_(value)
        , type_(variant_type::variant_string)
    {
        if (value == "true")
        {
            int_value_ = 1;
            float_value_ = 1.0f;
            bool_value_ = true;
        }
        else if (value == "false")
        {
            int_value_ = 0;
            float_value_ = 0.0f;
            bool_value_ = false;
        }
        else
        {
            try
            {
                float_value_ = std::stof(string_value_);
                int_value_ = static_cast<int>(float_value_);
                bool_value_ = float_value_ >= 0.0;
            }
            catch (std::exception &)
            {
                float_value_ = 0.0f;
                int_value_ = 0;
                bool_value_ = false;
            }
        }
    }

    const int &int_value() const
    {
        return int_value_;
    }

    const float &float_value() const
    {
        return float_value_;
    }

    const bool &bool_value() const
    {
        return bool_value_;
    }

    const std::string &string_value() const
    {
        return string_value_;
    }

    const variant_type &type() const
    {
        return type_;
    }

private:
    int int_value_;
    float float_value_;
    bool bool_value_;
    std::string string_value_;
    variant_type type_;
};

} // namespace utility
} // namespace aeon
