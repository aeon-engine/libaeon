// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <string>

namespace aeon::web::http
{

auto url_encode(const std::string &str) -> std::string;
auto url_decode(const std::string &str) -> std::string;

} // namespace aeon::web::http
