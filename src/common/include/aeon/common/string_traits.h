// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <string>

namespace aeon::common::string
{

template <typename T>
struct convert
{
};

template <>
struct convert<std::string>
{
    [[nodiscard]] static auto to(const std::string &v)
    {
        return v;
    }

    [[nodiscard]] static auto from(const std::string &v)
    {
        return v;
    }
};

template <>
struct convert<int>
{
    [[nodiscard]] static auto to(const int v)
    {
        return std::to_string(v);
    }

    [[nodiscard]] static auto from(const std::string &v)
    {
        return std::stoi(v);
    }
};

template <>
struct convert<float>
{
    [[nodiscard]] static auto to(const float v)
    {
        return std::to_string(v);
    }

    [[nodiscard]] static auto from(const std::string &v)
    {
        return std::stof(v);
    }
};

template <>
struct convert<bool>
{
    [[nodiscard]] static auto to(const bool v)
    {
        return v ? "1" : "0";
    }

    [[nodiscard]] static auto from(const std::string &v)
    {
        return v == "1" || v == "true";
    }
};

} // namespace aeon::common::string
