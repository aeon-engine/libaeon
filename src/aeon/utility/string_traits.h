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
namespace utility
{
namespace string
{

template <typename T>
struct convert
{
};

template <>
struct convert<std::string>
{
    static std::string to(const std::string &v)
    {
        return v;
    }

    static std::string from(const std::string &v)
    {
        return v;
    }
};

template <>
struct convert<int>
{
    static std::string to(int v)
    {
        return std::to_string(v);
    }

    static int from(const std::string &v)
    {
        return std::stoi(v);
    }
};

template <>
struct convert<float>
{
    static std::string to(float v)
    {
        return std::to_string(v);
    }

    static float from(const std::string &v)
    {
        return std::stof(v);
    }
};

template <>
struct convert<bool>
{
    static std::string to(bool v)
    {
        return v ? "1" : "0";
    }

    static bool from(const std::string &v)
    {
        return v == "1" || v == "true";
    }
};

} // namespace string
} // namespace utility
} // namespace aeon
