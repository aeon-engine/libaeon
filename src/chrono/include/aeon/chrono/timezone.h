// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/chrono/offset.h>
#include <memory>
#include <string>
#include <vector>
#include <chrono>

namespace aeon::chrono
{

class timezone_impl;

class timezone final
{
    friend class calendar;

public:
    ~timezone();

    timezone(const timezone &other);
    auto operator=(const timezone &other) -> timezone &;

    timezone(timezone &&) noexcept;
    auto operator=(timezone &&) noexcept -> timezone &;

    auto operator==(const timezone &other) const -> bool;
    auto operator!=(const timezone &other) const -> bool;

    /*!
     * Get the unix tz name (IANA Olson)
     * For example: "Europe/Amsterdam" or "America/New_York"
     */
    [[nodiscard]] auto id() const -> std::string;

    /*!
     * Returns true if the current timezone uses daylight saving time
     */
    [[nodiscard]] auto uses_dst() const -> bool;

    /*!
     * Returns the amount of time in milliseconds to be added to local standard time to get local wall clock time.
     */
    [[nodiscard]] auto get_dst_savings() const -> std::chrono::milliseconds;

    /*!
     * Returns the time zone raw and GMT offset for the given moment in time.  Upon return, local-millis = GMT-millis +
     * rawOffset + dstOffset. All computations are performed in the proleptic Gregorian calendar.
     */
    [[nodiscard]] auto get_offset(const std::chrono::system_clock::time_point time,
                                  const offset_timezone timezone) const -> offset_result;

    /*!
     * Returns the TimeZone's raw GMT offset (i.e., the number of milliseconds to add to GMT to get local time, before
     * taking daylight savings time into account).
     */
    [[nodiscard]] auto get_raw_offset() const -> std::chrono::milliseconds;

    /*!
     * Create an unknown timezone. It behaves like the GMT/UTC time zone but has the "Etc/Unknown" IANA name.
     */
    [[nodiscard]] static auto unknown() -> timezone;

    /*!
     * Construct a GMT timezone without daylight saving (UTC). The id for this timezone is Etc/GMT
     */
    [[nodiscard]] static auto gmt() -> timezone;

    /*!
     * Construct a timezone based on standard unix tz database names (IANA/Olson database)
     * For example: "Europe/Amsterdam" or "America/New_York"
     */
    [[nodiscard]] static auto create(const char *const name) -> timezone;

    /*!
     * Construct a timezone based on the host's system settings.
     */
    [[nodiscard]] static auto local_time() -> timezone;

    [[nodiscard]] static auto enumerate() -> std::vector<std::string>;

private:
    timezone();
    explicit timezone(std::unique_ptr<timezone_impl> tz);
    std::unique_ptr<timezone_impl> timezone_;
};

} // namespace aeon::chrono
