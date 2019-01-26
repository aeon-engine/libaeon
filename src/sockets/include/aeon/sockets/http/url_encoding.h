// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <string>

namespace aeon::sockets::http
{

auto url_encode(const std::string &str) -> std::string;
auto url_decode(const std::string &str) -> std::string;

} // namespace aeon::sockets::http
