// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/chrono/calendar.h>
#include <variant>
#include <cstdint>
#include <string>
#include <any>

namespace aeon::variant
{

class converting_variant final
{
public:
    enum class type : std::uint32_t
    {
        unknown,
        int8,
        uint8,
        int16,
        uint16,
        int32,
        uint32,
        int64,
        uint64,
        float_t,
        double_t,
        boolean,
        string,
        calendar,
        user
    };

    converting_variant() noexcept;

    explicit converting_variant(const type t) noexcept;

    template <typename T, std::enable_if_t<!std::is_same_v<converting_variant, T>, int> = 0>
    converting_variant(T &&value, const int user_index = 0);

    template <typename T, std::enable_if_t<!std::is_same_v<converting_variant, T>, int> = 0>
    converting_variant(const T &value, const int user_index = 0);

    converting_variant(const char *const str);

    /*!
     * Assumes a gmt/utc timezone. If another timezone is required, construct the variant with an explicit calendar
     * instance.
     */
    converting_variant(const std::chrono::system_clock::time_point utc_time);

    ~converting_variant() = default;

    converting_variant(const converting_variant &other) = default;
    auto operator=(const converting_variant &other) -> converting_variant & = default;

    converting_variant(converting_variant &&other) noexcept = default;
    auto operator=(converting_variant &&other) noexcept -> converting_variant & = default;

    [[nodiscard]] auto type() const noexcept -> type;
    [[nodiscard]] auto is_user_type() const noexcept -> bool;

    /*!
     * Returns the index set by set_value when using a user defined type.
     * Returns -1 if the variant isn't a user defined type.
     */
    [[nodiscard]] auto user_index() const noexcept -> int;
    [[nodiscard]] auto is_null() const noexcept -> bool;

    template <typename T>
    void set_value(T &&value, const int user_index = 0);

    template <typename T>
    void set_value(const T &value, const int user_index = 0);

    /*!
     * Get the value of the variant. If a user type is set, no conversion
     * will be done and it is assumed that T is the user type that was set.
     */
    template <typename T>
    [[nodiscard]] auto get_value() const -> T;

    /*!
     * Get the value for a user type and convert it to something else
     */
    template <typename from_t, typename to_t>
    [[nodiscard]] auto get_value() const -> to_t;

    /*!
     * Convert the internal value to the given type if possible. If not, an exception is thrown.
     */
    template <typename T>
    void convert_value();

    /*!
     * Convert the internal value for a user type to the given type if possible. If not, an exception is thrown.
     */
    template <typename from_t, typename to_t>
    void convert_value();

    /*!
     * Get the internal std::variant.
     */
    [[nodiscard]] const auto &get_variant_value() const noexcept
    {
        return data_;
    }

private:
    template <typename from_t, typename to_t>
    [[nodiscard]] auto get_value_internal() const -> to_t;

    template <typename from_t, typename to_t>
    [[nodiscard]] auto get_user_value_internal() const -> to_t;

    std::variant<std::monostate, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t,
                 std::int64_t, std::uint64_t, float, double, std::string, chrono::calendar, std::any, bool>
        data_;

    std::uint32_t type_ : 8;
    std::uint32_t user_index_ : 24;
};

} // namespace aeon::variant

#include <aeon/variant/impl/converting_variant_impl.h>
