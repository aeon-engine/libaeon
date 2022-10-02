// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/web/http/method.h>
#include <string>

namespace aeon::web::http
{

struct method_string_lookup_t
{
    std::u8string str;
    http_method method = http_method::invalid;
};

static const method_string_lookup_t method_string_lookup[] = {{u8"GET", http_method::get},
                                                              {u8"HEAD", http_method::head},
                                                              {u8"POST", http_method::post},
                                                              {u8"PUT", http_method::put},
                                                              {u8"DELETE", http_method::delete_method},
                                                              {u8"OPTIONS", http_method::options},
                                                              {u8"PATCH", http_method::patch}};

auto string_to_method(const std::u8string_view &str) noexcept -> http_method
{
    for (const auto &method_string : method_string_lookup)
    {
        if (method_string.str == str)
            return method_string.method;
    }

    return http_method::invalid;
}

} // namespace aeon::web::http
