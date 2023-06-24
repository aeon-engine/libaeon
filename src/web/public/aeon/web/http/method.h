// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string_view.h>

namespace aeon::web::http
{

enum class http_method
{
    invalid,
    get,
    head,
    post,
    put,
    delete_method, // Delete is a keyword...
    options,
    patch
};

[[nodiscard]] auto string_to_method(const common::string_view &str) noexcept -> http_method;

} // namespace aeon::web::http
