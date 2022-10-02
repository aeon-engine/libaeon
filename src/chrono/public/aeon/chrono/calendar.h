// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/chrono/timezone.h>
#include <chrono>
#include <cstdint>

namespace aeon::chrono
{

class gregorian_calendar_impl;

enum class weekday : std::int32_t
{
    sunday = 1,
    monday,
    tuesday,
    wednessday,
    thursday,
    friday,
    saturday
};

/*!
 * Implementation of a gregorian calendar with date, time and timezone support.
 */
class calendar final
{
public:
    /*!
     * Create a calendar in the current system timezone with the current time
     */
    explicit calendar();

    /*!
     * Create a calendar from an ISO 8601 formatted string
     */
    explicit calendar(const std::u8string &str);

    /*!
     * Create a calendar with a given timezone with the current time
     */
    explicit calendar(timezone zone);

    /*!
     * Create a calendar with a given timezone and utc/gmt time
     */
    explicit calendar(timezone zone, const std::chrono::system_clock::time_point utc_time);

    /*!
     * Create a calendar with a given timezone, date and time. The date and time must be in the given timezone.
     * \param year The year
     * \param month The month (1-12)
     * \param date The date (1-31)
     * \param hour The hour of the day in 24-hour format (0-23)
     * \param minute The minute of the hour (0-59)
     * \param second The second of the minute (0-59)
     */
    explicit calendar(timezone zone, const std::int32_t year, const std::int32_t month, const std::int32_t date,
                      const std::int32_t hour = 0, const std::int32_t minute = 0, const std::int32_t second = 0);

    ~calendar();

    calendar(const calendar &other);
    auto operator=(const calendar &other) -> calendar &;

    calendar(calendar &&other) noexcept;
    auto operator=(calendar &&other) noexcept -> calendar &;

    auto operator==(const calendar &other) const -> bool;
    auto operator!=(const calendar &other) const -> bool;

    auto operator<(const calendar &other) const -> bool;
    auto operator<=(const calendar &other) const -> bool;
    auto operator>(const calendar &other) const -> bool;
    auto operator>=(const calendar &other) const -> bool;

    auto operator+=(const std::chrono::milliseconds &time) -> calendar &;

    /*!
     * Set the timezone
     */
    void set_timezone(timezone zone);

    /*!
     * Get the timezone
     */
    [[nodiscard]] auto get_timezone() const noexcept -> const timezone &;

    /*!
     * Set the date/time of the calendar. Given time_point must be in GMT/UTC.
     */
    void set(const std::chrono::system_clock::time_point utc_time);

    /*!
     * Add time to the current date/time.
     */
    void add(const std::chrono::milliseconds time);

    /*
     * Get the UTC/GMT time
     */
    [[nodiscard]] auto get() const -> std::chrono::system_clock::time_point;

    /*!
     * Set the year, month and date values. The hour and minute values are not updated.
     * \param year The year; negative years are also allowed (BC)
     * \param month The month (1-12)
     * \param date The date (1-31)
     */
    void set(const std::int32_t year, const std::int32_t month, const std::int32_t date);

    /*!
     * Set the year, month, date and time values. The second value is not updated.
     * \param year The year
     * \param month The month (1-12)
     * \param date The date (1-31)
     * \param hour The hour of the day in 24-hour format (0-23)
     * \param minute The minute of the hour (0-59)
     */
    void set(const std::int32_t year, const std::int32_t month, const std::int32_t date, const std::int32_t hour,
             const std::int32_t minute);

    /*!
     * Set the date and time values
     * \param year The year
     * \param month The month (1-12)
     * \param date The date (1-31)
     * \param hour The hour of the day in 24-hour format (0-23)
     * \param minute The minute of the hour (0-59)
     * \param second The second of the minute (0-59)
     */
    void set(const std::int32_t year, const std::int32_t month, const std::int32_t date, const std::int32_t hour,
             const std::int32_t minute, const std::int32_t second);

    /*!
     * Get the year in the given timezone.
     */
    [[nodiscard]] auto get_year() const -> std::int32_t;

    /*!
     * Get the month in the given timezone (1-12).
     */
    [[nodiscard]] auto get_month() const -> std::int32_t;

    /*!
     * Get the date (day of the month) in the given timezone (1-31)
     */
    [[nodiscard]] auto get_date() const -> std::int32_t;

    /*!
     * Get the hour of the day in the given timezone (0-23)
     */
    [[nodiscard]] auto get_hour() const -> std::int32_t;

    /*!
     * Get the minute of the hour in the given timezone (0-59)
     */
    [[nodiscard]] auto get_minute() const -> std::int32_t;

    /*!
     * Get the second of the minute in the given timezone (0-59)
     */
    [[nodiscard]] auto get_second() const -> std::int32_t;

    /*!
     * Get the millisecond of the second in the given timezone (0-999)
     */
    [[nodiscard]] auto get_millisecond() const -> std::int32_t;

    /*!
     * Get day number within the week
     */
    [[nodiscard]] auto get_week_day() const -> weekday;

    /*!
     * Get week number within the year
     */
    [[nodiscard]] auto get_week_number() const -> std::int32_t;

    /*!
     * Get the raw offset from GMT/UTC in milliseconds.
     */
    [[nodiscard]] auto get_gmt_offset() const -> std::int32_t;

    /*!
     * Get the daylight savings offset in milliseconds.
     */
    [[nodiscard]] auto get_dst_offset() const -> std::int32_t;

    /*!
     * Format the date/time as an ISO 8601 string
     */
    [[nodiscard]] auto to_string() const -> std::u8string;

private:
    timezone timezone_;
    std::unique_ptr<gregorian_calendar_impl> calendar_;
};

} // namespace aeon::chrono
