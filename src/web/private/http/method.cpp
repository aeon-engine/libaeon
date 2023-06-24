// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/web/http/method.h>
#include <aeon/common/string.h>

namespace aeon::web::http
{

struct method_string_lookup_t
{
    common::string str;
    http_method method = http_method::invalid;
};

static const method_string_lookup_t method_string_lookup[] = {{"GET", http_method::get},
                                                              {"HEAD", http_method::head},
                                                              {"POST", http_method::post},
                                                              {"PUT", http_method::put},
                                                              {"DELETE", http_method::delete_method},
                                                              {"OPTIONS", http_method::options},
                                                              {"PATCH", http_method::patch}};

auto string_to_method(const common::string_view &str) noexcept -> http_method
{
    for (const auto &method_string : method_string_lookup)
    {
        if (method_string.str == str)
            return method_string.method;
    }

    return http_method::invalid;
}

} // namespace aeon::web::http
