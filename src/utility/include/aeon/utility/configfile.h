// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/idynamic_stream.h>
#include <aeon/common/string_traits.h>
#include <filesystem>
#include <exception>
#include <vector>
#include <string>
#include <map>

namespace aeon::utility
{

class configfile_exception : public std::exception
{
};

/*!
 * \brief Reader and writer for files in .ini file format
 *
 * Allows reading and writing configuration settings to a stream. Usually this
 * means a config ini file. If the config file contains syntax errors, messages
 * are logged to the console.
 */
class configfile
{
public:
    using entries = std::map<std::string, std::string>;

    /*!
     * Constructor
     */
    configfile() = default;

    /*!
     * Destructor
     */
    ~configfile() = default;

    configfile(configfile &&other) noexcept
        : entries_{std::move(other.entries_)}
    {
    }

    configfile &operator=(configfile &&other) noexcept
    {
        entries_ = std::move(other.entries_);
        return *this;
    }

    configfile(const configfile &) noexcept = delete;
    auto operator=(const configfile &) noexcept -> configfile & = delete;

    /*!
     * Check if the loaded config file has a certain entry key
     * \param key The entry key to be checked
     * \returns True if the entry was found
     */
    [[nodiscard]] bool has_entry(const std::string &key) const;

    /*!
     * Get a value.
     * \param key The entry key
     * \return Either the value of the entry of key, or throws an exception.
     */
    template <typename T>
    [[nodiscard]] auto get(const std::string &key) const
    {
        const auto itr = entries_.find(key);

        // If it could not find the key...
        if (itr == entries_.end())
            throw configfile_exception{};

        return common::string::convert<T>::from(itr->second);
    }

    /*!
     * Get a value.
     * \param key The entry key
     * \param default_val Default value. If the key is not found in the config file, the default value is returned.
     * \return Either the value of the entry of key, or the default value.
     */
    template <typename T>
    [[nodiscard]] auto get(const std::string &key, const T &default_val)
    {
        const auto itr = entries_.find(key);

        // If it could not find the key...
        if (itr == entries_.end())
        {
            set<T>(key, default_val);
            return default_val;
        }

        return common::string::convert<T>::from(itr->second);
    }

    /*!
     * Set a value
     * \param key The entry key
     * \param val The value.
     */
    template <typename T>
    void set(const std::string &key, const T &val)
    {
        entries_[key] = common::string::convert<T>::to(val);
    }

    /*!
     * Load a config from a stream
     * \param stream The configfile to load
     */
    void load(streams::idynamic_stream &stream);

    /*!
     * Save a config to a stream
     * \param stream The configfile to save.
     */
    void save(streams::idynamic_stream &stream) const;

    /*!
     * Load a config from a file
     * \param path The configfile path to load
     */
    void load(const std::filesystem::path &path);

    /*!
     * Save a config to a file
     * \param path The configfile path to save.
     *             File will be overwritten if it already exists.
     */
    void save(const std::filesystem::path &path) const;

    /*!
     * Load a config from memory
     * \param data Vector to load from. It will be treated as a text
     *             file in memory. This means that \n or \n\r will
     *             be treated as seperators.
     */
    void load(const std::vector<char> &data);

    /*!
     * Save a config to memory
     * \param data Vector to save to. It will be treated as a text
     *             file in memory. This means that \n or \n\r will
     *             be treated as seperators. The vector will be
     *             cleared first.
     */
    void save(std::vector<char> &data) const;

    /*!
     * Begin iterator for foreach loops.
     */
    [[nodiscard]] auto begin() const noexcept
    {
        return entries_.cbegin();
    }

    /*!
     * End iterator for foreach loops.
     */
    [[nodiscard]] auto end() const noexcept
    {
        return entries_.cend();
    }

private:
    /*!
     * Handle a line when loading a file
     */
    void __read_line(const std::string &line);

    entries entries_;
};

} // namespace aeon::utility
