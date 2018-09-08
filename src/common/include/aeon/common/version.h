/*
 * Copyright (c) 2012-2018 Robin Degen
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

#pragma once

#include <tuple>
#include <ostream>
#include <string>

namespace aeon::common
{

class version
{
public:
    version() noexcept
        : major{}
        , minor{}
        , patch{}
        , build{}
    {
    }

    explicit version(const int major, const int minor) noexcept
        : major{major}
        , minor{minor}
        , patch{}
        , build{}
    {
    }

    explicit version(const int major, const int minor, const int patch) noexcept
        : major{major}
        , minor{minor}
        , patch{patch}
        , build{}
    {
    }

    explicit version(const int major, const int minor, const int patch, const int build) noexcept
        : major{major}
        , minor{minor}
        , patch{patch}
        , build{build}
    {
    }

    ~version() = default;

    version(const version &) noexcept = default;
    auto operator=(const version &) noexcept -> version & = default;

    version(version &&) noexcept = default;
    auto operator=(version &&) noexcept -> version & = default;

    auto str() const -> std::string
    {
        std::string version;
        version.reserve(7); // Typically 1.2.3.4
        version += std::to_string(major);
        version += '.';
        version += std::to_string(minor);
        version += '.';
        version += std::to_string(patch);
        version += '.';
        version += std::to_string(build);
        return version;
    }

    int major;
    int minor;
    int patch;
    int build;
};

inline auto operator<(const version &lhs, const version &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) < std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

inline auto operator<=(const version &lhs, const version &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) <= std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

inline auto operator>(const version &lhs, const version &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) > std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

inline auto operator>=(const version &lhs, const version &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) >= std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

inline auto operator==(const version &lhs, const version &rhs) noexcept -> bool
{
    return lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.patch == rhs.patch && lhs.build == rhs.build;
}

inline auto operator!=(const version &lhs, const version &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

inline auto operator<<(std::ostream &os, const version &v) -> std::ostream &
{
    return os << v.major << "." << v.minor << "." << v.patch << "." << v.build;
}

} // namespace aeon::common
