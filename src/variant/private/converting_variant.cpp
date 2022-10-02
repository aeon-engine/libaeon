// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/variant/converting_variant.h>

namespace aeon::variant
{

converting_variant::converting_variant() noexcept
    : data_{}
    , type_{static_cast<std::uint32_t>(type::unknown)}
    , user_index_{0}
{
}

converting_variant::converting_variant(const char8_t *const str)
    : data_{std::u8string{str}}
    , type_{static_cast<std::uint32_t>(type::string)}
    , user_index_{0}
{
}

converting_variant::converting_variant(const std::chrono::system_clock::time_point utc_time)
    : data_{chrono::calendar{chrono::timezone::gmt(), utc_time}}
    , type_{static_cast<std::uint32_t>(type::calendar)}
    , user_index_{0}
{
}

converting_variant::converting_variant(const enum type t) noexcept
    : data_{}
    , type_{static_cast<std::uint32_t>(t)}
    , user_index_{0}
{
}

auto converting_variant::type() const noexcept -> enum type
{
    return static_cast<enum type>(type_);
}

auto converting_variant::is_user_type() const noexcept -> bool
{
    return type() == type::user;
}

auto converting_variant::user_index() const noexcept -> int
{
    if (!is_user_type() || is_null())
        return 0;

    return user_index_;
}

auto converting_variant::is_null() const noexcept -> bool
{
    return data_.index() == 0;
}

} // namespace aeon::variant
