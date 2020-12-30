// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/chrono/calendar.h>
#include "timezone_impl.h"
#include <unicode/gregocal.h>
#include <unicode/smpdtfmt.h>
#include <stdexcept>

namespace aeon::chrono
{

namespace internal
{
constexpr static auto iso8601_format = u"yyyy-MM-dd'T'HH:mm:ss.SSSZZZZZ";
} // namespace internal

class gregorian_calendar_impl final : public icu::GregorianCalendar
{
public:
    using icu::GregorianCalendar::GregorianCalendar;
    ~gregorian_calendar_impl() final = default;

    gregorian_calendar_impl(const gregorian_calendar_impl &other) = delete;
    auto operator=(const gregorian_calendar_impl &other) -> gregorian_calendar_impl & = delete;

    gregorian_calendar_impl(gregorian_calendar_impl &&other) noexcept = delete;
    auto operator=(gregorian_calendar_impl &&other) noexcept -> gregorian_calendar_impl & = delete;

    /*!
     * complete() must be called after manually changing date and/or time fields.
     * However this method is protected. This method exposes it to the calendar implementation.
     */
    void do_complete()
    {
        UErrorCode error{};
        complete(error);

        if (error != U_ZERO_ERROR)
            throw std::runtime_error{"Could not apply values."};
    }
};

namespace internal
{

[[nodiscard]] auto create_calendar(const icu::TimeZone &zone)
{
    UErrorCode error{};
    auto calendar = std::make_unique<gregorian_calendar_impl>(zone, error);

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Could not create gregorian calendar."};

    calendar->clear();

    return calendar;
}

[[nodiscard]] auto get_calendar_field(const icu::GregorianCalendar &calendar, const UCalendarDateFields field)
{
    UErrorCode error{};
    const auto result = calendar.get(field, error);

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Could not get calendar field."};

    return result;
}

} // namespace internal

calendar::calendar()
    : calendar{timezone::local_time(), std::chrono::system_clock::now()}
{
}

calendar::calendar(const std::string &str)
    : timezone_{}
    , calendar_{}
{
    UErrorCode error{};

    const icu::SimpleDateFormat fmt{internal::iso8601_format, error};

    if (error != U_ZERO_ERROR && error != U_USING_FALLBACK_WARNING)
        throw std::runtime_error{"Could not construct date/time formatter."};

    calendar_ = std::make_unique<gregorian_calendar_impl>(error);

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Could not create gregorian calendar."};

    const auto ustr = icu::UnicodeString::fromUTF8(str);
    icu::ParsePosition position{};
    fmt.parse(ustr, *calendar_, position);

    if (position.getErrorIndex() != -1)
        throw std::runtime_error{"Calendar parse error. Make sure the given string is in ISO 8601 format."};

    // This part is a little nasty. We should be the owner of the timezone, so we must clone
    // it and set the pointer to gain ownership of it; otherwise the calendar has ownership over it.
    timezone_ = timezone{std::make_unique<timezone_impl>(calendar_->getTimeZone().clone())};
    calendar_->setTimeZone(*timezone_.timezone_->get());
}

calendar::calendar(timezone zone)
    : calendar{std::move(zone), std::chrono::system_clock::now()}
{
}

calendar::calendar(timezone zone, const std::chrono::system_clock::time_point utc_time)
    : timezone_{std::move(zone)}
    , calendar_{internal::create_calendar(*timezone_.timezone_->get())}
{
    set(utc_time);
}

calendar::calendar(timezone zone, const std::int32_t year, const std::int32_t month, const std::int32_t date,
                   const std::int32_t hour, const std::int32_t minute, const std::int32_t second)
    : timezone_{std::move(zone)}
    , calendar_{internal::create_calendar(*timezone_.timezone_->get())}
{
    set(year, month, date, hour, minute, second);
}

calendar::~calendar() = default;

calendar::calendar(const calendar &other)
    : timezone_{other.timezone_}
    , calendar_{static_cast<gregorian_calendar_impl *>(other.calendar_->clone())}
{
    calendar_->setTimeZone(*timezone_.timezone_->get());
}

auto calendar::operator=(const calendar &other) -> calendar &
{
    if (this != &other) [[likely]]
    {
        calendar_.reset(static_cast<gregorian_calendar_impl *>(other.calendar_->clone()));
        timezone_ = other.timezone_;
        calendar_->setTimeZone(*timezone_.timezone_->get());
    }

    return *this;
}

calendar::calendar(calendar &&) noexcept = default;
auto calendar::operator=(calendar &&) noexcept -> calendar & = default;

auto calendar::operator==(const calendar &other) const -> bool
{
    UErrorCode error{};

    const auto result = calendar_->equals(*other.calendar_, error);

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Could not compare calendars."};

    return result;
}

auto calendar::operator!=(const calendar &other) const -> bool
{
    return !(*this == other);
}

auto calendar::operator<(const calendar &other) const -> bool
{
    UErrorCode error{};
    const auto result = calendar_->before(*other.calendar_, error);

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Could not compare calendars."};

    return result == TRUE;
}

auto calendar::operator<=(const calendar &other) const -> bool
{
    if (*this == other)
        return true;

    return *this < other;
}

auto calendar::operator>(const calendar &other) const -> bool
{
    UErrorCode error{};
    const auto result = calendar_->after(*other.calendar_, error);

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Could not compare calendars."};

    return result == TRUE;
}

auto calendar::operator>=(const calendar &other) const -> bool
{
    if (*this == other)
        return true;

    return *this > other;
}

auto calendar::operator+=(const std::chrono::milliseconds &time) -> calendar &
{
    add(time);
    return *this;
}

void calendar::set_timezone(timezone zone)
{
    calendar_->setTimeZone(*zone.timezone_->get());
    timezone_ = std::move(zone);
}

auto calendar::get_timezone() const noexcept -> const timezone &
{
    return timezone_;
}

void calendar::set(const std::chrono::system_clock::time_point utc_time)
{
    const auto d =
        std::chrono::duration<double, std::chrono::milliseconds::period>(utc_time.time_since_epoch()).count();

    UErrorCode error{};
    calendar_->setTime(d, error);

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Could not set date/time."};
}

void calendar::add(const std::chrono::milliseconds time)
{
    const auto count = time.count();

    if (count > std::numeric_limits<std::int32_t>::max())
        throw std::runtime_error{"Time to add is out of range."};

    if (count < std::numeric_limits<std::int32_t>::min())
        throw std::runtime_error{"Time to add is out of range."};

    UErrorCode error{};
    calendar_->add(UCAL_MILLISECOND, static_cast<std::int32_t>(time.count()), error);

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Could not add time."};
}

auto calendar::get() const -> std::chrono::system_clock::time_point
{
    UErrorCode error{};
    const std::chrono::duration<double, std::chrono::milliseconds::period> period{calendar_->getTime(error)};

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Could not get date/time."};

    return std::chrono::system_clock::time_point{
        std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(period.count()))};
}

void calendar::set(const std::int32_t year, const std::int32_t month, const std::int32_t date)
{
    calendar_->set(year, month - 1, date);
    calendar_->do_complete();
}

void calendar::set(const std::int32_t year, const std::int32_t month, const std::int32_t date, const std::int32_t hour,
                   const std::int32_t minute)
{
    calendar_->set(year, month - 1, date, hour, minute);
    calendar_->do_complete();
}

void calendar::set(const std::int32_t year, const std::int32_t month, const std::int32_t date, const std::int32_t hour,
                   const std::int32_t minute, const std::int32_t second)
{
    calendar_->set(year, month - 1, date, hour, minute, second);
    calendar_->do_complete();
}

auto calendar::get_year() const -> std::int32_t
{
    UErrorCode error{};
    const auto result = calendar_->get(UCAL_YEAR, error);

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Could not get year."};

    return result;
}

auto calendar::get_month() const -> std::int32_t
{
    return internal::get_calendar_field(*calendar_, UCAL_MONTH) + 1;
}

auto calendar::get_date() const -> std::int32_t
{
    return internal::get_calendar_field(*calendar_, UCAL_DATE);
}

auto calendar::get_hour() const -> std::int32_t
{
    return internal::get_calendar_field(*calendar_, UCAL_HOUR_OF_DAY);
}

auto calendar::get_minute() const -> std::int32_t
{
    return internal::get_calendar_field(*calendar_, UCAL_MINUTE);
}

auto calendar::get_second() const -> std::int32_t
{
    return internal::get_calendar_field(*calendar_, UCAL_SECOND);
}

auto calendar::get_millisecond() const -> std::int32_t
{
    return internal::get_calendar_field(*calendar_, UCAL_MILLISECOND);
}

auto calendar::get_week_day() const -> weekday
{
    return static_cast<weekday>(internal::get_calendar_field(*calendar_, UCAL_DAY_OF_WEEK));
}

auto calendar::get_week_number() const -> std::int32_t
{
    return internal::get_calendar_field(*calendar_, UCAL_WEEK_OF_YEAR);
}

auto calendar::get_gmt_offset() const -> std::int32_t
{
    return internal::get_calendar_field(*calendar_, UCAL_ZONE_OFFSET);
}

auto calendar::get_dst_offset() const -> std::int32_t
{
    return internal::get_calendar_field(*calendar_, UCAL_DST_OFFSET);
}

auto calendar::to_string() const -> std::string
{
    UErrorCode error{};

    const icu::SimpleDateFormat fmt{internal::iso8601_format, error};

    if (error != U_ZERO_ERROR && error != U_USING_FALLBACK_WARNING)
        throw std::runtime_error{"Could not construct date/time formatter."};

    icu::UnicodeString str;
    icu::FieldPosition fields;
    fmt.format(*calendar_, str, fields);

    std::string std_str;
    str.toUTF8String(std_str);
    return std_str;
}

} // namespace aeon::chrono
