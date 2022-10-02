// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <optional>
#include <stdexcept>

namespace aeon::common
{

class uuid_parse_exception : public std::exception
{
};

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
    explicit uuid(data_type data) noexcept;
    ~uuid() noexcept;

    uuid(const uuid &) noexcept = default;
    auto operator=(const uuid &) noexcept -> uuid & = default;

    uuid(uuid &&) noexcept = default;
    auto operator=(uuid &&) noexcept -> uuid & = default;

    [[nodiscard]] auto begin() noexcept -> data_type::iterator;
    [[nodiscard]] auto begin() const noexcept -> data_type::const_iterator;
    [[nodiscard]] auto end() noexcept -> data_type::iterator;
    [[nodiscard]] auto end() const noexcept -> data_type::const_iterator;

    [[nodiscard]] auto is_nil() const noexcept -> bool;

    [[nodiscard]] auto variant() const noexcept -> variant_type;

    [[nodiscard]] auto version() const noexcept -> version_type;

    [[nodiscard]] auto str() const -> std::string;

    [[nodiscard]] auto u8str() const -> std::u8string;

    [[nodiscard]] auto size() const noexcept -> std::size_t;

    [[nodiscard]] static auto generate() noexcept -> uuid;

    [[nodiscard]] static auto nil() noexcept -> uuid;

    [[nodiscard]] static auto parse(const std::string_view &str) -> uuid;
    [[nodiscard]] static auto try_parse(const std::string_view &str) noexcept -> std::optional<uuid>;

    [[nodiscard]] operator bool() const noexcept;

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

} // namespace aeon::common
