// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <string>

namespace aeon::common
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
        : int_value_{}
        , float_value_{}
        , bool_value_{}
        , string_value_{}
        , type_(variant_type::variant_nil)
    {
    }

    variant(const int &value)
        : int_value_{value}
        , float_value_{static_cast<float>(value)}
        , bool_value_{value >= 0}
        , string_value_{std::to_string(value)}
        , type_{variant_type::variant_int}
    {
    }

    variant(const float &value)
        : int_value_{static_cast<int>(value)}
        , float_value_{value}
        , bool_value_{value >= 0.0f}
        , string_value_{std::to_string(value)}
        , type_{variant_type::variant_float}
    {
    }

    variant(const bool &value)
        : int_value_{value ? 1 : 0}
        , float_value_{value ? 1.0f : 0.0f}
        , bool_value_{value}
        , string_value_{value ? "true" : "false"}
        , type_{variant_type::variant_bool}
    {
    }

    variant(std::string value)
        : int_value_{}
        , float_value_{}
        , bool_value_{}
        , string_value_{std::move(value)}
        , type_{variant_type::variant_string}
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

    auto int_value() const noexcept
    {
        return int_value_;
    }

    auto float_value() const noexcept
    {
        return float_value_;
    }

    auto bool_value() const noexcept
    {
        return bool_value_;
    }

    const auto &string_value() const noexcept
    {
        return string_value_;
    }

    auto type() const noexcept
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

} // namespace aeon::common
