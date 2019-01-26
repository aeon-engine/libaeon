// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <array>
#include <cstdint>
#include <string>

namespace aeon::utility
{

/*!
 * UUID class based on boost::uuid.
 */
class uuid
{
public:
    using value_type = std::uint8_t;
    using data_type = std::array<value_type, 16>;

    enum class variant_type
    {
        variant_ncs,
        variant_rfc_4122,
        variant_microsoft,
        variant_future
    };

    enum class version_type
    {
        version_unknown = -1,
        version_time_based = 1,
        version_dce_security = 2,
        version_name_based_md5 = 3,
        version_random_number_based = 4,
        version_name_based_sha1 = 5
    };

    uuid() noexcept;
    explicit uuid(const std::string &str);
    ~uuid() noexcept;

    uuid(const uuid &) noexcept = default;
    auto operator=(const uuid &) noexcept -> uuid & = default;

    uuid(uuid &&) noexcept = default;
    auto operator=(uuid &&) noexcept -> uuid & = default;

    auto begin() noexcept -> data_type::iterator;
    auto begin() const noexcept -> data_type::const_iterator;
    auto end() noexcept -> data_type::iterator;
    auto end() const noexcept -> data_type::const_iterator;

    bool is_nil() const noexcept;

    auto variant() const noexcept -> variant_type;

    auto version() const noexcept -> version_type;

    auto str() const -> std::string;

    auto size() const noexcept -> std::size_t;

    static auto generate() -> uuid;

    static auto nil() noexcept -> uuid;

    data_type data;
};

bool operator==(uuid const &lhs, uuid const &rhs) noexcept;
bool operator<(uuid const &lhs, uuid const &rhs) noexcept;

inline bool operator!=(uuid const &lhs, uuid const &rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator>(uuid const &lhs, uuid const &rhs) noexcept
{
    return rhs < lhs;
}
inline bool operator<=(uuid const &lhs, uuid const &rhs) noexcept
{
    return !(rhs < lhs);
}

inline bool operator>=(uuid const &lhs, uuid const &rhs) noexcept
{
    return !(lhs < rhs);
}

} // namespace aeon::utility
