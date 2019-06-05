// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <string>

namespace aeon::web::http::detail
{

auto validate_http_version_string(const std::string &version_string) noexcept -> bool;
auto validate_uri(const std::string &uri) noexcept -> bool;

} // namespace aeon::web::http::detail
