// Copyright (c) 2012-2019 Robin Degen

#include <aeon/sockets/http/validators.h>
#include <aeon/sockets/http/constants.h>

namespace aeon::sockets::http::detail
{

auto validate_http_version_string(const std::string &version_string) noexcept -> bool
{
    return version_string == http_version_string;
}

auto validate_uri(const std::string &uri) noexcept -> bool
{
    for (const auto c : uri)
    {
        // Valid character?
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '/' || c == '?' ||
              c == '%' || c == '&' || c == '=' || c == '+' || c == '-' || c == '*' || c == '.' || c == '_' ||
              c == '@' || c == ',' || c == '~'))
        {
            return false;
        }
    }

    return true;
}

} // namespace aeon::sockets::http::detail
