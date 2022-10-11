// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/chrono/timezone.h>
#include "timezone_impl.h"
#include <unicode/timezone.h>
#include <unicode/strenum.h>
#include <stdexcept>
#include <cassert>

namespace aeon::chrono
{

timezone::~timezone() = default;

timezone::timezone(const timezone &other)
    : timezone_{other.timezone_->clone()}
{
}

auto timezone::operator=(const timezone &other) -> timezone &
{
    timezone_ = other.timezone_->clone();
    return *this;
}

timezone::timezone(timezone &&) noexcept = default;
auto timezone::operator=(timezone &&) noexcept -> timezone & = default;

auto timezone::operator==(const timezone &other) const -> bool
{
    return timezone_->has_same_rules(*other.timezone_);
}

auto timezone::operator!=(const timezone &other) const -> bool
{
    return !(*this == other);
}

auto timezone::id() const -> common::string
{
    assert(timezone_);
    return timezone_->id();
}

auto timezone::uses_dst() const -> bool
{
    assert(timezone_);
    return timezone_->uses_dst();
}

auto timezone::get_dst_savings() const -> std::chrono::milliseconds
{
    assert(timezone_);
    return timezone_->get_dst_savings();
}

auto timezone::get_offset(const std::chrono::system_clock::time_point time, const offset_timezone timezone) const
    -> offset_result
{
    assert(timezone_);
    return timezone_->get_offset(time, timezone);
}

auto timezone::get_raw_offset() const -> std::chrono::milliseconds
{
    assert(timezone_);
    return timezone_->get_raw_offset();
}

auto timezone::unknown() -> timezone
{
    return timezone{std::make_unique<timezone_impl>(icu::TimeZone::getUnknown().clone())};
}

auto timezone::gmt() -> timezone
{
    return timezone{std::make_unique<timezone_impl>(icu::TimeZone::getGMT()->clone())};
}

auto timezone::create(const char *const name) -> timezone
{
    return timezone{std::make_unique<timezone_impl>(icu::TimeZone::createTimeZone(name))};
}

auto timezone::local_time() -> timezone
{
    return timezone{std::make_unique<timezone_impl>(icu::TimeZone::createDefault())};
}

auto timezone::enumerate() -> std::vector<common::string>
{
    std::unique_ptr<icu::StringEnumeration> timezones{icu::TimeZone::createEnumeration()};

    UErrorCode error = U_ZERO_ERROR;

    std::vector<common::string> result;
    result.reserve(timezones->count(error));

    if (U_FAILURE(error))
        throw std::runtime_error{"Error enumerating timezones."};

    while (const auto timezone = timezones->snext(error))
    {
        if (U_FAILURE(error))
            throw std::runtime_error{"Error enumerating timezones."};

        common::string value;
        timezone->toUTF8String(value.str());
        result.emplace_back(std::move(value));
    }

    return result;
}

timezone::timezone()
    : timezone_{}
{
}

timezone::timezone(std::unique_ptr<timezone_impl> tz)
    : timezone_{std::move(tz)}
{
}

} // namespace aeon::chrono
