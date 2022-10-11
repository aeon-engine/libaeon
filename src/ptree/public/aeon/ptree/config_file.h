// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <optional>
#include <stdexcept>

namespace aeon::ptree
{

class config_file_exception : public std::exception
{
};

template <typename T>
concept config_file_value = std::is_same_v<T, bool> || std::is_integral_v<T> || std::is_floating_point_v<T> ||
                            std::is_same_v<T, common::string> || std::is_same_v<T, common::uuid>;

/*!
 * Wrapper for reading and writing config file settings, for example for use in
 * conjunction with the ini format serialization.
 *
 * The config format poses some limitations on the format of the ptree.
 * - The root ptree must be an object type
 * - The keys of this root are used as the segments
 * - The values must also be an object type as their key-values are mapped
 *   directly to key value pairs under the segments.
 * - Values can not be an array or object.
 *
 * This wrapper will use this format for reading and writing to the property tree.
 */
class config_file final
{
public:
    explicit config_file(property_tree &pt);
    ~config_file() noexcept = default;

    config_file(const config_file &) = default;
    auto operator=(const config_file &) -> config_file & = default;

    config_file(config_file &&) noexcept = default;
    auto operator=(config_file &&) noexcept -> config_file & = default;

    /*!
     * Check if the loaded config file has a certain entry key
     * \param header The header to be checked
     * \returns True if the entry was found
     */
    [[nodiscard]] auto has_header(const common::string &header) const noexcept -> bool;

    /*!
     * Check if the loaded config file has a certain entry key
     * \param header The header to look for
     * \param key The entry key to be checked
     * \returns True if the entry was found
     */
    [[nodiscard]] auto has_entry(const common::string &header,
                                 const common::string &key) // NOLINT(bugprone-exception-escape)
        const noexcept -> bool;

    /*!
     * Get a value.
     * \param header The header of the key
     * \param key The entry key
     * \return Either the value of the entry of key, nullopt
     */
    template <config_file_value T>
    [[nodiscard]] auto get(const common::string &header, const common::string &key) // NOLINT(bugprone-exception-escape)
        const noexcept -> std::optional<T>;

    /*!
     * Get a value.
     * \param header The header of the key
     * \param key The entry key
     * \param default_val Default value. If the key is not found in the config file, the default value is returned.
     * \return Either the value of the entry of key, or the default value.
     */
    template <config_file_value T>
    [[nodiscard]] auto get(const common::string &header, const common::string &key, const T &default_val) -> T;

    /*!
     * Get a value, or throw an exception if it does not exist
     * \param header The header of the key
     * \param key The entry key
     * \return Either the value of the entry of key, or throws std::invalid_argument
     */
    template <config_file_value T>
    [[nodiscard]] auto get_or_except(const common::string &header, const common::string &key) const -> T;

    /*!
     * Set a value
     * \param header The header of the key
     * \param key The entry key
     * \param val The value.
     */
    template <config_file_value T>
    void set(const common::string &header, const common::string &key, const T &val);

private:
    property_tree *pt_;
};

} // namespace aeon::ptree

#include <aeon/ptree/impl/config_file_impl.h>
