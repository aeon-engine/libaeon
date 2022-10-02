// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <string>

namespace aeon::web::http
{

auto url_encode(const std::u8string &str) -> std::u8string;
auto url_decode(const std::u8string &str) -> std::u8string;

} // namespace aeon::web::http
