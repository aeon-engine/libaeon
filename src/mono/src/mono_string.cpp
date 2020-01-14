// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/mono/mono_string.h>

namespace aeon::mono
{

mono_string::mono_string(MonoString *mono_string) noexcept
    : mono_object{reinterpret_cast<MonoObject *>(mono_string)}
    , domain_{nullptr}
{
}

mono_string::mono_string(MonoDomain *domain, const std::string &str) noexcept
    : mono_object{reinterpret_cast<MonoObject *>(mono_string_new(domain, str.c_str()))}
    , domain_{domain}
{
}

mono_string::~mono_string() = default;

mono_string::mono_string(mono_string &&) noexcept = default;
auto mono_string::operator=(mono_string &&) noexcept -> mono_string & = default;

auto mono_string::operator=(const std::string &str) noexcept -> mono_string &
{
    if (domain_ == nullptr)
        domain_ = mono_object_get_domain(object_);

    object_ = reinterpret_cast<MonoObject *>(mono_string_new(domain_, str.c_str()));
    return *this;
}

[[nodiscard]] auto mono_string::str() const -> std::string
{
    // TODO: This could be probably optimized by doing no additional
    // allocation though mono_string_chars and mono_string_length.
    const auto raw_utf8_str = mono_string_to_utf8(get_mono_string());
    std::string str = raw_utf8_str;
    mono_free(raw_utf8_str);
    return str;
}

[[nodiscard]] auto mono_string::get_mono_string() const -> MonoString *
{
    return reinterpret_cast<MonoString *>(object_);
}

} // namespace aeon::mono
