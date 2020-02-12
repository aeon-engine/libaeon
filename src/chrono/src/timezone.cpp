// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/chrono/timezone.h>
#include <unicode/timezone.h>
#include <unicode/strenum.h>
#include <stdexcept>
#include <cassert>

namespace aeon::chrono
{

class timezone_impl final : public icu::TimeZone
{
public:
    using icu::TimeZone::TimeZone;
    ~timezone_impl() final = default;
};

timezone::~timezone() = default;

timezone::timezone(const timezone &other)
    : timezone_{static_cast<timezone_impl *>(other.timezone_->clone())}
{
}

auto timezone::operator=(const timezone &other) -> timezone &
{
    timezone_.reset(static_cast<timezone_impl *>(other.timezone_->clone()));
    return *this;
}

timezone::timezone(timezone &&) noexcept = default;
auto timezone::operator=(timezone &&) noexcept -> timezone & = default;

auto timezone::operator==(const timezone &other) const -> bool
{
    return timezone_->hasSameRules(*other.timezone_) == TRUE;
}

auto timezone::operator!=(const timezone &other) const -> bool
{
    return !(*this == other);
}

auto timezone::id() const -> std::string
{
    assert(timezone_);

    icu::UnicodeString id;
    timezone_->getID(id);

    std::string id_str;
    id.toUTF8String(id_str);
    return id_str;
}

auto timezone::uses_dst() const -> bool
{
    assert(timezone_);
    return timezone_->useDaylightTime() == TRUE;
}

auto timezone::get_dst_savings() const -> std::chrono::milliseconds
{
    assert(timezone_);
    return std::chrono::milliseconds{timezone_->getDSTSavings()};
}

auto timezone::get_offset(const std::chrono::system_clock::time_point time, const offset_timezone timezone) const
    -> offset_result
{
    assert(timezone_);

    const auto date = std::chrono::duration<double, std::chrono::milliseconds::period>(time.time_since_epoch()).count();

    std::int32_t raw_offset{};
    std::int32_t dst_offset{};
    UErrorCode error{};
    timezone_->getOffset(date, timezone == offset_timezone::local ? TRUE : FALSE, raw_offset, dst_offset, error);

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Error in get_offset"};

    return {std::chrono::milliseconds{raw_offset}, std::chrono::milliseconds{dst_offset}};
}

auto timezone::get_raw_offset() const -> std::chrono::milliseconds
{
    assert(timezone_);
    return std::chrono::milliseconds{timezone_->getRawOffset()};
}

auto timezone::unknown() -> timezone
{
    return timezone{static_cast<timezone_impl *>(icu::TimeZone::getUnknown().clone())};
}

auto timezone::gmt() -> timezone
{
    return timezone{static_cast<timezone_impl *>(icu::TimeZone::getGMT()->clone())};
}

auto timezone::create(const char *const name) -> timezone
{
    return timezone{static_cast<timezone_impl *>(icu::TimeZone::createTimeZone(name))};
}

auto timezone::local_time() -> timezone
{
    return timezone{static_cast<timezone_impl *>(icu::TimeZone::createDefault())};
}

auto timezone::enumerate() -> std::vector<std::string>
{
    std::unique_ptr<icu::StringEnumeration> timezones{icu::TimeZone::createEnumeration()};

    UErrorCode error = U_ZERO_ERROR;

    std::vector<std::string> result;
    result.reserve(timezones->count(error));

    if (error != U_ZERO_ERROR)
        throw std::runtime_error{"Error enumerating timezones."};

    while (const auto timezone = timezones->snext(error))
    {
        if (error != U_ZERO_ERROR)
            throw std::runtime_error{"Error enumerating timezones."};

        std::string value;
        timezone->toUTF8String(value);
        result.push_back(std::move(value));
    }

    return result;
}

timezone::timezone()
    : timezone_{}
{
}

timezone::timezone(timezone_impl *tz)
    : timezone_{tz}
{
}

} // namespace aeon::chrono
