// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <string_view>

namespace aeon::sockets::http
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

auto string_to_method(const std::string_view &str) noexcept -> http_method;

} // namespace aeon::sockets::http
