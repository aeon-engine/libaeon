// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>

namespace aeon::web::http
{

auto url_encode(const common::string &str) -> common::string;
auto url_decode(const common::string &str) -> common::string;

} // namespace aeon::web::http
