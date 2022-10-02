// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/chrono/offset.h>
#include <unicode/timezone.h>
#include <chrono>
#include <string>
#include <memory>
#include <stdexcept>

namespace aeon::chrono
{

class timezone_impl final
{
public:
    explicit timezone_impl(icu::TimeZone *tz) noexcept
        : timezone_{tz}
    {
    }

    ~timezone_impl() = default;

    timezone_impl(const timezone_impl &) = delete;
    auto operator=(const timezone_impl &) -> timezone_impl & = delete;

    timezone_impl(timezone_impl &&) noexcept = delete;
    auto operator=(timezone_impl &&) noexcept -> timezone_impl & = delete;

    [[nodiscard]] auto id() const -> std::string
    {
        icu::UnicodeString id;
        timezone_->getID(id);

        std::string id_str;
        id.toUTF8String(id_str);
        return id_str;
    }

    [[nodiscard]] auto has_same_rules(const timezone_impl &tz) const noexcept -> bool
    {
        return timezone_->hasSameRules(*tz.timezone_) == 1;
    }

    [[nodiscard]] auto uses_dst() const noexcept -> bool
    {
        return timezone_->useDaylightTime() == 1;
    }

    [[nodiscard]] auto get_dst_savings() const -> std::chrono::milliseconds
    {
        return std::chrono::milliseconds{timezone_->getDSTSavings()};
    }

    [[nodiscard]] auto get_offset(const std::chrono::system_clock::time_point time,
                                  const offset_timezone timezone) const -> offset_result
    {
        const auto date =
            std::chrono::duration<double, std::chrono::milliseconds::period>(time.time_since_epoch()).count();

        std::int32_t raw_offset{};
        std::int32_t dst_offset{};
        UErrorCode error{};
        timezone_->getOffset(date, timezone == offset_timezone::local ? 1 : 0, raw_offset, dst_offset, error);

        if (U_FAILURE(error))
            throw std::runtime_error{"Error in get_offset"};

        return {std::chrono::milliseconds{raw_offset}, std::chrono::milliseconds{dst_offset}};
    }

    [[nodiscard]] auto get_raw_offset() const -> std::chrono::milliseconds
    {
        return std::chrono::milliseconds{timezone_->getRawOffset()};
    }

    [[nodiscard]] auto get() const noexcept
    {
        return timezone_.get();
    }

    [[nodiscard]] auto clone() const -> std::unique_ptr<timezone_impl>
    {
        return std::make_unique<timezone_impl>(timezone_->clone());
    }

private:
    std::unique_ptr<icu::TimeZone> timezone_;
};

} // namespace aeon::chrono
