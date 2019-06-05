// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

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

    [[nodiscard]] auto str() const -> std::string
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
